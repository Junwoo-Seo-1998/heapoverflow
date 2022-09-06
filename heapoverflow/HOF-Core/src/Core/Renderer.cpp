/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "Renderer.h"
#include "Camera.h"
#include "shader.h"
#include "GL/glew.h"
#include "Entity/Entity.h"
#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Components/LightComponent.h"
#include "Core/Graphics/Mesh.h"
#include "Core/Graphics/Material.h"
#include "glm/glm.hpp"
namespace hof
{

	Renderer::RenderData Renderer::s_Data;

	
	void Renderer::Init()
	{
		glEnable(GL_DEPTH_TEST);
		//glEnable(GL_CULL_FACE);
		//glFrontFace(GL_CCW);
		//glCullFace(GL_BACK);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glViewport(0, 0, 1600, 900);

		//don't need to add to shader lib
		s_Data.ShadowRenderShader = std::make_shared<Shader>("ShadowRenderShader", "resource/shader/Shadow/ShadowRender.vert", "resource/shader/Shadow/ShadowRender.frag");
		s_Data.DepthRenderShader = std::make_shared<Shader>("DepthRenderShader", "resource/shader/Depth/Depth.vert", "resource/shader/Depth/Depth.frag");

		glm::vec4 QuadVertices[4];
		QuadVertices[0] = { -1.f, -1.f, 0.0f, 1.0f };
		QuadVertices[1] = { 1.f, -1.f, 0.0f, 1.0f };
		QuadVertices[2] = { 1.f,  1.f, 0.0f, 1.0f };
		QuadVertices[3] = { -1.f,  1.f, 0.0f, 1.0f };

		glm::vec2 QuadTexCoord[4];
		QuadTexCoord[0] = { 0.f,0.f };
		QuadTexCoord[1] = { 1.f,0.f };
		QuadTexCoord[2] = { 1.f,1.f };
		QuadTexCoord[3] = { 0.f,1.f };
		

		unsigned int QuadIndices[6];
		QuadIndices[0] = 0;
		QuadIndices[1] = 1;
		QuadIndices[2] = 2;
					
		QuadIndices[3] = 2;
		QuadIndices[4] = 3;
		QuadIndices[5] = 0;

		s_Data.QuadVertexArray = std::make_shared<VertexArray>();
		std::shared_ptr<VertexBuffer> QuadVertexBuffer = std::make_shared<VertexBuffer>(QuadVertices, sizeof(glm::vec4) * 4);
		QuadVertexBuffer->DescribeData({
			{Float4,0},
		});
		std::shared_ptr<VertexBuffer> QuadTexCoordBuffer = std::make_shared<VertexBuffer>(QuadTexCoord, sizeof(glm::vec2) * 4);
		QuadTexCoordBuffer->DescribeData({
			{Float2,1},
		});
		
		std::shared_ptr<IndexBuffer> QuadIndexBuffer = std::make_shared<IndexBuffer>(QuadIndices, 6);
		s_Data.QuadVertexArray->AddVertexBuffer(QuadVertexBuffer);
		s_Data.QuadVertexArray->AddVertexBuffer(QuadTexCoordBuffer);
		s_Data.QuadVertexArray->AddIndexBuffer(QuadIndexBuffer);

	}

	void Renderer::Shutdown()
	{
	}

	void Renderer::SetViewport(unsigned width, unsigned height)
	{
		glViewport(0, 0, width, height);
	}

	void Renderer::SetClearColor(const glm::vec4& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::ClearScreen()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::SetNumberOfPatches(unsigned num)
	{
		glPatchParameteri(GL_PATCH_VERTICES, num);
	}

	void Renderer::DrawShadow(const std::shared_ptr<Mesh>& mesh, const glm::mat4& transform)
	{
		s_Data.ShadowRenderShader->Bind();
		s_Data.ShadowRenderShader->SetMat4("u_ViewProjection", s_Data.ViewProjectionMatrix);
		s_Data.ShadowRenderShader->SetMat4("u_Transform", transform);

		for (auto sub_mesh : *mesh)
		{
			sub_mesh->GetVertexArray()->Bind();
			glDrawElements(GL_TRIANGLES, sub_mesh->GetNumOfIndices(), GL_UNSIGNED_INT, nullptr);
		}
		
	}

	void Renderer::DrawBegin(Entity& cam_entt)
	{
		CameraComponent& cam = cam_entt.GetComponent<CameraComponent>();
		TransformComponent& transform = cam_entt.GetComponent<TransformComponent>();
		DrawBegin(cam.Camera, transform.GetTransform());
	}

	void Renderer::DrawBegin(Camera& cam, const glm::mat4& cam_transform)
	{
		s_Data.ViewProjectionMatrix = cam.GetProjection() * glm::inverse(cam_transform);
	}

	void Renderer::DrawBegin(const glm::mat4& mat)
	{
		s_Data.ViewProjectionMatrix = mat;
	}

	void Renderer::DrawIndexed(const std::shared_ptr<Shader>& shader, std::shared_ptr<VertexArray> vertex_array,
		const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_Data.ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		GLenum DrawMode = GL_TRIANGLES;

		if (shader->GetFlag(ShaderFlag::TessellationShader))
		{
			Renderer::SetNumberOfPatches(3);
			DrawMode = GL_PATCHES;
		}
		
		glDrawElements(DrawMode, vertex_array->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}


	void Renderer::DrawMesh(const std::shared_ptr<Shader>& shader, std::shared_ptr<Mesh> mesh,
		const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("u_ViewProjection", s_Data.ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);

		GLenum DrawMode = GL_TRIANGLES;

		if (shader->GetFlag(ShaderFlag::TessellationShader))
		{
			Renderer::SetNumberOfPatches(3);
			DrawMode = GL_PATCHES;
		}
		
		for (auto sub_mesh:*mesh)
		{
			sub_mesh->GetVertexArray()->Bind();
			glDrawElements(DrawMode, sub_mesh->GetNumOfIndices(), GL_UNSIGNED_INT, nullptr);
		}
		
	}

	void Renderer::DrawMeshWithMaterials(const std::vector<std::shared_ptr<Material>>& materials,
		const std::shared_ptr<Mesh>& mesh, const glm::mat4& transform)
	{
		for (const auto& material : materials)
		{
			DrawMeshWithMaterial(material, mesh, transform);
		}
	}

	void Renderer::DrawMeshWithMaterial(const std::shared_ptr<Material>& material, const std::shared_ptr<Mesh>& mesh,
	                                    const glm::mat4& transform)
	{
		material->Bind();
		auto shader = material->GetShader();
		shader->SetMat4("u_ViewProjection", s_Data.ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);
		GLenum DrawMode = GL_TRIANGLES;
		if (shader->GetFlag(ShaderFlag::TessellationShader))
		{
			Renderer::SetNumberOfPatches(3);
			DrawMode = GL_PATCHES;
		}
		
		for (auto sub_mesh : *mesh)
		{
			sub_mesh->GetVertexArray()->Bind();
			
			glDrawElements(DrawMode, sub_mesh->GetNumOfIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}

	void Renderer::DrawMeshWithMaterialAndShadow(const std::shared_ptr<Material>& material,
		const std::shared_ptr<Mesh>& mesh, const glm::mat4& transform, const TransformComponent& light_transform,
		const LightComponent& light_component)
	{
		material->Bind();
		auto shader = material->GetShader();
		shader->SetMat4("u_ViewProjection", s_Data.ViewProjectionMatrix);
		shader->SetMat4("u_Transform", transform);
		shader->SetFloat3("u_LightPosition", light_transform.Position);
		shader->SetMat4("u_LightProjection", light_component.m_Light.GetLightProjection() * glm::inverse(light_transform.GetTransform()));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, light_component.m_ShadowMap->GetDepthTexture());
		shader->SetInt("ShadowMap", 0);
		
		GLenum DrawMode = GL_TRIANGLES;
		if (shader->GetFlag(ShaderFlag::TessellationShader))
		{
			Renderer::SetNumberOfPatches(3);
			DrawMode = GL_PATCHES;
		}

		for (auto sub_mesh : *mesh)
		{
			sub_mesh->GetVertexArray()->Bind();

			glDrawElements(DrawMode, sub_mesh->GetNumOfIndices(), GL_UNSIGNED_INT, nullptr);
		}
	}


	void Renderer::DrawEnd()
	{
	}

	void Renderer::DrawDepthTexture(unsigned depth_texture)
	{
		s_Data.DepthRenderShader->Bind();
		s_Data.QuadVertexArray->Bind();
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depth_texture);

		s_Data.DepthRenderShader->SetInt("ShadowMap", 0);

		glDrawElements(GL_TRIANGLES, s_Data.QuadVertexArray->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

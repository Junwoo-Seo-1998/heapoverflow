/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include "glm/glm.hpp"
#include <memory>

#include "shader.h"
#include "VertexArray.h"
#include "glm/ext/matrix_transform.hpp"
namespace hof
{
	struct LightComponent;
	struct TransformComponent;
	class Camera;
	class Entity;
	class Mesh;
	class Material;
	class Renderer
	{
	public:
		static void Init();
		static void Shutdown();
		static void SetViewport(unsigned int width, unsigned height);
		static void SetClearColor(const glm::vec4& color);
		static void ClearScreen();
		static void SetNumberOfPatches(unsigned int num);
		
		static void DrawShadow(const std::shared_ptr<Mesh>& mesh, const glm::mat4& transform);
		
		static void DrawBegin(Entity& cam_entt);
		static void DrawBegin(Camera& cam, const glm::mat4& cam_transform);
		static void DrawBegin(const glm::mat4& mat);
		static void DrawIndexed(const std::shared_ptr<Shader>& shader, std::shared_ptr<VertexArray> vertex_array, const glm::mat4& transform);
		static void DrawMesh(const std::shared_ptr<Shader>& shader, std::shared_ptr<Mesh> mesh, const glm::mat4& transform);
		static void DrawMeshWithMaterials(const std::vector<std::shared_ptr<Material>>& materials, const std::shared_ptr<Mesh>& mesh, const glm::mat4& transform);
		static void DrawMeshWithMaterial(const std::shared_ptr<Material>& material, const std::shared_ptr<Mesh>& mesh, const glm::mat4& transform);

		static void DrawMeshWithMaterialAndShadow(const std::shared_ptr<Material>& material, const std::shared_ptr<Mesh>& mesh, const glm::mat4& transform,
			const TransformComponent& light_transform, const LightComponent& light_component);
		static void DrawEnd();
		//only for debug purpose
		static void DrawDepthTexture(unsigned int depth_texture);
		
	private:
		struct RenderData
		{
			glm::mat4 ViewProjectionMatrix=glm::identity<glm::mat4>();

			std::shared_ptr<Shader> ShadowRenderShader;
			
			std::shared_ptr<Shader> DepthRenderShader;
			std::shared_ptr<VertexArray> QuadVertexArray;
		};
		static RenderData s_Data;
	};
}

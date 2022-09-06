/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "ShadowGUILayer.h"

#include "imgui.h"
#include "Core/Components/LightComponent.h"


void ShadowGUILayer::OnAttach()
{
	using namespace hof;
	FrameBufferSpecification spec;
	spec.Formats = { FrameBufferFormat::RGBA,FrameBufferFormat::Depth };
	spec.Width = 1600;
	spec.Height = 900;
	DepthRenderingFrameBuffer = std::make_shared<FrameBuffer>(spec);
}

void ShadowGUILayer::OnDetach()
{
}

void ShadowGUILayer::OnUpdate([[maybe_unused]] float dt)
{
	
}

void ShadowGUILayer::OnGuiRender()
{
	ImGui::Begin("Shadow");
	ImGui::Text("Light Control");
	ImGui::Separator();
	auto lights = hof::SceneManager::GetCurrentScene()->GetRegistry().view<hof::TransformComponent, hof::LightComponent>();
	for (auto& entt : lights)
	{
		DepthRenderingFrameBuffer->Bind();
		hof::Renderer::ClearScreen();
		auto [transform, light] = lights.get<hof::TransformComponent, hof::LightComponent>(entt);
		glm::vec3 pos = transform.Position;
		ImGui::DragFloat3("Light Position", &pos.x);
		transform.Position = pos;	
		glm::vec3 rot = transform.Rotation;
		ImGui::DragFloat3("Light Rotation", &rot.x,0.005f);
		transform.Rotation = rot;
		float far = light.m_Light.GetFar();
		ImGui::DragFloat("Far", &far);
		light.m_Light.SetFar(far);
		float near = light.m_Light.GetNear();
		ImGui::DragFloat("Near", &near);
		light.m_Light.SetNear(near);
		hof::Renderer::DrawDepthTexture(light.m_ShadowMap->GetDepthTexture());
		DepthRenderingFrameBuffer->Unbind();
		break; //just get first one 
	}
	
	ImGui::DragFloat("Max Bias", &max_bias,0.001f);
	hof::AssetManager::GetShaderManager()->Get("ShadowShader")->SetFloat("u_BiasMax", max_bias);
	ImGui::DragFloat("Min Bias", &min_bias,0.001f);
	hof::AssetManager::GetShaderManager()->Get("ShadowShader")->SetFloat("u_BiasMin", min_bias);

	
	
	ImGui::Separator();
	ImGui::Text("Shadow Depth Texture");
	ImGui::Separator();
	uint32_t textureID = DepthRenderingFrameBuffer->GetColorTexture(0);
	ImGui::Image((void*)textureID, ImVec2{ 400,400 }, ImVec2{ 0,1 }, ImVec2{ 1,0 });
	ImGui::End();
}

void ShadowGUILayer::OnEvent([[maybe_unused]] hof::Event& event)
{
}

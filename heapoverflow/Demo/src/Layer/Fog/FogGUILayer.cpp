/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "FogGUILayer.h"
#include "imgui.h"

FogGUILayer::FogGUILayer()
{
}

void FogGUILayer::OnAttach()
{
}

void FogGUILayer::OnDetach()
{
}

void FogGUILayer::OnUpdate([[maybe_unused]]float dt)
{
	hof::Renderer::SetClearColor(m_FogColor);
	hof::AssetManager::GetShaderManager()->Get("FogShader")->SetFloat3("fog_color", { m_FogColor.x,m_FogColor.y,m_FogColor.z });
	hof::AssetManager::GetShaderManager()->Get("FogShader")->SetFloat("fog_max_dist", m_fog_max_dist);
	hof::AssetManager::GetShaderManager()->Get("FogShader")->SetFloat("fog_min_dist", m_fog_min_dist);
}

void FogGUILayer::OnGuiRender()
{
	ImGui::Begin("Fog Control");
	ImGui::ColorPicker4("Fog Color", &m_FogColor.x);
	ImGui::DragFloat("fog_max_dist", &m_fog_max_dist,1,m_fog_min_dist+10,1000.f);
	ImGui::DragFloat("fog_min_dist", &m_fog_min_dist,1,1,m_fog_max_dist-10);
	ImGui::End();
}

void FogGUILayer::OnEvent([[maybe_unused]] hof::Event& event)
{
}

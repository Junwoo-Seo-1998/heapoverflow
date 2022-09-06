/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "ToonGUILayer.h"
#include "imgui.h"
#include "HOF.h"
ToonGUILayer::ToonGUILayer()
{
}

void ToonGUILayer::OnAttach()
{
}

void ToonGUILayer::OnDetach()
{
}

void ToonGUILayer::OnUpdate([[maybe_unused]] float dt)
{
}

void ToonGUILayer::OnGuiRender()
{
	ImGui::Begin("Toon Control");
	ImGui::ColorEdit3("color", &color.x);
	hof::AssetManager::GetShaderManager()->Get("ToonShader")->SetFloat3("u_Color",color);
	ImGui::End();
}

void ToonGUILayer::OnEvent([[maybe_unused]] hof::Event& event)
{
}

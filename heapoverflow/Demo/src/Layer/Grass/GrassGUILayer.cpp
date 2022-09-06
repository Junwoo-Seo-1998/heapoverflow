/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "GrassGUILayer.h"
#include "imgui.h"
GrassGUILayer::GrassGUILayer()
{
}

void GrassGUILayer::OnAttach()
{
}

void GrassGUILayer::OnDetach()
{
}

void GrassGUILayer::OnUpdate([[maybe_unused]] float dt)
{
	auto shader = hof::AssetManager::GetShaderManager()->Get("GrassShader");
	shader->Bind();
	shader->SetFloat("Inner", Inner);
	shader->SetFloat("Outer", Outer);
	shader->SetFloat("Outer", Outer);
	shader->SetFloat("u_width", width);
	shader->SetFloat("u_height", height);
	shader->SetFloat("u_rotation", glm::radians(rotate));
	shader = hof::AssetManager::GetShaderManager()->Get("GrassGroundShader");
	shader->Bind();
	shader->SetFloat("Inner", Inner);
	shader->SetFloat("Outer", Outer);
}

void GrassGUILayer::OnGuiRender()
{
	ImGui::Begin("Grass");
	ImGui::Text("Tessellation Control");
	ImGui::Separator();
	ImGui::DragFloat("Inner", &Inner, 0.5f, 1.f, 100.f);
	ImGui::DragFloat("Outer", &Outer, 0.5f, 1.f, 100.f);
	ImGui::Separator();

	ImGui::Text("Geometry Control");
	ImGui::Separator();
	ImGui::DragFloat("Width", &width, 0.5f, 0.01f, 100.f);
	ImGui::DragFloat("Height", &height, 0.5f, 1.f, 100.f);
	ImGui::DragFloat("Rotation", &rotate, 1.f, 0.f, 90.f);
	ImGui::Separator();
	ImGui::End();
}

void GrassGUILayer::OnEvent([[maybe_unused]] hof::Event& event)
{
	
}

/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "CommonSceneGUILayer.h"
#include "imgui.h"
void CommonSceneGUILayer::OnAttach()
{
}

void CommonSceneGUILayer::OnDetach()
{
}

void CommonSceneGUILayer::OnUpdate([[maybe_unused]] float dt)
{
}

void CommonSceneGUILayer::OnGuiRender()
{
	ImGui::Begin("Demo");

	ImGui::Text("Render Mode");
	ImGui::Separator();
	if (ImGui::Button("Normal-Mode"))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	if(ImGui::Button("Poly-Line-Mode"))
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glPointSize(3);
	}
	ImGui::Separator();

	ImGui::Text("Select Demo");
	ImGui::Separator();
	if (ImGui::Button("ToonDemo"))
	{
		hof::SceneManager::LoadScene("ToonDemo");
	}


	if (ImGui::Button("FogDemo"))
	{
		hof::SceneManager::LoadScene("FogDemo");
	}

	if (ImGui::Button("GrassDemo - ( Geometry, Tessellation )"))
	{
		hof::SceneManager::LoadScene("GrassDemo");
	}

	if (ImGui::Button("ShadowDemo"))
	{
		hof::SceneManager::LoadScene("ShadowDemo");
	}
	ImGui::Separator();
	
	ImGui::End();


	ImGui::Begin("Cam");
	
	auto view = hof::SceneManager::GetCurrentScene()->GetRegistry().view<hof::TransformComponent, hof::CameraComponent>();
	hof::Entity cam_entity(view.front(), hof::SceneManager::GetCurrentScene().get());
	glm::vec3 position = cam_entity.GetComponent<hof::TransformComponent>().Position;
	ImGui::DragFloat3("Cam Position", &position.x);
	cam_entity.GetComponent<hof::TransformComponent>().Position = position;

	glm::vec3 rotation = cam_entity.GetComponent<hof::TransformComponent>().Rotation;
	ImGui::DragFloat3("Cam Rotation", &rotation.x,0.01f);
	cam_entity.GetComponent<hof::TransformComponent>().Rotation = rotation;
	ImGui::End();
}

void CommonSceneGUILayer::OnEvent([[maybe_unused]] hof::Event& event)
{
	
}

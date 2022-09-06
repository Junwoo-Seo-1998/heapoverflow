/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "ShadowScene.h"


#include "Core/Components/LightComponent.h"
#include "Layer/Shadow/ShadowGUILayer.h"

ShadowScene::ShadowScene()
{
}

ShadowScene::~ShadowScene()
{
}

void ShadowScene::OnLoad()
{
	using namespace hof;
	auto layer = std::make_shared<ShadowGUILayer>();
	m_OverlayLayerStack.push(layer);
	hof::Application::Get().PushOverlay(layer);

	auto cam = CreateEntity();
	cam.GetComponent<hof::TransformComponent>().Position = { 0.f,12.f,50.f };
	auto& cam_comp = cam.AddComponent<hof::CameraComponent>();
	unsigned int width = hof::Application::Get().GetWindow().GetWidth();
	unsigned int height = hof::Application::Get().GetWindow().GetHeight();

	cam_comp.Camera.SetViewportSize(width, height);
	cam_comp.Camera.SetPerspective(glm::radians(45.0f), 0.1f, 1000.f);

	auto material = std::make_shared<Material>(AssetManager::GetShaderManager()->Get("ShadowShader"));

	auto monkey = CreateEntity();
	monkey.AddComponent<MeshRendererComponent>(AssetManager::GetMesh("Monkey"), material,true);
	monkey.GetComponent<TransformComponent>().Position = { 0.f,10.f,0.f };
	monkey.GetComponent<TransformComponent>().Scale = { 5.f, 5.f, 5.f };
	rotating_monkey = monkey;
	
	auto monkey2 = CreateEntity();
	monkey2.AddComponent<MeshRendererComponent>(AssetManager::GetMesh("Monkey"), material, true);
	monkey2.GetComponent<TransformComponent>().Position = { 15.f,10.f,0.f };
	monkey2.GetComponent<TransformComponent>().Scale = { 5.f, 5.f, 5.f };

	auto monkey3 = CreateEntity();
	monkey3.AddComponent<MeshRendererComponent>(AssetManager::GetMesh("Monkey"), material, true);
	monkey3.GetComponent<TransformComponent>().Position = { 20.f,10.f,10.f };
	monkey3.GetComponent<TransformComponent>().Scale = { 5.f, 5.f, 5.f };

	auto cube = CreateEntity();
	cube.AddComponent<MeshRendererComponent>(AssetManager::GetMesh("Cube"), material, true);
	cube.GetComponent<TransformComponent>().Position = { -10.f,10.f,10.f };
	cube.GetComponent<TransformComponent>().Scale = { 3.f, 3.f, 3.f };

	auto cube2 = CreateEntity();
	cube2.AddComponent<MeshRendererComponent>(AssetManager::GetMesh("Cube"), material, true);
	cube2.GetComponent<TransformComponent>().Position = { -20.f,10.f,-10.f };
	cube2.GetComponent<TransformComponent>().Scale = { 3.f, 3.f, 3.f };
	cube2.GetComponent<TransformComponent>().Rotation = { 3.f, 3.f, 3.f };

	auto cube3 = CreateEntity();
	cube3.AddComponent<MeshRendererComponent>(AssetManager::GetMesh("Cube"), material, true);
	cube3.GetComponent<TransformComponent>().Position = { 5.f,20.f,0.f };
	cube3.GetComponent<TransformComponent>().Scale = { 3.f, 3.f, 3.f };
	cube3.GetComponent<TransformComponent>().Rotation = { 0.f, 0.f, 0.f };


	
	auto Ground = CreateEntity();
	Ground.AddComponent<MeshRendererComponent>(AssetManager::GetMesh("Plane"), material, true);
	Ground.GetComponent<hof::TransformComponent>().Position = { 0.f,0.f,0.f };
	Ground.GetComponent<hof::TransformComponent>().Scale = { 45.f,1.f,45.f };

	auto light = CreateEntity();
	light.AddComponent<LightComponent>();
	light.GetComponent<hof::TransformComponent>().Position = { 20.f,20.f,30.f };
	light.GetComponent<hof::TransformComponent>().Rotation = { glm::radians(-45.f),glm::radians(45.f),0.f };

	Renderer::SetClearColor({ 0.2f,0.3f,0.5f,1.0f });
}

void ShadowScene::OnUpdate(float dt)
{
	rotating_monkey.GetComponent<hof::TransformComponent>().Rotation.z += glm::sin(dt);
}

void ShadowScene::OnUnload()
{
	while (m_OverlayLayerStack.empty() == false)
	{
		auto layer = m_OverlayLayerStack.top();
		m_OverlayLayerStack.pop();
		hof::Application::Get().PopOverlay(layer);
	}
}

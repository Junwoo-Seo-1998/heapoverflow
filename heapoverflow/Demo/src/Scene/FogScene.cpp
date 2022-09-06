/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "FogScene.h"
#include "HOF.h"
#include "Layer/Fog/FogGUILayer.h"

FogScene::FogScene()
{
}

FogScene::~FogScene()
{
}

void FogScene::OnLoad()
{
	using namespace hof;

	auto GUILayer = std::make_shared<FogGUILayer>();
	m_OverlayLayerStack.push(GUILayer);
	Application::Get().PushOverlay(GUILayer);
	
	auto cam = CreateEntity();
	cam.GetComponent<TransformComponent>().Position = { 0.f,0.f,50.f };
	auto& cam_comp = cam.AddComponent<CameraComponent>();
	unsigned int width = Application::Get().GetWindow().GetWidth();
	unsigned int height = Application::Get().GetWindow().GetHeight();

	cam_comp.Camera.SetViewportSize(width, height);
	cam_comp.Camera.SetPerspective(glm::radians(45.0f), 0.1f, 1000.f);

	auto material = std::make_shared<Material>(AssetManager::GetShaderManager()->Get("FogShader"));
	
	auto monkey_mid = CreateEntity();
	monkey_mid.AddComponent<MeshRendererComponent>(AssetManager::GetMesh("Monkey"), material);
	monkey_mid.GetComponent<TransformComponent>().Scale = { 5.f, 5.f, 5.f };


	for(int i=1; i<=10; ++i)
	{
		auto monkey_left = CreateEntity();
		monkey_left.AddComponent<MeshRendererComponent>(AssetManager::GetMesh("Monkey"), material);
		monkey_left.GetComponent<TransformComponent>().Position = { -10.f * i,0.f,-10.f * i };
		monkey_left.GetComponent<TransformComponent>().Scale = { 5.f, 5.f, 5.f };


		auto monkey_right = CreateEntity();
		monkey_right.AddComponent<MeshRendererComponent>(AssetManager::GetMesh("Monkey"), material);
		monkey_right.GetComponent<TransformComponent>().Position = { 10.f * i,0.f,-10.f * i };
		monkey_right.GetComponent<TransformComponent>().Scale = { 5.f, 5.f, 5.f };
	}
	

	Renderer::SetClearColor({ 0.796875f, 0.796875f, 0.796875f,1.0f });
}

void FogScene::OnUpdate([[maybe_unused]] float dt)
{
}

void FogScene::OnUnload()
{
	while (m_OverlayLayerStack.empty() == false)
	{
		auto layer = m_OverlayLayerStack.top();
		m_OverlayLayerStack.pop();
		hof::Application::Get().PopOverlay(layer);
	}
}

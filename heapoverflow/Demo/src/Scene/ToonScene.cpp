/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "ToonScene.h"
#include <iostream>
#include "Core/SceneCamera.h"

#include "HOF.h"
#include "Layer/Toon/ToonGUILayer.h"

ToonScene::ToonScene()
	:Scene(), m_OverlayLayerStack()
{
}

ToonScene::~ToonScene()
{
}

void ToonScene::OnLoad()
{
	using namespace hof;
	auto GUILayer = std::make_shared<ToonGUILayer>();
	m_OverlayLayerStack.push(GUILayer);
	Application::Get().PushOverlay(GUILayer);
	
	auto cam = CreateEntity();
	cam.GetComponent<TransformComponent>().Position = { 0.f,0.f,50.f };
	auto& cam_comp=cam.AddComponent<CameraComponent>();
	unsigned int width=Application::Get().GetWindow().GetWidth();
	unsigned int height=Application::Get().GetWindow().GetHeight();
	
	cam_comp.Camera.SetViewportSize(width, height);
	cam_comp.Camera.SetPerspective(glm::radians(45.0f), 0.1f, 1000.f);
	
	auto material = std::make_shared<Material>(AssetManager::GetShaderManager()->Get("ToonShader"));

	auto monkey = CreateEntity();
	monkey.AddComponent<MeshRendererComponent>(AssetManager::GetMesh("Monkey"), material);
	monkey.GetComponent<TransformComponent>().Scale={ 10.f, 10.f, 10.f };

	Renderer::SetClearColor({ 0.2f,0.3f,0.5f,1.0f });
}

void ToonScene::OnUpdate([[maybe_unused]]float dt)
{

}

void ToonScene::OnUnload()
{
	while (m_OverlayLayerStack.empty() == false)
	{
		auto layer = m_OverlayLayerStack.top();
		m_OverlayLayerStack.pop();
		hof::Application::Get().PopOverlay(layer);
	}
}

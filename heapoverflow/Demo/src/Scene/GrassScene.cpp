/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "GrassScene.h"

#include "Layer/Common/CommonSceneGUILayer.h"
#include "Layer/Grass/GrassGUILayer.h"


GrassScene::GrassScene()
{
}

GrassScene::~GrassScene()
{
}

void GrassScene::OnLoad()
{
	auto layer = std::make_shared<GrassGUILayer>();
	m_OverlayLayerStack.push(layer);
	hof::Application::Get().PushOverlay(layer);
	
	auto cam = CreateEntity();
	cam.GetComponent<hof::TransformComponent>().Position = { 0.f,12.f,50.f };
	auto& cam_comp = cam.AddComponent<hof::CameraComponent>();
	unsigned int width = hof::Application::Get().GetWindow().GetWidth();
	unsigned int height = hof::Application::Get().GetWindow().GetHeight();

	cam_comp.Camera.SetViewportSize(width, height);
	cam_comp.Camera.SetPerspective(glm::radians(45.0f), 0.1f, 1000.f);

	auto material = std::make_shared<hof::Material>(hof::AssetManager::GetShaderManager()->Get("GrassShader"));
	auto default_material = std::make_shared<hof::Material>(hof::AssetManager::GetShaderManager()->Get("GrassGroundShader"));
	auto ground = CreateEntity();
	ground.GetComponent<hof::TransformComponent>().Position = { 0.f,0.f,0.f };
	ground.GetComponent<hof::TransformComponent>().Scale = { 20.f,1.f,20.f };
	ground.AddComponent<hof::MeshRendererComponent>(hof::AssetManager::GetMesh("Plane"), material).materials.push_back(default_material);

	hof::Renderer::SetClearColor({ 0.2f,0.3f,0.5f,1.0f });
}

void GrassScene::OnUpdate([[maybe_unused]] float dt)
{

}

void GrassScene::OnUnload()
{
	while (m_OverlayLayerStack.empty() == false)
	{
		auto layer = m_OverlayLayerStack.top();
		m_OverlayLayerStack.pop();
		hof::Application::Get().PopOverlay(layer);
	}
}

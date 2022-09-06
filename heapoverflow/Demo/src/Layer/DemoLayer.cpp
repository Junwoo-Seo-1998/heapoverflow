/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "DemoLayer.h"

#include <iostream>

#include "imgui.h"

#include <glm/glm.hpp>
#include "glm/gtx/quaternion.hpp"

#include "HOF.h"
#include "Core/Components/LightComponent.h"

DemoLayer::DemoLayer()
{
}

void DemoLayer::OnAttach()
{
	using namespace hof;
	hof::FrameBufferSpecification spec;
	spec.Formats = { FrameBufferFormat::RGBA,FrameBufferFormat::Depth };
	spec.Width = 1600;
	spec.Height = 900;
}

void DemoLayer::OnDetach()
{
}

void DemoLayer::OnUpdate([[maybe_unused]] float dt)
{
	using namespace hof; 
	auto view = SceneManager::GetCurrentScene()->GetRegistry().view<TransformComponent, CameraComponent>();
	Entity cam_entity(view.front(), SceneManager::GetCurrentScene().get());


	auto Renderables = SceneManager::GetCurrentScene()->GetRegistry().view<TransformComponent, MeshRendererComponent>();

	auto lights = SceneManager::GetCurrentScene()->GetRegistry().view<TransformComponent, LightComponent>();
	for (auto& entt:lights)
	{
		auto [TransformComp, LightComp] = lights.get<TransformComponent, LightComponent>(entt);
		LightComp.m_ShadowMap->Bind();
		Renderer::ClearScreen();
		Renderer::DrawBegin(LightComp.m_Light.GetLightProjection() * glm::inverse(TransformComp.GetTransform()));
		for (auto& entity : Renderables)
		{
			auto [entt_TransformComp, MeshRendererComp] = Renderables.get<TransformComponent, MeshRendererComponent>(entity);

			Renderer::DrawShadow(MeshRendererComp.mesh, entt_TransformComp.GetTransform());
		}
		Renderer::DrawEnd();
		LightComp.m_ShadowMap->Unbind();
	}

	
	Renderer::ClearScreen();
	Renderer::DrawBegin(cam_entity);
	//draw all rendererable 
	for (auto& entity:Renderables)
	{
		auto [TransformComp, MeshRendererComp] = Renderables.get<TransformComponent, MeshRendererComponent>(entity);

		if (MeshRendererComp.cast_shadow == false)
		{
			Renderer::DrawMeshWithMaterials(MeshRendererComp.materials, MeshRendererComp.mesh, TransformComp.GetTransform());
		}
	}

	for (auto& entt : lights)
	{
		auto [LightTransformComp, LightComp] = lights.get<TransformComponent, LightComponent>(entt);
		for (auto& entity : Renderables)
		{
			auto [TransformComp, MeshRendererComp] = Renderables.get<TransformComponent, MeshRendererComponent>(entity);

			if (MeshRendererComp.cast_shadow == true)
			{
				Renderer::DrawMeshWithMaterialAndShadow(MeshRendererComp.materials.front(), MeshRendererComp.mesh, TransformComp.GetTransform(), LightTransformComp, LightComp);
			}
		}
	}
	Renderer::DrawEnd();
}

void DemoLayer::OnGuiRender()
{
}

void DemoLayer::OnEvent(hof::Event& event)
{
	hof::EventDispatcher dispatcher(event);

	dispatcher.Dispatch<hof::WindowResizeEvent>([](hof::WindowResizeEvent& event)->bool
	{
		auto view = hof::SceneManager::GetCurrentScene()->GetRegistry().view<hof::TransformComponent, hof::CameraComponent>();
		hof::Entity cam_entt(view.front(), hof::SceneManager::GetCurrentScene().get());
		auto& cam=cam_entt.GetComponent<hof::CameraComponent>();
		auto [width, height] = event.GetWidthAndHeight();
		cam.Camera.SetViewportSize(width, height);
		return true;
	});
}

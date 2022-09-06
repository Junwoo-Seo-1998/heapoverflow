/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "Scene.h"
#include "Core/Entity/Entity.h"
#include "Core/Components/TransformComponent.h"
namespace hof
{
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity()
	{
		Entity entity{ m_Registry.create(),this };
		entity.AddComponent<TransformComponent>();
		return entity;
	}

	void Scene::OnLoad()
	{
	}

	void Scene::OnUpdate([[maybe_unused]] float dt)
	{
	}

	void Scene::OnUnload()
	{
	}

	entt::registry& Scene::GetRegistry()
	{
		return m_Registry;
	}
}

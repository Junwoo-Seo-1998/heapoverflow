/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include "entt.hpp"
#include "Core/Scene/Scene.h"
namespace hof
{
	class Scene;
	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity entity_handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename Comp_type, typename... Args>
		Comp_type& AddComponent(Args&&... args);

		template<typename Comp_type>
		bool HasComponent();

		template <typename Comp_type>
		Comp_type& GetComponent();

		template <typename Comp_type>
		void RemoveComponent();
		
	private:
		entt::entity m_EntityHandle = entt::null;
		//for easy adding components
		Scene* m_Scene = nullptr;
	};

	template <typename Comp_type, typename ... Args>
	Comp_type& Entity::AddComponent(Args&&... args)
	{
		//static_assert(!HasComponent<Comp_type>(), "comp already exist!");
		Comp_type& comp = m_Scene->m_Registry.emplace<Comp_type>(m_EntityHandle, std::forward<Args>(args)...);
		return comp;
	}

	template <typename Comp_type>
	bool Entity::HasComponent()
	{
		return m_Scene->m_Registry.any_of<Comp_type>(m_EntityHandle);
	}

	template <typename Comp_type>
	Comp_type& Entity::GetComponent()
	{
		return m_Scene->m_Registry.get<Comp_type>(m_EntityHandle);
	}

	template <typename Comp_type>
	void Entity::RemoveComponent()
	{
		m_Scene->m_Registry.remove<Comp_type>(m_EntityHandle);
	}
}

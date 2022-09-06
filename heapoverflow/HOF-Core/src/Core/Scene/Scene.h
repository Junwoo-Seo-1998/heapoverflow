/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include "entt.hpp"

namespace hof
{
	class Entity;
	
	class Scene
	{
		friend class Entity;
	public:
		Scene();
		virtual ~Scene();

		Entity CreateEntity();
		virtual void OnLoad();
		virtual void OnUpdate([[maybe_unused]] float dt);
		virtual void OnUnload();
		entt::registry& GetRegistry();
	protected:
		entt::registry m_Registry;

	};
}

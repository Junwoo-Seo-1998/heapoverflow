/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "Entity.h"
#include "Core/Scene/Scene.h"


namespace hof
{
	Entity::Entity(entt::entity entity_handle, Scene* scene)
		:m_EntityHandle(entity_handle), m_Scene(scene)
	{
	}
}

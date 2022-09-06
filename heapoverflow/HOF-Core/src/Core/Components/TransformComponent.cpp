/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "TransformComponent.h"

#include "glm/gtx/quaternion.hpp"

glm::mat4 hof::TransformComponent::GetTransform() const
{
	return glm::translate(glm::mat4(1.0f), Position)
		* glm::toMat4(glm::quat(Rotation))
		* glm::scale(glm::mat4(1.0f), Scale);
}

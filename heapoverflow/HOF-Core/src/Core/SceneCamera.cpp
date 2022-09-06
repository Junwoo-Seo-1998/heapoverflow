/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "SceneCamera.h"

#include "glm/ext/matrix_clip_space.hpp"

namespace hof
{
	SceneCamera::SceneCamera()
	{
		ReCompute();
	}

	void SceneCamera::SetPerspective(float verticalFOV, float near, float far)
	{
		m_PerspectiveFOV = verticalFOV;
		m_PerspectiveNear = near;
		m_PerspectiveFar = far;
		ReCompute();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0)
			return;
		m_AspectRatio = static_cast<float>(width) / static_cast<float>(height);
		ReCompute();
	}

	void SceneCamera::ReCompute()
	{
		m_Projection = glm::perspective(m_PerspectiveFOV, m_AspectRatio, m_PerspectiveNear, m_PerspectiveFar);
	}
}

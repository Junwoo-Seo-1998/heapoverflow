/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "Light.h"

namespace hof
{
	DirectionalLight::DirectionalLight()
	{
	}

	DirectionalLight::DirectionalLight(const glm::vec2& left_bot, const glm::vec2& right_top, float near, float far)
		:m_LeftBottom(left_bot), m_RightTop(right_top), m_Near(near), m_Far(far)
	{
		ReCompute();
	}

	const glm::mat4& DirectionalLight::GetLightProjection() const
	{
		return m_LightProjection;
	}

	float DirectionalLight::GetNear() const
	{
		return m_Near;
	}

	void DirectionalLight::SetNear(float near)
	{
		m_Near = near;
		ReCompute();
	}

	float DirectionalLight::GetFar() const
	{
		return m_Far;
	}

	void DirectionalLight::SetFar(float far)
	{
		m_Far = far;
		ReCompute();
	}

	void DirectionalLight::ReCompute()
	{
		m_LightProjection = glm::ortho(m_LeftBottom.x, m_RightTop.x, m_LeftBottom.y, m_RightTop.y, m_Near, m_Far);
	}
}

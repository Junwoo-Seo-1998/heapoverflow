/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include "glm/glm.hpp"
#include "glm/ext/matrix_clip_space.hpp"

namespace hof
{
	class DirectionalLight
	{
	public:
		DirectionalLight();
		DirectionalLight(const glm::vec2& left_bot, const glm::vec2& right_top, float near, float far);
		const glm::mat4& GetLightProjection() const;
		float GetNear() const;
		void SetNear(float near);
		float GetFar() const;
		void SetFar(float far);
	private:
		void ReCompute();
		glm::mat4 m_LightProjection = glm::ortho(-90.f, 90.f, -90.f, 90.f, 1.f, 100.f);

		glm::vec2 m_LeftBottom = { -90.f,-90.f };
		glm::vec2 m_RightTop = { 90.f,90.f };

		float m_Near = 1.f;
		float m_Far = 100.f;
		
	};
}

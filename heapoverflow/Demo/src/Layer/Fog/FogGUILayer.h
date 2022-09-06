/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include "HOF.h"

class FogGUILayer : public hof::Layer
{
public:
	FogGUILayer();
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate([[maybe_unused]] float dt) override;
	virtual void OnGuiRender() override;
	virtual void OnEvent(hof::Event& event) override;
private:
	glm::vec4 m_FogColor{ 0.796875f, 0.796875f, 0.796875f,1.0f };
	float m_fog_max_dist = 200.f;
	float m_fog_min_dist = 1.f;
};
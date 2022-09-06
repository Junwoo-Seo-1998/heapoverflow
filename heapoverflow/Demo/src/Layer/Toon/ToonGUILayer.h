/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include "HOF.h"

class ToonGUILayer : public hof::Layer
{
public:
	ToonGUILayer();
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnGuiRender() override;
	virtual void OnEvent(hof::Event& event) override;
private:
	glm::vec3 color = { 0.7255f, 0.7216f, 0.4275f };
};
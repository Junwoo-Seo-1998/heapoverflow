/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include "HOF.h"

class GrassGUILayer : public hof::Layer
{
public:
	GrassGUILayer();
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnGuiRender() override;
	virtual void OnEvent([[maybe_unused]] hof::Event& event) override;
private:
	float Inner = 1.f;
	float Outer = 1.f;
	float width = 10.f;
	float height = 10.f;
	float rotate = 20.f;
};
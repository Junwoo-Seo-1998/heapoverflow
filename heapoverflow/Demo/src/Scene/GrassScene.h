/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include "HOF.h"
#include <stack>

class GrassScene :public hof::Scene
{
public:
	GrassScene();
	virtual ~GrassScene() override;
	virtual void OnLoad() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnUnload() override;

private:
	std::stack<std::shared_ptr<hof::Layer>> m_OverlayLayerStack;
};
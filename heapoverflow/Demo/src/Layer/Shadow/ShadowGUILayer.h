/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include "HOF.h"

class ShadowGUILayer : public hof::Layer
{
public:
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate(float dt) override;
	virtual void OnGuiRender() override;
	virtual void OnEvent([[maybe_unused]] hof::Event& event) override;
private:
	std::shared_ptr<hof::FrameBuffer> DepthRenderingFrameBuffer;
	float max_bias = 0.05f;
	float min_bias = 0.005f;
};
/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include "HOF.h"
class DemoLayer :public hof::Layer
{
public:
	DemoLayer();
	virtual void OnAttach() override;
	virtual void OnDetach() override;
	virtual void OnUpdate([[maybe_unused]] float dt) override;
	virtual void OnGuiRender() override;
	virtual void OnEvent(hof::Event& event) override;
private:
	std::shared_ptr<hof::VertexArray> m_VertexArray;
	glm::vec3 position{ 0,0,-1.f };
	glm::vec3 rotation{ 0, 0, 0 };

};
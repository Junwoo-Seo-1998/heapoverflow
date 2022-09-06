/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "LightComponent.h"
#include "Core/Application.h"
namespace hof
{
	LightComponent::LightComponent()
		:m_Light()
	{
		auto [width, height] = hof::Application::Get().GetWindow().GetWidthHeight();
		FrameBufferSpecification spec;
		spec.Width = width;
		spec.Height = height;
		spec.Formats = { FrameBufferFormat::Depth };
		m_ShadowMap = std::make_shared<FrameBuffer>(spec);
	}
}

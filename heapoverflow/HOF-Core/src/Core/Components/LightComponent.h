/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include <memory>


#include "Core/FrameBuffer.h"
#include "Core/Graphics/Light.h"
namespace hof
{
	//just directional light
	//basically having a z direction vector and follows transform rotation
	struct LightComponent
	{
		LightComponent();
		DirectionalLight m_Light;
		std::shared_ptr<FrameBuffer> m_ShadowMap;
	};
}

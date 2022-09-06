/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once

namespace hof
{
	class Event;
	class Layer
	{
	public:
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate([[maybe_unused]]float dt) {}
		virtual void OnGuiRender(){}
		virtual void OnEvent([[maybe_unused]] Event& event) {}
	};
}

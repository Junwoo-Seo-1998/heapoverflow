/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include "Utils/KeyCodes.h"
#include "Utils/MouseCodes.h"
namespace hof
{
	class Application;

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode keycode);
		static bool IsMouseButtonPressed(MouseCode button);
		static std::pair<float, float> GetMousePosition();
		static std::pair<float, float> GetLastMousePosition();
		static std::pair<float, float> GetRelativeMousePositionChange();
		static float GetMouseX();
		static float GetMouseY();
	private:
		static void SetLastMousePosition();
		friend Application;
	};
}

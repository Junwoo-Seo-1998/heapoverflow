/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "Input.h"


#include "Application.h"
#include "GLFW/glfw3.h"

namespace hof
{
	static double last_x_pos = 0.0, last_y_pos = 0.0;
	
	bool Input::IsKeyPressed(KeyCode keycode)
	{
		auto window = static_cast<GLFWwindow*> (Application::Get().GetWindow().GetGLFWWindow());
		auto state = glfwGetKey(window, static_cast<int>(keycode));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		auto window = static_cast<GLFWwindow*> (Application::Get().GetWindow().GetGLFWWindow());
		auto state = glfwGetMouseButton(window, static_cast<int>(button));
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		auto window = static_cast<GLFWwindow*> (Application::Get().GetWindow().GetGLFWWindow());
		double x_pos = 0.0, y_pos = 0.0;
		glfwGetCursorPos(window, &x_pos, &y_pos);

		return  { static_cast<float>(x_pos),static_cast<float>(y_pos) };
	}

	std::pair<float, float> Input::GetLastMousePosition()
	{
		return  { static_cast<float>(last_x_pos),static_cast<float>(last_y_pos) };
	}

	std::pair<float, float> Input::GetRelativeMousePositionChange()
	{
		const auto [x, y] = GetMousePosition();
		return { x - static_cast<float>(last_x_pos),y - static_cast<float>(last_y_pos) };
	}

	float Input::GetMouseX()
	{
		auto [x, y] = GetMousePosition();

		return x;
	}

	float Input::GetMouseY()
	{
		auto [x, y] = GetMousePosition();

		return y;
	}

	void Input::SetLastMousePosition()
	{
		auto window = static_cast<GLFWwindow*> (Application::Get().GetWindow().GetGLFWWindow());
		glfwGetCursorPos(window, &last_x_pos, &last_y_pos);
	}
}

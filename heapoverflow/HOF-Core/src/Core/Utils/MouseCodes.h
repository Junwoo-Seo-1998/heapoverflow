/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include <ostream>
//enums From glfw3.h however for easy use i made my engine one that converts glfw api to mine
namespace hof
{
	typedef enum class MouseCode : unsigned short
	{
		Button0 = 0,
		Button1 = 1,
		Button2 = 2,
		Button3 = 3,
		Button4 = 4,
		Button5 = 5,
		Button6 = 6,
		Button7 = 7,

		ButtonLast = Button7,
		ButtonLeft = Button0,
		ButtonRight = Button1,
		ButtonMiddle = Button2
	} Mouse;

	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int>(mouseCode);
		return os;
	}
}

#define MOUSE_BUTTON_0      ::hof::Mouse::Button0
#define MOUSE_BUTTON_1      ::hof::Mouse::Button1
#define MOUSE_BUTTON_2      ::hof::Mouse::Button2
#define MOUSE_BUTTON_3      ::hof::Mouse::Button3
#define MOUSE_BUTTON_4      ::hof::Mouse::Button4
#define MOUSE_BUTTON_5      ::hof::Mouse::Button5
#define MOUSE_BUTTON_6      ::hof::Mouse::Button6
#define MOUSE_BUTTON_7      ::hof::Mouse::Button7
#define MOUSE_BUTTON_LAST   ::hof::Mouse::ButtonLast
#define MOUSE_BUTTON_LEFT   ::hof::Mouse::ButtonLeft
#define MOUSE_BUTTON_RIGHT  ::hof::Mouse::ButtonRight
#define MOUSE_BUTTON_MIDDLE ::hof::Mouse::ButtonMiddle

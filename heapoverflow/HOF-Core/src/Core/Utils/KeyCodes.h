/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include <iostream>
//enums From glfw3.h however for easy use i made my engine one that converts glfw api to mine
namespace hof
{
	typedef enum class KeyCode : unsigned short
	{
		// From glfw3.h
		Space = 32,
		Apostrophe = 39, /* ' */
		Comma = 44, /* , */
		Minus = 45, /* - */
		Period = 46, /* . */
		Slash = 47, /* / */

		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */

		Semicolon = 59, /* ; */
		Equal = 61, /* = */

		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,

		LeftBracket = 91,  /* [ */
		Backslash = 92,  /* \ */
		RightBracket = 93,  /* ] */
		GraveAccent = 96,  /* ` */

		World1 = 161, /* non-US #1 */
		World2 = 162, /* non-US #2 */

		/* Function keys */
		Escape = 256,
		Enter = 257,
		Tab = 258,
		Backspace = 259,
		Insert = 260,
		Delete = 261,
		Right = 262,
		Left = 263,
		Down = 264,
		Up = 265,
		PageUp = 266,
		PageDown = 267,
		Home = 268,
		End = 269,
		CapsLock = 280,
		ScrollLock = 281,
		NumLock = 282,
		PrintScreen = 283,
		Pause = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,

		/* Keypad */
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KPDecimal = 330,
		KPDivide = 331,
		KPMultiply = 332,
		KPSubtract = 333,
		KPAdd = 334,
		KPEnter = 335,
		KPEqual = 336,

		LeftShift = 340,
		LeftControl = 341,
		LeftAlt = 342,
		LeftSuper = 343,
		RightShift = 344,
		RightControl = 345,
		RightAlt = 346,
		RightSuper = 347,
		Menu = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int>(keyCode);
		return os;
	}
}

// From glfw3.h
#define KEY_SPACE           ::hof::KeyCode::Space
#define KEY_APOSTROPHE      ::hof::KeyCode::Apostrophe    /* ' */
#define KEY_COMMA           ::hof::KeyCode::Comma         /* , */
#define KEY_MINUS           ::hof::KeyCode::Minus         /* - */
#define KEY_PERIOD          ::hof::KeyCode::Period        /* . */
#define KEY_SLASH           ::hof::KeyCode::Slash         /* / */
#define KEY_0               ::hof::KeyCode::D0
#define KEY_1               ::hof::KeyCode::D1
#define KEY_2               ::hof::KeyCode::D2
#define KEY_3               ::hof::KeyCode::D3
#define KEY_4               ::hof::KeyCode::D4
#define KEY_5               ::hof::KeyCode::D5
#define KEY_6               ::hof::KeyCode::D6
#define KEY_7               ::hof::KeyCode::D7
#define KEY_8               ::hof::KeyCode::D8
#define KEY_9               ::hof::KeyCode::D9
#define KEY_SEMICOLON       ::hof::KeyCode::Semicolon     /* ; */
#define KEY_EQUAL           ::hof::KeyCode::Equal         /* = */
#define KEY_A               ::hof::KeyCode::A
#define KEY_B               ::hof::KeyCode::B
#define KEY_C               ::hof::KeyCode::C
#define KEY_D               ::hof::KeyCode::D
#define KEY_E               ::hof::KeyCode::E
#define KEY_F               ::hof::KeyCode::F
#define KEY_G               ::hof::KeyCode::G
#define KEY_H               ::hof::KeyCode::H
#define KEY_I               ::hof::KeyCode::I
#define KEY_J               ::hof::KeyCode::J
#define KEY_K               ::hof::KeyCode::K
#define KEY_L               ::hof::KeyCode::L
#define KEY_M               ::hof::KeyCode::M
#define KEY_N               ::hof::KeyCode::N
#define KEY_O               ::hof::KeyCode::O
#define KEY_P               ::hof::KeyCode::P
#define KEY_Q               ::hof::KeyCode::Q
#define KEY_R               ::hof::KeyCode::R
#define KEY_S               ::hof::KeyCode::S
#define KEY_T               ::hof::KeyCode::T
#define KEY_U               ::hof::KeyCode::U
#define KEY_V               ::hof::KeyCode::V
#define KEY_W               ::hof::KeyCode::W
#define KEY_X               ::hof::KeyCode::X
#define KEY_Y               ::hof::KeyCode::Y
#define KEY_Z               ::hof::KeyCode::Z
#define KEY_LEFT_BRACKET    ::hof::KeyCode::LeftBracket   /* [ */
#define KEY_BACKSLASH       ::hof::KeyCode::Backslash     /* \ */
#define KEY_RIGHT_BRACKET   ::hof::KeyCode::RightBracket  /* ] */
#define KEY_GRAVE_ACCENT    ::hof::KeyCode::GraveAccent   /* ` */
#define KEY_WORLD_1         ::hof::KeyCode::World1        /* non-US #1 */
#define KEY_WORLD_2         ::hof::KeyCode::World2        /* non-US #2 */

/* Function keys */
#define KEY_ESCAPE          ::hof::KeyCode::Escape
#define KEY_ENTER           ::hof::KeyCode::Enter
#define KEY_TAB             ::hof::KeyCode::Tab
#define KEY_BACKSPACE       ::hof::KeyCode::Backspace
#define KEY_INSERT          ::hof::KeyCode::Insert
#define KEY_DELETE          ::hof::KeyCode::Delete
#define KEY_RIGHT           ::hof::KeyCode::Right
#define KEY_LEFT            ::hof::KeyCode::Left
#define KEY_DOWN            ::hof::KeyCode::Down
#define KEY_UP              ::hof::KeyCode::Up
#define KEY_PAGE_UP         ::hof::KeyCode::PageUp
#define KEY_PAGE_DOWN       ::hof::KeyCode::PageDown
#define KEY_HOME            ::hof::KeyCode::Home
#define KEY_END             ::hof::KeyCode::End
#define KEY_CAPS_LOCK       ::hof::KeyCode::CapsLock
#define KEY_SCROLL_LOCK     ::hof::KeyCode::ScrollLock
#define KEY_NUM_LOCK        ::hof::KeyCode::NumLock
#define KEY_PRINT_SCREEN    ::hof::KeyCode::PrintScreen
#define KEY_PAUSE           ::hof::KeyCode::Pause
#define KEY_F1              ::hof::KeyCode::F1
#define KEY_F2              ::hof::KeyCode::F2
#define KEY_F3              ::hof::KeyCode::F3
#define KEY_F4              ::hof::KeyCode::F4
#define KEY_F5              ::hof::KeyCode::F5
#define KEY_F6              ::hof::KeyCode::F6
#define KEY_F7              ::hof::KeyCode::F7
#define KEY_F8              ::hof::KeyCode::F8
#define KEY_F9              ::hof::KeyCode::F9
#define KEY_F10             ::hof::KeyCode::F10
#define KEY_F11             ::hof::KeyCode::F11
#define KEY_F12             ::hof::KeyCode::F12
#define KEY_F13             ::hof::KeyCode::F13
#define KEY_F14             ::hof::KeyCode::F14
#define KEY_F15             ::hof::KeyCode::F15
#define KEY_F16             ::hof::KeyCode::F16
#define KEY_F17             ::hof::KeyCode::F17
#define KEY_F18             ::hof::KeyCode::F18
#define KEY_F19             ::hof::KeyCode::F19
#define KEY_F20             ::hof::KeyCode::F20
#define KEY_F21             ::hof::KeyCode::F21
#define KEY_F22             ::hof::KeyCode::F22
#define KEY_F23             ::hof::KeyCode::F23
#define KEY_F24             ::hof::KeyCode::F24
#define KEY_F25             ::hof::KeyCode::F25

/* Keypad */
#define KEY_KP_0            ::hof::KeyCode::KP0
#define KEY_KP_1            ::hof::KeyCode::KP1
#define KEY_KP_2            ::hof::KeyCode::KP2
#define KEY_KP_3            ::hof::KeyCode::KP3
#define KEY_KP_4            ::hof::KeyCode::KP4
#define KEY_KP_5            ::hof::KeyCode::KP5
#define KEY_KP_6            ::hof::KeyCode::KP6
#define KEY_KP_7            ::hof::KeyCode::KP7
#define KEY_KP_8            ::hof::KeyCode::KP8
#define KEY_KP_9            ::hof::KeyCode::KP9
#define KEY_KP_DECIMAL      ::hof::KeyCode::KPDecimal
#define KEY_KP_DIVIDE       ::hof::KeyCode::KPDivide
#define KEY_KP_MULTIPLY     ::hof::KeyCode::KPMultiply
#define KEY_KP_SUBTRACT     ::hof::KeyCode::KPSubtract
#define KEY_KP_ADD          ::hof::KeyCode::KPAdd
#define KEY_KP_ENTER        ::hof::KeyCode::KPEnter
#define KEY_KP_EQUAL        ::hof::KeyCode::KPEqual

#define KEY_LEFT_SHIFT      ::hof::KeyCode::LeftShift
#define KEY_LEFT_CONTROL    ::hof::KeyCode::LeftControl
#define KEY_LEFT_ALT        ::hof::KeyCode::LeftAlt
#define KEY_LEFT_SUPER      ::hof::KeyCode::LeftSuper
#define KEY_RIGHT_SHIFT     ::hof::KeyCode::RightShift
#define KEY_RIGHT_CONTROL   ::hof::KeyCode::RightControl
#define KEY_RIGHT_ALT       ::hof::KeyCode::RightAlt
#define KEY_RIGHT_SUPER     ::hof::KeyCode::RightSuper
#define KEY_MENU            ::hof::KeyCode::Menu

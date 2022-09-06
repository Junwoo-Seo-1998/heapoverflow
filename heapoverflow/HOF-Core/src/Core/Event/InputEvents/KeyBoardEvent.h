/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include "Core/Event/Event.h"
#include "Core/Utils/KeyCodes.h"

namespace hof
{
	class KeyBoardEvent :public hof::Event
	{
	public:
		EVENT_CATEGORY(EventCategory::KeyBoardEvent);
		hof::KeyCode GetKeyCode() const;
		KeyBoardEvent(KeyCode keycode)
			: m_KeyCode(keycode) {}
		hof::KeyCode m_KeyCode;
	};


	class KeyBoardPressedEvent :public KeyBoardEvent
	{
	public:
		KeyBoardPressedEvent(hof::KeyCode keycode, int repeatCount)
			:KeyBoardEvent(keycode), m_RepeatCount(repeatCount) {}
		EVENT_TYPE(EventType::KeyPressed);
		int GetRepeatCount() const;
		virtual std::string GetEventNameString() const override;;
	private:
		int m_RepeatCount;
	};
}
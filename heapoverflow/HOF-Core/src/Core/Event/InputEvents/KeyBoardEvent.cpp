/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "KeyBoardEvent.h"
#include <sstream>

namespace hof
{
	KeyCode KeyBoardEvent::GetKeyCode() const
	{
		return m_KeyCode;
	}

	int KeyBoardPressedEvent::GetRepeatCount() const
	{
		return m_RepeatCount;
	}

	std::string KeyBoardPressedEvent::GetEventNameString() const
	{
		std::stringstream ss;
		ss << GetEventName() << " : KeyCode - " << m_KeyCode << " Repeats - " << m_RepeatCount << std::endl;
		return ss.str();
	}
}
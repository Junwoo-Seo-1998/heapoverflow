/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "Event.h"

namespace hof
{
	std::string Event::GetEventNameString() const
	{
		return GetEventName();
	}

	bool Event::IsInCategory(EventCategory category)
	{
		return GetCategory() & static_cast<int>(category);
	}

	EventDispatcher::EventDispatcher(Event& event)
		:m_Event(event)
	{}

	
}

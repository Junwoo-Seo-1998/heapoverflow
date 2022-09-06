/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include "Event.h"

namespace hof
{
	template <typename T>
	bool EventDispatcher::Dispatch(EventFunction<T> function)
	{
		if(m_Event.GetEventType()==T::GetStaticType())
		{
			m_Event.m_Handled = function(*(T*)&m_Event);
			return true;
		}
		return false;
	}
}
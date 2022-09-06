/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#include "ApplicationEvent.h"
#include <sstream>
namespace hof
{
	WindowResizeEvent::WindowResizeEvent(unsigned width, unsigned height)
		:m_Width(width), m_Height(height)
	{
	}

	WindowResizeEvent::~WindowResizeEvent()
	{
	}

	std::string WindowResizeEvent::GetEventNameString() const
	{
		std::stringstream ss;
		ss << GetEventName() << "-" << "Event: " << m_Width << ", " << m_Height;
		return ss.str();
	}

	unsigned WindowResizeEvent::GetWidth() const
	{
		return m_Width;
	}

	unsigned WindowResizeEvent::GetHeight() const
	{
		return m_Height;
	}

	std::tuple<unsigned, unsigned> WindowResizeEvent::GetWidthAndHeight() const
	{
		return std::tuple<unsigned, unsigned>(m_Width, m_Height);
	}
}

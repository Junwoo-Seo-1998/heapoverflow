/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include "../Event.h"

namespace hof
{
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}
		EVENT_TYPE(EventType::WindowClose);
		EVENT_CATEGORY(EventCategory::ApplicationEvent);
	};

	
	class WindowResizeEvent : public Event
	{
	public:
		EVENT_TYPE(EventType::WindowResize);
		EVENT_CATEGORY(EventCategory::ApplicationEvent);
		WindowResizeEvent(unsigned int width, unsigned int height);
		virtual ~WindowResizeEvent() override;
		virtual std::string GetEventNameString() const override;

		unsigned int GetWidth() const;
		unsigned int GetHeight() const;

		std::tuple<unsigned, unsigned> GetWidthAndHeight() const;
	private:
		unsigned int m_Width, m_Height;
	};
}

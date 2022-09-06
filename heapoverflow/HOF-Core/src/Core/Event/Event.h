/*--------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project: CS250
Author: Junwoo Seo
-----------------------------------------------------------------*/
#pragma once
#include <functional>
#include "Core/Utils/Utils.h"
namespace hof
{
	enum class EventType : int
	{
		None=0,
		WindowClose,WindowResize,
		KeyPressed,
		KeyReleased,
	};
	
	enum class EventCategory : int
	{
		None = 0,
		ApplicationEvent = BIT(0),
		KeyBoardEvent=BIT(1),
	};
	
	class EventDispatcher;
	
	class Event
	{
		friend  EventDispatcher;
	public:
		virtual ~Event() = default;
		virtual const char* GetEventName() const = 0;
		virtual EventType GetEventType() const = 0;
		virtual int GetCategory() const = 0;

		//debug purpose 
		virtual std::string GetEventNameString() const;

		bool IsInCategory(EventCategory category);

		bool m_Handled = false;
	};
	
	class EventDispatcher
	{
		template<typename T>
		using EventFunction = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event);
		template<typename T>
		bool Dispatch(EventFunction<T> function);

	private:
		Event& m_Event;
	};

}

#define EVENT_TYPE(type)			static EventType GetStaticType(){ return type; }\
									virtual EventType GetEventType() const override { return GetStaticType(); }\
									virtual const char* GetEventName() const override { return #type; };
#define EVENT_CATEGORY(category)	virtual int GetCategory() const override { return static_cast<int>(category); }

#define BIND_EVENT_FUNCTION(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }
#include "Event.hpp"
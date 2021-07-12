#pragma once

#include <functional>
#include <ostream>

#include "Core/Core.h"

enum class EventType
{
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	AppTick, AppUpdate, AppRender,
	KeyPressed, KeyReleased,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum EventCategory
{
	None = 0,
	EventCategoryApplication  = Bit(0),
	EventCategoryInput		 = Bit(1),
	EventCategoryKeyboard	 = Bit(2),
	EventCategoryMouse		 = Bit(3),
	EventCategoryMouseButton  = Bit(4)
};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								EventType GetEventType() const override { return GetStaticType(); }\
								const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) int GetCategoryFlags() const override { return category; }

class LETGEN_API Event
{
	friend class EventDispatcher;
public:
	virtual EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual int GetCategoryFlags() const = 0;
	virtual std::string ToString() const { return GetName(); }
	bool Handled() const { return _handled; }
	bool IsInCategory(EventCategory category) const
	{
		return GetCategoryFlags() & static_cast<int>(category);
	}
protected:
	bool _handled = false;
};

class LETGEN_API EventDispatcher
{
	template<typename T>
	using EventFn = std::function<bool(T&)>;
public:
	explicit EventDispatcher(Event& event)
		: _event(event) { }

	template<typename T>
	bool Dispatch(EventFn<T> func)
	{
		if(_event.GetEventType() == T::GetStaticType())
		{
			_event._handled = func(*static_cast<T*>(&_event));
			return true;
		}
		return false;
	}
private:
	Event& _event;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
	return os << e.ToString();
}
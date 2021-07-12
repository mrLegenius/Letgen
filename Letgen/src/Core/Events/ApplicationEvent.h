#pragma once

#include <sstream>

#include "Event.h"

#include <string>

class LETGEN_API WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(const unsigned int width, const unsigned int height)
		: _width(width), _height(height) { }

	unsigned int GetWidth() const { return _width; }
	unsigned int GetHeight() const { return _height; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "WindowResizeEvent: " << _width << ", " << _height;
		return ss.str();
	}

	EVENT_CLASS_TYPE(WindowResize)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
private:
	unsigned int _width;
	unsigned int _height;

};

class LETGEN_API WindowCloseEvent: public Event
{
public:
	WindowCloseEvent() = default;

	EVENT_CLASS_TYPE(WindowClose)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class LETGEN_API AppTickEvent : public Event
{
public:
	AppTickEvent() = default;

	EVENT_CLASS_TYPE(AppTick)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class LETGEN_API AppUpdateEvent : public Event
{
public:
	AppUpdateEvent() = default;

	EVENT_CLASS_TYPE(AppUpdate)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class LETGEN_API AppRenderEvent : public Event
{
public:
	AppRenderEvent() = default;

	EVENT_CLASS_TYPE(AppRender)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};


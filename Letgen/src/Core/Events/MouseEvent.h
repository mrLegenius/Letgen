#pragma once

#include <sstream>
#include "Event.h"

class LETGEN_API MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(const float x, const float y)
		: _mouseX(x), _mouseY(y) { }

	float GetX() const { return _mouseX; }
	float GetY() const { return _mouseY; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseMovedEvent: " << _mouseX << ", " << _mouseY;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseMoved)
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	
private:
	float _mouseX;
	float _mouseY;
};

class LETGEN_API MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(const float xOffset, const float yOffset)
		: _xOffset(xOffset), _yOffset(yOffset) { }

	float GetXOffset() const { return _xOffset; }
	float GetYOffset() const { return _yOffset; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseScrolledEvent: " << _xOffset << ", " << _yOffset;
		return ss.str();
	}
	
	EVENT_CLASS_TYPE(MouseScrolled)
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
private:
	float _xOffset;
	float _yOffset;
};

class LETGEN_API MouseButtonEvent : public Event
{
public:
	int GetMouseButton() const { return _button; }

	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
protected:
	explicit MouseButtonEvent(const int button)
		: _button(button) { }
	int _button;
};

class LETGEN_API MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	explicit MouseButtonPressedEvent(const int button)
		: MouseButtonEvent(button) { }
	
	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << _button;
		return ss.str();
	}
	
	EVENT_CLASS_TYPE(MouseButtonPressed)
};

class LETGEN_API MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	explicit MouseButtonReleasedEvent(const int button)
		: MouseButtonEvent(button) { }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: " << _button;
		return ss.str();
	}

	EVENT_CLASS_TYPE(MouseButtonReleased)
};



#pragma once

#include <sstream>

#include "Event.h"

class LETGEN_API KeyEvent : public Event
{
public:
	int GetKeyCode() const { return _keycode; }

	EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
protected:
	explicit KeyEvent(const int keycode) : _keycode(keycode) { }

	int _keycode;
};

class LETGEN_API KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(const int keycode, const int repeatCount)
		: KeyEvent(keycode), _repeatCount(repeatCount) { }

	int GetRepeatCount() const { return _repeatCount; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << _keycode << " (" << _repeatCount << " repeats)";
		return ss.str();
	}
	
	EVENT_CLASS_TYPE(KeyPressed)
	
private:
	int _repeatCount;
};

class LETGEN_API KeyReleasedEvent : public KeyEvent
{
public:
	explicit KeyReleasedEvent(const int keycode)
		: KeyEvent(keycode) { }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << _keycode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyReleased)
};
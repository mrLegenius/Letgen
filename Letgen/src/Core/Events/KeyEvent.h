#pragma once

#include <sstream>

#include "Event.h"

class LETGEN_API KeyEvent : public Event
{
public:
	int GetKeyCode() const { return m_Keycode; }

	EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
protected:
	explicit KeyEvent(const int keycode) : m_Keycode(keycode) { }

	int m_Keycode;
};

class LETGEN_API KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(const int keycode, const int repeatCount)
		: KeyEvent(keycode), m_RepeatCount(repeatCount) { }

	int GetRepeatCount() const { return m_RepeatCount; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << m_Keycode << " (" << m_RepeatCount << " repeats)";
		return ss.str();
	}
	
	EVENT_CLASS_TYPE(KeyPressed)
	
private:
	int m_RepeatCount;
};

class LETGEN_API KeyReleasedEvent : public KeyEvent
{
public:
	explicit KeyReleasedEvent(const int keycode)
		: KeyEvent(keycode) { }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << m_Keycode;
		return ss.str();
	}

	EVENT_CLASS_TYPE(KeyReleased)
};
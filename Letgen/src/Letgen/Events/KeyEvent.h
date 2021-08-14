#pragma once
#include "Event.h"
#include "Letgen/Input/KeyCodes.h"

namespace Letgen
{
	class KeyEvent : public Event
	{
	public:
		_NODISCARD KeyCode GetKeyCode() const { return m_Keycode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		explicit KeyEvent(const KeyCode keycode) : m_Keycode(keycode) { }

		KeyCode m_Keycode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(const KeyCode keycode, const int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) { }

		_NODISCARD int GetRepeatCount() const { return m_RepeatCount; }

		_NODISCARD std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << static_cast<int>(m_Keycode) << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_RepeatCount;
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(const KeyCode keycode)
			: KeyEvent(keycode) { }

		_NODISCARD std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << static_cast<int>(m_Keycode);
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		explicit KeyReleasedEvent(const KeyCode keycode)
			: KeyEvent(keycode) { }

		_NODISCARD std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << static_cast<int>(m_Keycode);
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}
#pragma once
#include <sstream>

#include "Event.h" 

namespace Letgen
{
	class LETGEN_API WindowResizedEvent : public Event
	{
	public:
		WindowResizedEvent(const unsigned int width, const unsigned int height)
			: m_Width(width), m_Height(height) { }

		unsigned int GetWidth() const { return m_Width; }
		unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizedEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width;
		unsigned int m_Height;

	};

	class LETGEN_API WindowClosedEvent : public Event
	{
	public:
		WindowClosedEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class LETGEN_API AppTickedEvent : public Event
	{
	public:
		AppTickedEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class LETGEN_API AppUpdatedEvent : public Event
	{
	public:
		AppUpdatedEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class LETGEN_API AppRenderedEvent : public Event
	{
	public:
		AppRenderedEvent() = default;

		EVENT_CLASS_TYPE(AppRender)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}
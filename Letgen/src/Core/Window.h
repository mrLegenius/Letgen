#pragma once

#include "Events/Event.h"

namespace Letgen
{
	struct LETGEN_API WindowAttributes
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		explicit WindowAttributes(std::string title = "Letgen",
			const unsigned int width = 1280,
			const unsigned int height = 720)
			: title(std::move(title)),
			width(width),
			height(height) { }
	};
	
	class LETGEN_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() { }

		virtual void Update() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowAttributes& attributes = WindowAttributes());
	};
}
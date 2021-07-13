#pragma once
#include "Core/Window.h"
#include "GLFW/glfw3.h"

namespace Letgen
{
	class WindowsWindow : public Window
	{
	public:
		explicit WindowsWindow(const WindowAttributes& attributes);
		~WindowsWindow() override;

		void Update() override;

		unsigned int GetWidth() const override { return m_Data.width; }
		unsigned int GetHeight() const override { return m_Data.height; }

		void SetEventCallback(const EventCallbackFn& callback) override
		{
			m_Data.eventCallback = callback;
		}

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		void* GetNativeWindow() const override { return m_Window; }
	
	private:
		virtual void Init(const WindowAttributes& attributes);
		virtual void Close();

		GLFWwindow* m_Window = nullptr;

		struct WindowData
		{
			std::string title;
			unsigned int width = 0;
			unsigned int height = 0;

			bool vSync = false;

			EventCallbackFn eventCallback;
		};

		WindowData m_Data;
	};
}

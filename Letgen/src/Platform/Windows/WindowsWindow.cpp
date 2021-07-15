#include "pch.h"
#include "WindowsWindow.h"

#include "Core/Window.h"
#include "Core/Core.h"
#include "Core/Input.h"
#include "Core/Logger.h"
#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/KeyEvent.h"
#include "Core/Events/MouseEvent.h"

#include "glad/glad.h"

namespace Letgen
{
	static bool is_window_initialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		Log::Error("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowAttributes& attributes)
	{
		return new WindowsWindow(attributes);
	}

	WindowsWindow::WindowsWindow(const WindowAttributes& attributes)
	{
		WindowsWindow::Init(attributes);
	}

	WindowsWindow::~WindowsWindow()
	{
		WindowsWindow::Close();
	}

	void WindowsWindow::Init(const WindowAttributes& attributes)
	{
		m_Data.title = attributes.title;
		m_Data.width = attributes.width;
		m_Data.height = attributes.height;

		Log::InnerInfo("Creating window {0} ({1}x{2})",
			attributes.title, attributes.width, attributes.height);

		if (!is_window_initialized)
		{
			int success = glfwInit();
			LE_INNER_ASSERT(success, "Could not initialize GLFW");

			glfwSetErrorCallback(GLFWErrorCallback);
			is_window_initialized = true;
		}

		m_Window = glfwCreateWindow(
			static_cast<int>(m_Data.width),
			static_cast<int>(m_Data.height),
			m_Data.title.c_str(),
			nullptr,
			nullptr);

		glfwMakeContextCurrent(m_Window);

		int success = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		LE_INNER_ASSERT(success, "Could not initialize GLAD");
		
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		//Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			data.width = width;
			data.height = height;

			WindowResizedEvent event(width, height);
			data.eventCallback(event);
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			WindowClosedEvent event;
			data.eventCallback(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.eventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.eventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				//TODO: find a repeat count
				KeyPressedEvent event(key, 1);
				data.eventCallback(event);
				break;
			}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int character)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			KeyTypedEvent event(character);
			data.eventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent event(button);
				data.eventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent event(button);
				data.eventCallback(event);
				break;
			}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
			data.eventCallback(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			auto& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
			MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
			data.eventCallback(event);
		});
	}

	void WindowsWindow::Close()
	{
		glfwDestroyWindow(m_Window);
	}
	
	void WindowsWindow::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}
	
	void WindowsWindow::SetVSync(const bool enabled)
	{
		glfwSwapInterval(enabled ? 1 : 0);

		m_Data.vSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.vSync;
	}
}

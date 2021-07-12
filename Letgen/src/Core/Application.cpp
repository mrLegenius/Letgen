#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Logger.h"

#include <GLFW/glfw3.h>

namespace Letgen
{
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{		
		while (m_IsRunning)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);


			m_Window->Update();
		}
	}

	void Application::OnEvent(Event& e)
	{

		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));

		Log::Debug("{0}", e);

	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_IsRunning = false;
		return true;
	}

}

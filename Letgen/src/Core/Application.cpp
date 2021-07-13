#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Logger.h"

#include <glad/glad.h>

namespace Letgen
{

	Application* Application::s_Instance = nullptr;
	
	Application::Application()
	{
		LE_INNER_ASSERT(!s_Instance, "Only one applications allowed");
		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(LE_BIND_EVENT_FN(Application::OnEvent));
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

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}
			
			m_Window->Update();
		}
	}

	void Application::OnEvent(Event& e)
	{

		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowClosedEvent>(LE_BIND_EVENT_FN(Application::OnWindowClosed));

		Log::Debug("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
	
	bool Application::OnWindowClosed(WindowClosedEvent& e)
	{
		m_IsRunning = false;
		return true;
	}

}

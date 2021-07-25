#include "pch.h"
#include "Application.h"

#include "Letgen/Events/ApplicationEvent.h"
#include "Letgen/Events/Event.h"
#include "Letgen/Core/Asserts.h"

#include "Letgen/Renderer/Renderer.h"

#include <GLFW/glfw3.h>

#include "Time.h"

namespace Letgen
{
	Application* Application::s_Instance = nullptr;
	
	Application::Application(const std::string& name)
	{
		LET_PROFILE_FUNCTION();
		
		LET_CORE_ASSERT(!s_Instance, "Only one applications allowed");
		s_Instance = this;
		
		m_Window = Window::Create(WindowAttributes(name));
		m_Window->SetEventCallback(LET_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();
		
		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		Renderer::Shutdown();
	}

	void Application::Run()
	{
		LET_PROFILE_FUNCTION();
		
		while (m_IsRunning)
		{
			LET_PROFILE_SCOPE("Run loop");
			
			const auto time = static_cast<float>(glfwGetTime()); //Platform::GetTime
			const float timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			Time::s_DeltaTime = timestep;	
			
			if(!m_Minimized)
			{
				LET_PROFILE_SCOPE("LayerStack OnUpdate");
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate();
				}		
			}

			m_ImGuiLayer->Begin();
			{
				LET_PROFILE_SCOPE("LayerStack OnImGuiRender");
				for (Layer* layer : m_LayerStack)
					layer->OnImGuiRender();
			}
			m_ImGuiLayer->End();
			
			m_Window->Update();
		}
	}

	void Application::Close()
	{
		m_IsRunning = false;
	}

	void Application::OnEvent(Event& e)
	{
		LET_PROFILE_FUNCTION();
		
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowClosedEvent>(LET_BIND_EVENT_FN(Application::OnWindowClosed));
		dispatcher.Dispatch<WindowResizedEvent>(LET_BIND_EVENT_FN(Application::OnWindowResized));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.handled)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		LET_PROFILE_FUNCTION();
		
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* overlay)
	{
		LET_PROFILE_FUNCTION();
		
		m_LayerStack.PushOverlay(overlay);
		overlay->OnAttach();
	}
	
	bool Application::OnWindowClosed(WindowClosedEvent& e)
	{
		Close();
		return true;
	}

	bool Application::OnWindowResized(WindowResizedEvent& e)
	{
		LET_PROFILE_FUNCTION();
		
		if(e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			
			return false;
		}

		m_Minimized = false;

		Renderer::OnWindowResized(e.GetWidth(), e.GetHeight());
		
		return false;
	}
}

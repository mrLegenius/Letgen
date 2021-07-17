﻿#include "pch.h"
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
	
	Application::Application()
	{
		LE_CORE_ASSERT(!s_Instance, "Only one applications allowed");
		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(LE_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();
		
		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{		
		while (m_IsRunning)
		{
			const float time = static_cast<float>(glfwGetTime()); //Platform::GetTime
			const float timestep = time - m_LastFrameTime;
			m_LastFrameTime = time;
			Time::s_DeltaTime = timestep;	
			
			if(!m_Minimized)
			{
				for (Layer* layer : m_LayerStack)
				{
					layer->OnUpdate();
				}		
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();
			
			m_Window->Update();
		}
	}
	
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowClosedEvent>(LE_BIND_EVENT_FN(Application::OnWindowClosed));
		dispatcher.Dispatch<WindowResizedEvent>(LE_BIND_EVENT_FN(Application::OnWindowResized));

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

	bool Application::OnWindowResized(WindowResizedEvent& e)
	{
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
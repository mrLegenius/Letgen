#include "pch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Logger.h"

#include <glad/glad.h>

#include "Renderer/Shader.h"

namespace Letgen
{

	Application* Application::s_Instance = nullptr;
	
	Application::Application()
	{
		LE_CORE_ASSERT(!s_Instance, "Only one applications allowed");
		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(LE_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);


		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		float vertices[3 * 3] =
		{
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);

		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


		//m_Shader = new Shader("../res/shaders/Unlit_Color.shader");
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{		
		while (m_IsRunning)
		{
			const float gray = 0.69f / 5;
			glClearColor(gray, gray, gray, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			//m_Shader->Bind();
			
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			
			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
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

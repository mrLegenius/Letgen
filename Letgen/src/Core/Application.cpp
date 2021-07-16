#include "pch.h"
#include "Application.h"

#include "Events/ApplicationEvent.h"
#include "Events/Event.h"
#include "Asserts.h"
#include "Input.h"
#include "Events/KeyEvent.h"

#include "Renderer/Buffer.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/Renderer.h"
#include "Renderer/Shader.h"

namespace Letgen
{
	Application* Application::s_Instance = nullptr;
	
	Application::Application() :
		m_Camera(-10.0f, 10.0f, -10.0f, 10.0f)
	{
		LE_CORE_ASSERT(!s_Instance, "Only one applications allowed");
		s_Instance = this;
		
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(LE_BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer;
		PushOverlay(m_ImGuiLayer);

		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f,  0.69f / 1, 0.69f / 2, 0.69f / 3, 1.0f,
			0.5f, -0.5f, 0.0f,  0.69f / 4, 0.69f / 5, 0.69f / 6, 1.0f,
			0.0f, 0.5f, 0.0f, 0.69f / 7, 0.69f / 8, 0.69f / 9, 1.0f
		};

		uint32_t indices[3] = { 0, 1, 2 };
		m_VertexArray.reset(VertexArray::Create()); 

		std::shared_ptr<VertexBuffer> vertexBuffer(VertexBuffer::Create(vertices, sizeof vertices));
		
		vertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" }
		});

		const std::shared_ptr<IndexBuffer> indexBuffer(IndexBuffer::Create(indices, sizeof indices / sizeof(uint32_t)));

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);
		
		m_Shader.reset(new Shader("C:/Projects/C++/Letgen/Letgen/res/shaders/Unlit_Color.shader"));
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{		
		while (m_IsRunning)
		{
			const float gray = 0.69f / 5;
			
			RenderCommand::SetClearColor(glm::vec4(glm::vec3(gray), 1.0f));
			RenderCommand::Clear();
			
			Renderer::BeginScene();

			if(Input::IsKeyPressed(KeyCode::A))
				m_Camera.SetPosition({ 1.0f, 0.0f, 0.0f });

			if (Input::IsKeyPressed(KeyCode::D))
				m_Camera.SetPosition({ -1.0f, 0.0f, 0.0f });

			if (Input::IsKeyPressed(KeyCode::S))
				m_Camera.SetPosition({ 0.0f, 1.0f, 0.0f });

			if (Input::IsKeyPressed(KeyCode::W))
				m_Camera.SetPosition({ 0.0f, -1.0f, 0.0f });
			
			
			auto view = m_Camera.GetViewMatrix();
			auto projection = m_Camera.GetProjectionMatrix();
			
			m_Shader->Bind();

			m_Shader->SetUniformMat4f("u_View", view);
			m_Shader->SetUniformMat4f("u_Projection", projection);
			
			Renderer::Submit(m_VertexArray);
			
			Renderer::EndScene();
			
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

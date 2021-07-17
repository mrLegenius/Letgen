#include <Letgen.h>
#include <glm/glm.hpp>

#include "imgui/imgui.h"

class ExampleLayer : public Letgen::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f,  0.69f / 1, 0.69f / 3, 0.69f / 1, 1.0f,
			0.5f, -0.5f, 0.0f,  0.69f / 2, 0.69f / 2, 0.69f / 1, 1.0f,
			0.0f, 0.5f, 0.0f, 0.69f / 3, 0.69f / 1, 0.69f / 1, 1.0f
		};

		uint32_t indices[3] = { 0, 1, 2 };
		m_VertexArray.reset(Letgen::VertexArray::Create());
		std::shared_ptr<Letgen::VertexBuffer> vertexBuffer(Letgen::VertexBuffer::Create(vertices, sizeof vertices));

		vertexBuffer->SetLayout({
			{ Letgen::ShaderDataType::Float3, "a_Position" },
			{ Letgen::ShaderDataType::Float4, "a_Color" }
		});

		const std::shared_ptr<Letgen::IndexBuffer> indexBuffer(Letgen::IndexBuffer::Create(indices, sizeof indices / sizeof(uint32_t)));

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_Shader.reset(new Letgen::Shader("C:/Projects/C++/Letgen/Letgen/res/shaders/Unlit_Color.shader"));
	}

	void OnUpdate() override
	{
		Letgen::Log::Info("Delta time {0}ms", Letgen::Time::GetDeltaTime().GetMilliseconds());
		const float gray = 0.69f / 5;

		if(Letgen::Input::IsKeyPressed(KeyCode::A))
		{
			m_Transform.position.x -= 1.0f * Letgen::Time::GetDeltaTime();
		}
		if (Letgen::Input::IsKeyPressed(KeyCode::D))
		{
			m_Transform.position.x += 1.0f * Letgen::Time::GetDeltaTime();
		}
		
		Letgen::RenderCommand::SetClearColor(glm::vec4(glm::vec3(gray), 1.0f));
		Letgen::RenderCommand::Clear();

		Letgen::Renderer::BeginScene();

		m_Camera.SetPosition(m_Position);
		const auto view = m_Camera.GetViewMatrix();
		const auto projection = m_Camera.GetProjectionMatrix();

		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_Model", m_Transform.GetModel());
		m_Shader->SetUniformMat4f("u_View", view);
		m_Shader->SetUniformMat4f("u_Projection", projection);

		Letgen::Renderer::Submit(m_VertexArray);

		Letgen::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{

	}
	
	void OnEvent(Letgen::Event& event) override
	{
	}

private:
	glm::vec3 m_Position{ 0.0f };
	float m_CameraSpeed{ 0.1f };
	Letgen::Transform m_Transform;
	
	std::shared_ptr<Letgen::VertexArray> m_VertexArray;
	std::shared_ptr<Letgen::Shader> m_Shader;

	Letgen::OrthographicCamera m_Camera{-1.0f, 1.0f, -1.0f, 1.0f};
};


class Sandbox : public Letgen::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer);
	}
	~Sandbox() { }
};

Letgen::Application* Letgen::CreateApplication()
{
	return new Sandbox;
}
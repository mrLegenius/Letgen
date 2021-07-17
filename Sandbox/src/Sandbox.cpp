#include <Letgen.h>
#include <glm/glm.hpp>

#include "imgui/imgui.h"
#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public Letgen::Layer
{
public:
	ExampleLayer() : Layer("Example")
	{
		float vertices[] =
		{
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		uint32_t indices[] = { 0, 1, 2, 2, 3, 0 };
		m_VertexArray.reset(Letgen::VertexArray::Create());
		Letgen::Ref<Letgen::VertexBuffer> vertexBuffer(Letgen::VertexBuffer::Create(vertices, sizeof vertices));

		vertexBuffer->SetLayout({
			{ Letgen::ShaderDataType::Float3, "a_Position" },
			{ Letgen::ShaderDataType::Float2, "a_TexCoord" }
		});

		const Letgen::Ref<Letgen::IndexBuffer> indexBuffer(Letgen::IndexBuffer::Create(indices, sizeof indices / sizeof(uint32_t)));

		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);
		
		m_Shader.reset(Letgen::Shader::Create("assets/shaders/Unlit_Texture.shader"));
		
		m_Texture = Letgen::Texture2D::Create("assets/textures/love.jpg");

		Letgen::Log::Debug("Texture size: {0}x{1}", m_Texture->GetWidth(), m_Texture->GetHeight());
		
		std::dynamic_pointer_cast<Letgen::OpenGLShader>(m_Shader)->Bind();
		std::dynamic_pointer_cast<Letgen::OpenGLShader>(m_Shader)->SetUniformInt("u_Texture", 0);
	}

	void OnUpdate() override
	{
		const float gray = 0.69f / 5;
		
		Letgen::RenderCommand::SetClearColor(glm::vec4(glm::vec3(gray), 1.0f));
		Letgen::RenderCommand::Clear();

		Letgen::Renderer::BeginScene();

		const auto view = m_Camera.GetViewMatrix();
		const auto projection = m_Camera.GetProjectionMatrix();

		auto glShader = std::dynamic_pointer_cast<Letgen::OpenGLShader>(m_Shader);

		glShader->Bind();
		glShader->SetUniformFloatMatrix4("u_Model", m_Transform.GetModel());
		glShader->SetUniformFloatMatrix4("u_View", view);
		glShader->SetUniformFloatMatrix4("u_Projection", projection);

		m_Texture->Bind();
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

	Letgen::Ref<Letgen::VertexArray> m_VertexArray;
	Letgen::Ref<Letgen::Shader> m_Shader;
	Letgen::Ref<Letgen::Texture> m_Texture;
	Letgen::OrthographicCamera m_Camera{(720.0f / 1280.0f), 2.0f};
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
#include "Sandbox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D") { }

void Sandbox2D::OnAttach()
{
	m_Sprite = std::make_shared<Letgen::Sprite>("assets/textures/voenmeh.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate()
{
	m_CameraController.Update();

	const float gray = 0.69f / 5;

	Letgen::RenderCommand::SetClearColor(glm::vec4(glm::vec3(gray), 1.0f));
	Letgen::RenderCommand::Clear();

	Letgen::Renderer::BeginScene(m_CameraController.GetCamera());

	Letgen::Renderer::Submit(m_Sprite);

	m_Sprite->GetTransform()->position.x += m_Offset;

	Letgen::Renderer::Submit(m_Sprite);

	m_Sprite->GetTransform()->position.x -= m_Offset;

	Letgen::Renderer::EndScene();
}

void Sandbox2D::OnEvent(Letgen::Event& event)
{
	m_CameraController.OnEvent(event);
}

void Sandbox2D::OnImGuiRender()
{
}


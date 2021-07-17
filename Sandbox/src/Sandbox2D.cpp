#include "Sandbox2D.h"

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

	Letgen::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Letgen::Renderer2D::DrawQuad({
	{1.0f, 1.0f},45.0f,{1.0f, 1.0f} },
		{ 0.5f, 0.2f, 0.7f, 1.0f });
	

	Letgen::Renderer2D::DrawQuad({
		{-1.0f, -1.0f},30.0f,{0.6f, 0.8f} },
		{ 0.8f, 0.3f, 0.4f, 1.0f });
	
	Letgen::Renderer2D::DrawSprite(m_Sprite);

	m_Sprite->GetTransform()->position.x += m_Offset;
	Letgen::Renderer2D::DrawSprite(m_Sprite);
	m_Sprite->GetTransform()->position.x -= m_Offset;

	Letgen::Renderer2D::EndScene();
}

void Sandbox2D::OnEvent(Letgen::Event& event)
{
	m_CameraController.OnEvent(event);
}

void Sandbox2D::OnImGuiRender()
{
}


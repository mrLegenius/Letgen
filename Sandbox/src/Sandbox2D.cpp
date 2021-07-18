#include "Sandbox2D.h"

#include "ImGui/imgui.h"
#include "Letgen/Debug/Instrumentor.h"

Sandbox2D::Sandbox2D() : Layer("Sandbox2D") { }

void Sandbox2D::OnAttach()
{
	LE_PROFILE_FUNCTION();
	
	m_Sprite = std::make_shared<Letgen::Sprite>("assets/textures/voenmeh.png");
}

void Sandbox2D::OnDetach()
{
	LE_PROFILE_FUNCTION();
	
}

void Sandbox2D::OnUpdate()
{
	LE_PROFILE_FUNCTION();
	
	m_CameraController.Update();
	
	{
		LE_PROFILE_SCOPE("Renderer Begin");
		Letgen::Renderer2D::BeginScene(m_CameraController.GetCamera());
	}

	{
		LE_PROFILE_SCOPE("Renderer Draw");
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
	}
	{
		LE_PROFILE_SCOPE("Renderer End");
		Letgen::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnEvent(Letgen::Event& event)
{
	m_CameraController.OnEvent(event);
}

void Sandbox2D::OnImGuiRender()
{

}


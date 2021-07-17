#pragma once
#include "Letgen.h"

class Sandbox2D final : public Letgen::Layer
{
public:
	Sandbox2D();
	~Sandbox2D() override = default;

	void OnAttach() override;
	void OnDetach() override;
	void OnUpdate() override;
	void OnEvent(Letgen::Event& event) override;
	void OnImGuiRender() override;

private:
	Letgen::OrthographicCameraController m_CameraController{ 1280.0f / 720.0f , true };
	Letgen::Ref<Letgen::Sprite> m_Sprite;
	float m_Offset = 10.0f;
};

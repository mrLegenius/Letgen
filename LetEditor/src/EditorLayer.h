#pragma once
#include "Letgen.h"

namespace Letgen
{
	class EditorLayer final : public Layer
	{
	public:
		EditorLayer();
		~EditorLayer() override = default;

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;
		void OnImGuiRender() override;

	private:
		void DrawViewport();
		OrthographicCameraController m_CameraController { 1280.0f / 720.0f , true };
		Ref<Framebuffer> m_Framebuffer;

		glm::vec2 m_ViewportSize { 0.0f};
	};
}

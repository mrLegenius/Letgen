#pragma once
#include "Letgen.h"
#include "EditorWindows/SceneHierarchyEditorWindow.h"
#include "Letgen/Events/KeyEvent.h"

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
		bool OnKeyPressed(KeyPressedEvent& event);

		void CreateNewScene();
		void OpenScene();
		void SaveSceneAs();

		
		void DrawDockSpace();
		void DrawViewport();
		void DrawStatistics();

		OrthographicCameraController m_CameraController { 1280.0f / 720.0f , true };
		Ref<Framebuffer> m_Framebuffer = nullptr;

		Ref<Scene> m_ActiveScene = nullptr;
		Entity m_CameraEntity;
		Entity m_SquareEntity;
		
		glm::vec2 m_ViewportSize { 0.0f };

		bool m_ViewportFocused = false;
		bool m_ViewportHovered = false;

		SceneHierarchyEditorWindow m_Hierarchy;
	};
}

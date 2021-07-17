#pragma once
#include "Core/Renderer/Camera/OrthographicCamera.h"

#include "Core/Events/ApplicationEvent.h"
#include "Core/Events/MouseEvent.h"

namespace Letgen
{
	class OrthographicCameraController
	{
	public:
		explicit OrthographicCameraController(float aspectRatio, bool isRotatable);

		[[nodiscard]] const OrthographicCamera& GetCamera() const { return m_Camera; }
		[[nodiscard]] OrthographicCamera& GetCamera() { return m_Camera; }
		
		void Update();
		void OnEvent(Event& event);
	private:
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizedEvent& e);
		
		float m_Zoom = 1.0f;

		bool m_IsRotatable;
		
		OrthographicCamera m_Camera;

		const float m_MoveSpeed = 5.0f;
		const float m_RotationSpeed = 180.0f;
	};
}

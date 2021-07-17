#pragma once
#include "Letgen/Renderer/Camera/OrthographicCamera.h"

#include "Letgen/Events/ApplicationEvent.h"
#include "Letgen/Events/MouseEvent.h"

namespace Letgen
{
	class OrthographicCameraController
	{
	public:
		explicit OrthographicCameraController(float aspectRatio, bool isRotatable);

		void Update();
		void OnEvent(Event& event);
		
		[[nodiscard]] const OrthographicCamera& GetCamera() const { return m_Camera; }
		[[nodiscard]] OrthographicCamera& GetCamera() { return m_Camera; }
		
		
		[[nodiscard]] float GetZoom() const { return m_Zoom; }
		void SetZoom(const float zoom) { m_Zoom = zoom; }
	
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

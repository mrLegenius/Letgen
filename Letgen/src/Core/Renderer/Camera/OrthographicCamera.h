﻿#pragma once
#include "glm/glm.hpp"

namespace Letgen
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		~OrthographicCamera() = default;

		[[nodiscard]] const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position)
		{
			m_Position = position;
			RecalculateViewMatrix();
		}

		[[nodiscard]] float GetRotation() const { return m_Rotation; }
		void SetRotation(const float rotation)
		{
			m_Rotation = rotation;
			RecalculateViewMatrix();
		}

		[[nodiscard]] glm::mat4 GetViewMatrix() const { return m_ViewMatrix; }
		[[nodiscard]] glm::mat4 GetProjectionMatrix() const { return m_ProjectionMatrix; }
	
	private:
		void RecalculateViewMatrix();
		
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		
		glm::vec3 m_Position {0.0f};
		float m_Rotation = 0.0f;
	};
}

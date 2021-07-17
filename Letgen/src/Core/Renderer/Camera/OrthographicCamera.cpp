#include "pch.h"
#include "OrthographicCamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Letgen
{
	OrthographicCamera::OrthographicCamera(float aspectRatio, float orthographicSize)
		: m_ProjectionMatrix(glm::ortho(-orthographicSize, orthographicSize, aspectRatio * -orthographicSize, aspectRatio * orthographicSize, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		const glm::mat4 transform = translate(glm::mat4(1.0f), m_Position) * 
			rotate(glm::mat4(1.0f), m_Rotation, glm::vec3(1.0, 0.0f, 1.0f));

		m_ViewMatrix = inverse(transform);
	}
}

#include "pch.h"
#include "OrthographicCamera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Letgen
{
	OrthographicCamera::OrthographicCamera(const float aspectRatio, const float orthographicSize) :
		m_ProjectionMatrix({1.0f} ), m_ViewMatrix({ 1.0f } ), m_AspectRatio(aspectRatio), m_OrthographicSize(orthographicSize)
	{
		RecalculateProjectionMatrix();
	}

	void OrthographicCamera::SetAspectRatio(const float aspectRatio)
	{
		m_AspectRatio = aspectRatio;
		RecalculateProjectionMatrix();
	}
	
	void OrthographicCamera::SetOrthographicSize(const float size)
	{
		m_OrthographicSize = size;
		RecalculateProjectionMatrix();
	}

	void OrthographicCamera::RecalculateProjectionMatrix()
	{
		m_ProjectionMatrix = glm::ortho(
			-m_OrthographicSize * m_AspectRatio,
			m_OrthographicSize * m_AspectRatio,
			-m_OrthographicSize,
			 m_OrthographicSize,
			-1.0f,
			1.0f);
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		const glm::mat4 transform = translate(glm::mat4(1.0f), m_Position) * 
			rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0.0, 0.0f, 1.0f));

		m_ViewMatrix = inverse(transform);
	}
}

#include "pch.h"
#include "SceneCamera.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Letgen
{
	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	void SceneCamera::SetOrthographic(const float size, const float nearClip, const float farClip)
	{
		m_OrthographicSize = size;
		m_OrthographicNear = nearClip;
		m_OrthographicFar = farClip;

		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(const uint32_t width, const uint32_t height)
	{
		m_AspectRatio = static_cast<float>(width) / static_cast<float>(height);

		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		const float vertical = m_AspectRatio * m_OrthographicSize * 0.5f;
		const float horizontal = m_OrthographicSize * 0.5f;

		m_Projection = glm::ortho(
			-vertical, vertical,
			-horizontal, horizontal,
			m_OrthographicNear, m_OrthographicFar);
	}
}

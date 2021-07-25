#include "pch.h"
#include "Transform2DComponent.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"

namespace Letgen
{
	Transform2DComponent::Transform2DComponent(
		const glm::vec2& position,
		const float angle,
		const glm::vec2& scale) :
		position(position), angle(angle), scale(scale) { }


	void Transform2DComponent::RecalculateModel()
	{
		LET_PROFILE_FUNCTION();

		auto model = translate(glm::mat4(1.0f), glm::vec3(position, 0.0f));
		if (glm::abs(angle) > 0.000001f)
		{
			model = rotate(model, glm::radians(angle), glm::vec3(0, 0, 1.0f));
		}

		model = glm::scale(model, glm::vec3(scale, 1.0f));

		m_Model = model;
	}
}

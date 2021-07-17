#include "pch.h"
#include "Transform2D.h"

#include "glm/gtc/matrix_transform.hpp"
#include "glm/glm.hpp"

namespace Letgen
{
	Transform2D::Transform2D(
		const glm::vec2& position,
		const float angle,
		const glm::vec2& scale) :
			position(position), angle(angle), scale(scale) { }

	glm::mat4 Transform2D::GetModel() const
	{
		return translate(glm::mat4(1.0f), glm::vec3(position, 0.0f)) *
			rotate(glm::mat4(1.0f), glm::radians(angle) , glm::vec3(0, 0, 1.0f)) *
			glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f));
	}
}

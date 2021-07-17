#include "pch.h"
#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Letgen
{
	Transform::Transform(
		const glm::vec3& position,
		const glm::vec3& eulerAngles,
		const glm::vec3& scale) :
			position(position),
			eulerAngles(eulerAngles),
			scale(scale) { }

	glm::mat4 Transform::GetModel() const
	{
		return glm::translate(glm::mat4(1.0f), position) *
			glm::rotate(glm::mat4(1.0f), glm::radians(eulerAngles.x), glm::vec3(1.0f, 0, 0)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(eulerAngles.y), glm::vec3(0, 1.0f, 0)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(eulerAngles.z), glm::vec3(0, 0, 1.0f)) *
			glm::scale(glm::mat4(1.0f), scale);
	}
}


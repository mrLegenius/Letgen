#pragma once
#include "glm/glm.hpp"
namespace Letgen
{
	class Transform
	{
	public:
		glm::vec3 position;
		glm::vec3 eulerAngles;
		glm::vec3 scale;

		explicit Transform(
			const glm::vec3& position = { 0.0f, 0.0f, 0.0f },
			const glm::vec3& eulerAngles = { 0.0f, 0.0f, 0.0f },
			const glm::vec3& scale = { 1.0f, 1.0f, 1.0f });

		glm::mat4 GetModel() const;

		glm::vec3 Front() const;
	};
}

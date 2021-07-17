#pragma once
#include <glm/glm.hpp>

namespace Letgen
{
	class Transform2D
	{
	public:
		glm::vec2 position;
		float angle;
		glm::vec2 scale;

		Transform2D(
			const glm::vec2& position = { 0.0f, 0.0f },
			float angle = 0.0f,
			const glm::vec2& scale = { 1.0f, 1.0f });

		[[nodiscard]] glm::mat4 GetModel() const;
	};
}

#pragma once
#include "glm/glm.hpp"

namespace Letgen
{
	struct TransformComponent
	{
		glm::mat4 transform = glm::mat4(1.0f);

		TransformComponent() = default;
		TransformComponent(const glm::mat4& other)
			: transform(other) { }

		TransformComponent(const TransformComponent&) = default;

		operator glm::mat4& () { return transform; }
		operator const glm::mat4& () const { return transform; }
	};

	struct SpriteComponent
	{
		glm::vec4 color {1.0f};

		SpriteComponent() = default;
		SpriteComponent(const glm::vec4& other)
			: color(other) { }

		SpriteComponent(const SpriteComponent&) = default;

		operator glm::vec4& () { return color; }
		operator const glm::vec4& () const { return color; }
	};
}

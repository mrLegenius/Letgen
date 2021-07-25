#pragma once
#include "glm/glm.hpp"
#include "Letgen/Renderer/Camera/SceneCamera.h"

namespace Letgen
{
	struct TagComponent
	{
		std::string tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(std::string other)
			: tag(std::move(other)) { }
	};
	
	struct TransformComponent
	{
		glm::mat4 transform = glm::mat4(1.0f);

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& other)
			: transform(other) { }

		operator glm::mat4& () { return transform; }
		operator const glm::mat4& () const { return transform; }
	};

	struct SpriteComponent
	{
		glm::vec4 color {1.0f};

		SpriteComponent() = default;
		SpriteComponent(const SpriteComponent&) = default;
		SpriteComponent(const glm::vec4& other)
			: color(other) { }

		operator glm::vec4& () { return color; }
		operator const glm::vec4& () const { return color; }
	};

	struct CameraComponent
	{
		SceneCamera camera;
		bool isMain = true;
		bool fixedAspectRatio = false;

		CameraComponent() = default;
		CameraComponent(const CameraComponent&) = default;
	};
}

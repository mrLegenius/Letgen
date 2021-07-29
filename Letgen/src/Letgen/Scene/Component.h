#pragma once
#include "ScriptableEntity.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
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
		glm::vec3 position{ 0.0f };
		glm::vec3 rotation{ 0.0f };
		glm::vec3 scale{ 1.0f };

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::vec3& position)
			: position(position) { }

		glm::mat4 GetModel() const
		{
			return glm::translate(glm::mat4(1.0f), position) *
				glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0, 0)) *
				glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0, 1.0f, 0)) *
				glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0, 0, 1.0f)) *
				glm::scale(glm::mat4(1.0f), scale);
		}
	};

	struct SpriteRendererComponent
	{
		glm::vec4 color {1.0f};
		std::string texture;

		SpriteRendererComponent() = default;
		SpriteRendererComponent(const SpriteRendererComponent&) = default;
		SpriteRendererComponent(const glm::vec4& other)
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

	struct NativeScriptComponent
	{
		ScriptableEntity* instance = nullptr;

		ScriptableEntity* (*InstantiateScript)() = nullptr;
		void (*DestroyScript)(NativeScriptComponent*) = nullptr;

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->instance; nsc->instance = nullptr; };
		}
	};
}

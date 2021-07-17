#pragma once
#include "Sprite.h"
#include "Camera/OrthographicCamera.h"
#include "Letgen/Components/Transform2D.h"

namespace Letgen
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnWindowResized(uint32_t width, uint32_t height);
		
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(const Transform2D& transform, const glm::vec4& color);
		static void DrawSprite(const Ref<Sprite>& sprite);
	private:
		struct SceneData
		{
			glm::mat4 viewMatrix;
			glm::mat4 projectionMatrix;
		};

		static SceneData* s_SceneData;
	};
}

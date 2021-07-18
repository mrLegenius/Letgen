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

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void DrawQuad(const Transform2D& transform, const glm::vec4& color);
		static void DrawSprite(const Ref<Sprite>& sprite);
		static void DrawSprite(const Transform2D& transform, const Ref<Texture2D>& texture);

		static void Flush();
	private:
		static void Draw(const Transform2D& transform, const glm::vec4& color, const Ref<Texture2D>& texture, float tiling);
		static void AddQuadToVertexBuffer(const glm::mat4& model, const glm::vec4& color, const Ref<Texture2D>& texture);
	};
}

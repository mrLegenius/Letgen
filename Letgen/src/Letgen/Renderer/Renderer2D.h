#pragma once
#include "Sprite.h"
#include "Camera/Camera.h"
#include "Camera/OrthographicCamera.h"
#include "Letgen/Scene/Component.h"
#include "Letgen/Scene/Components/Transform2DComponent.h"

namespace Letgen
{
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void BeginScene(const Camera& camera, const glm::mat4& transform);
		static void EndScene();
		
		static void Flush();
		
		static void DrawQuad(const Transform2DComponent& transform, const glm::vec4& color);
		static void DrawSprite(const Ref<Sprite>& sprite);
		static void DrawSprite(const Transform2DComponent& transform, const Ref<Texture2D>& texture);

		struct Statistics
		{
			uint32_t drawCalls = 0;
			uint32_t quadCount = 0;

			_NODISCARD uint32_t GetTotalVertexCount() const { return quadCount * 4; }
			_NODISCARD uint32_t GetTotalIndexCount() const { return quadCount * 6; }
		};
		
		static void ResetStats();
		static Statistics GetStats();
	
	private:
		static void NextBatch();
		static void StartBatch();
		
		static void Draw(const Transform2DComponent& transform, const glm::vec4& color, const Ref<Texture2D>& texture, float tiling);
		static void AddQuadToVertexBuffer(const glm::mat4& model, const glm::vec4& color, const Ref<Texture2D>& texture);
	};
}

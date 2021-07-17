#pragma once
#include "Core/Renderer/RendererAPI.h"

namespace Letgen
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;
		void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
		void Init() override;
	};
}

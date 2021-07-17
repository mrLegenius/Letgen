﻿#pragma once
#include "Letgen/Renderer/RendererAPI.h"

namespace Letgen
{
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		void Init() override;

		void SetViewport(int x, int y, uint32_t width, uint32_t height) override;
		
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;
		
		void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};
}

﻿#pragma once

#include <glm/glm.hpp>

#include "VertexArray.h"

namespace Letgen
{
	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};

		virtual ~RendererAPI() = default;

		
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;
		virtual void Init() = 0;
		virtual void SetViewport(int x, int y, uint32_t width, uint32_t height) = 0;

		static API GetAPI() { return s_API; }
	private:
		static API s_API;
	};
}

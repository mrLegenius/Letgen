#pragma once

#include "RendererAPI.h"

namespace Letgen
{
	class Renderer
	{
	public:
		static void Init();

		static void OnWindowResized(uint32_t width, uint32_t height);
		
		static void BeginScene();
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray);
		
		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}

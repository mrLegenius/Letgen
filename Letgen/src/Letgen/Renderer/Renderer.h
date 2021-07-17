#pragma once

#include "RendererAPI.h"
#include "Shader.h"
#include "Letgen/Renderer/Camera/OrthographicCamera.h"
#include "Letgen/Renderer/Sprite.h"

namespace Letgen
{
	class Renderer
	{
	public:
		static void Init();

		static void OnWindowResized(uint32_t width, uint32_t height);
		
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const Ref<Sprite>& sprite);
		
		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	private:
		static OrthographicCamera s_Camera;
	};
}

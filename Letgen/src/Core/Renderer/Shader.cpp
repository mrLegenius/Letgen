#include "pch.h"
#include "Shader.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Letgen
{
	Shader* Shader::Create(const std::string& filepath)
	{
		switch (Renderer::GetAPI()) {

		case RendererAPI::API::None:
			LE_CORE_ASSERT(false, "None for API was chosen");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLShader(filepath);
		}

		LE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}

#include "pch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Letgen
{
	Ref<VertexArray> VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {

		case RendererAPI::API::None:
			LET_CORE_ASSERT(false, "None for API was chosen");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexArray>();
		}

		LET_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}

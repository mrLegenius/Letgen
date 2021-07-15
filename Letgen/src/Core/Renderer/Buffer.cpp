#include "pch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Letgen
{
	VertexBuffer* VertexBuffer::Create(float* vertices, const uint32_t size)
	{
		switch (Renderer::GetAPI()) {

		case RendererAPI::None:
			Log::CoreCritical("None of Renderer API was chosen");
			LE_CORE_ASSERT(false, "None for API was chosen");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLVertexBuffer(vertices, size);
		}

		LE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, const uint32_t count)
	{
		switch (Renderer::GetAPI()) {

		case RendererAPI::None:
			Log::CoreCritical("None of Renderer API was chosen");
			LE_CORE_ASSERT(false, "None for API was chosen");
			return nullptr;
		case RendererAPI::OpenGL:
			return new OpenGLIndexBuffer(indices, count);
		}

		LE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}

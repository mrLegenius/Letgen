#include "pch.h"
#include "Buffer.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Letgen
{
	Ref<VertexBuffer> VertexBuffer::Create(uint32_t size)
	{
		switch (Renderer::GetAPI()) {

		case RendererAPI::API::None:
			LET_CORE_ASSERT(false, "None for API was chosen");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(size);
		}

		LET_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

	Ref<VertexBuffer> VertexBuffer::Create(float* vertices, const uint32_t size)
	{
		switch (Renderer::GetAPI()) {

		case RendererAPI::API::None:
			LET_CORE_ASSERT(false, "None for API was chosen");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLVertexBuffer>(vertices, size);
		}

		LET_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}

	Ref<IndexBuffer> IndexBuffer::Create(uint32_t* indices, const uint32_t count)
	{
		switch (Renderer::GetAPI()) {

		case RendererAPI::API::None:
			Log::CoreCritical("None of Renderer API was chosen");
			LET_CORE_ASSERT(false, "None for API was chosen");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return std::make_shared<OpenGLIndexBuffer>(indices, count);
		}

		LET_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}

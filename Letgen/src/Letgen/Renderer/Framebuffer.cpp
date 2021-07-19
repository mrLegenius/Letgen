#include "pch.h"
#include "Framebuffer.h"

#include "Renderer.h"
#include "Letgen/Core/Asserts.h"
#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Letgen
{
	Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI()) {

		case RendererAPI::API::None:
			LE_CORE_ASSERT(false, "None for API was chosen");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return CreateRef<OpenGLFramebuffer>(spec);
		}

		LE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}

﻿#include "pch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Letgen
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI()) {

		case RendererAPI::API::None:
			LE_CORE_ASSERT(false, "None for API was chosen");
			return nullptr;
		case RendererAPI::API::OpenGL:
			return new OpenGLVertexArray();
		}

		LE_CORE_ASSERT(false, "Unknown Renderer API");
		return nullptr;
	}
}
#include "pch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Letgen
{
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}

#pragma once

#include "Core/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Letgen
{
	class OpenGLContext : public GraphicsContext
	{
	public:
		explicit OpenGLContext(GLFWwindow* windowHandle);
		
		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}

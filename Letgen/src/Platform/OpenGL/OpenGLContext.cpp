#include "pch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Letgen
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		LE_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		const int success = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		LE_CORE_ASSERT(success, "Could not initialize GLAD");

		Log::CoreInfo("OpenGL Info:");
		Log::CoreInfo("	Vendor: {0}", glGetString(GL_VENDOR));
		Log::CoreInfo("	Renderer: {0}", glGetString(GL_RENDERER));
		Log::CoreInfo("	Version: {0}", glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}

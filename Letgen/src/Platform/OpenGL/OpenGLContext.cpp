#include "pch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Letgen/Core/Asserts.h"

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

#ifdef LE_ENABLE_ASSERTS
		int versionMajor, versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);
		const bool isOpenGLVersionSupported = 
			versionMajor > 4 || versionMajor == 4 && versionMinor >= 5;
		
		LE_CORE_ASSERT(isOpenGLVersionSupported, "LetGen requires at least OpenGL 4.5!!!")
#endif
		
		
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}

#include "vlpch.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Vinyl
{
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : m_WindowHandle(windowHandle)
	{
		VL_CORE_ASSERT(windowHandle, "Window handle is null.");
	}
	
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);

		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		VL_CORE_ASSERT(status, "Failed to initialize Glad.");

		VL_CORE_INFO("OpenGL Info:");
		VL_CORE_INFO("OpenGL Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		VL_CORE_INFO("OpenGL Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		VL_CORE_INFO("OpenGL Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}
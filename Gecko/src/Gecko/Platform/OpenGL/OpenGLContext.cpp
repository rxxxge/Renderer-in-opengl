#include "gkpch.h"
#include "OpenGLContext.h"

#include "Gecko/Log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <gl/GL.h>

namespace Gecko {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		GK_CORE_ASSERT(m_WindowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		GK_CORE_ASSERT(status, "Failed to intialize GLAD!");

		glEnable(GL_DEPTH_TEST);

		GK_CORE_INFO("OpenGL info:");
		GK_CORE_INFO(" -- Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		GK_CORE_INFO(" -- Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		GK_CORE_INFO(" -- Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}
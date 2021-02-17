#include "fspch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Farscape {



	OpenGLContext::OpenGLContext(GLFWwindow * windowHandle)
		: m_WindowHandle(windowHandle)
	{
		FS_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		status *= 1;
		FS_CORE_ASSERT(status, "Failed to initialize GLAD!");
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

}

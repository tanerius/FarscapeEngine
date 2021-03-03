#include "fspch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Farscape {



    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
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

        FS_CORE_INFO("Vendor: {0} ", glGetString(GL_VENDOR));
        FS_CORE_INFO("Renderer: {0} ", glGetString(GL_RENDERER));
        FS_CORE_INFO("Version: {0} ", glGetString(GL_VERSION));

#ifdef FS_ENABLE_ASSERTS
        int versionMajor;
        int versionMinor;
        glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
        glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

        FS_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Minimum OpenGL version >= 4.5!");
#endif
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }

}

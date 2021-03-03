#include "fspch.h"
#include "AppleWindow.h"

namespace Farscape {

    static bool s_GLFWInitialized = false;

    Window* Window::Create(const WindowProperties &p)
    {
        return new AppleWindow(p);
    }

    AppleWindow::AppleWindow(const WindowProperties & p)
    {
        Init(p);
    }

    AppleWindow::~AppleWindow() 
    { 
        Shutdown();
    }

    void AppleWindow::Init(const WindowProperties& p)
    {
        m_Data.Title = p.Title + " (MacOS)";
        m_Data.Width = p.Width;
        m_Data.Height = p.Height;

        FS_CORE_INFO("Creating window {0} ({1}, {2})", m_Data.Title, p.Width, p.Height);

        if (!s_GLFWInitialized)
        {
            // TODO: glfwterminate 
            int isOk = glfwInit();
            isOk = isOk * 1;
            FS_CORE_ASSERT(isOk, "Could not initialize GLFW!");
            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)p.Width, (int)p.Height, m_Data.Title.c_str(), nullptr, nullptr);
        glfwMakeContextCurrent(m_Window);
        glfwSetWindowUserPointer(m_Window, &m_Data);
        SetVSync(true);
    }

    void AppleWindow::Shutdown()
    {
        glfwDestroyWindow(m_Window);
    }

    void AppleWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_Window);
    }

    void AppleWindow::SetVSync(bool enabled)
    {
        if (enabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }
        m_Data.VSync = enabled;
    }

    bool AppleWindow::IsVSync() const
    {
        return m_Data.VSync;
    }

}
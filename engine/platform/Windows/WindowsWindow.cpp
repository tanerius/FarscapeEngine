#include "fspch.h"
#include "Farscape/Engine/Log.h"
#include "WindowsWindow.h"

namespace Farscape {

	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProperties &p)
	{
		return new WindowsWindow(p);
	}

	WindowsWindow::WindowsWindow(const WindowProperties & p)
	{
		Init(p);
	}

	WindowsWindow::~WindowsWindow() 
	{ 
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProperties& p)
	{
		m_Data.Title = p.Title;
		m_Data.Width = p.Width;
		m_Data.Height = p.Height;

		FS_CORE_INFO("Creating window {0} ({1}, {2})", p.Title, p.Width, p.Height);

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

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
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

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

}
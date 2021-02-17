#include "fspch.h"
#include "Core/Log.h"
#include "WindowsWindow.h"

// include events
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>

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
		m_Data.Title = p.Title + " (Windows)";
		m_Data.Width = p.Width;
		m_Data.Height = p.Height;

		FS_CORE_INFO("Creating window {0} ({1}, {2})", m_Data.Title, p.Width, p.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwterminate 
			int isOk = glfwInit();
			isOk = isOk * 1;
			FS_CORE_ASSERT(isOk, "Could not initialize GLFW!");

			/*
			* Set an error callback as well
			*  @param[in] error_code An [error code](@ref errors).  Future releases may add
			*  more error codes.
			*  @param[in] description A UTF-8 encoded string describing the error.
			*/
			glfwSetErrorCallback([](int error_code, const char* msg)
			{
				FS_CORE_ERROR("GLFW Error ({0}): {1}", error_code, msg);
			});
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)p.Width, (int)p.Height, m_Data.Title.c_str(), nullptr, nullptr);

		// create a graphics context
		m_Context = new OpenGLContext(m_Window);

		m_Context->Init();

		
		// Attach a user payload to the window handler with stuff we want to have  (m_Data in this case)
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set Callbacks for window events

		// RESIZE
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int w, int h)
		{
			// Here we need to call OnEvent
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = w;
			data.Height = h;

			WindowResizeEvent event(w, h);
			// dispatch the event
			data.EventCallback(event);
		});


		// CLOSE
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			// Here we need to call OnEvent
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			// dispatch the event
			data.EventCallback(event);
		});


		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int , int action_type, int)
		{
			/*
			*  @param[in] window The window that received the event.
			*  @param[in] key The [keyboard key](@ref keys) that was pressed or released.
			*  @param[in] scancode The system-specific scancode of the key.
			*  @param[in] action `GLFW_PRESS`, `GLFW_RELEASE` or `GLFW_REPEAT`.  Future
			*  releases may add more actions.
			*  @param[in] mods Bit field describing which [modifier keys](@ref mods) were
			*  held down.
			*/
			// Here we need to call OnEvent
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			if (&data == nullptr)
				return;

			// check the action type
			switch (action_type)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT:
			{
				// The repeat count can be extracted from the win_api 
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}
			};
		});


		// key typed
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int key)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(key);
			data.EventCallback(event);
		});

		// mouse button pressed
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int which_btn, int action_type, int)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			/*
			* @param[in] window The window that received the event.
			*  @param[in] button The[mouse button](@ref buttons) that was pressed or
			*released.
			*  @param[in] action One of `GLFW_PRESS` or `GLFW_RELEASE`.  Future releases
			*  may add more actions.
			*  @param[in] mods Bit field describing which[modifier keys](@ref mods) were
			*  held down.
			*/
			switch (action_type)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(which_btn);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(which_btn);
					data.EventCallback(event);
					break;
				}
			}
		});


		// mouse scroll
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			/*
			 *  @param[in] window The window that received the event.
			 *  @param[in] xoffset The scroll offset along the x-axis.
			 *  @param[in] yoffset The scroll offset along the y-axis.
			*/

			// TODO: COnsider doubles instead of floats in the event classes
			MouseScrolledEvent event((float)xoffset, (float)yoffset);
			data.EventCallback(event);
		});

		
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
		});

		
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		m_Context->SwapBuffers();
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
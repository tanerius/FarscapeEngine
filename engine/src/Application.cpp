#include "fspch.h"
#include "Farscape/Engine/Application.h"
#include "Farscape/Events/ApplicationEvent.h"
#include <GLFW/glfw3.h>

namespace Farscape {
	Application::Application()
	{
		m_Window = Window::Create();
	}


	Application::~Application()
	{
	}


	void Application::Execute()
	{
		while (m_IsRunning)
		{
			//glClearColor(1, 0, 1, 1);
			//glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}
}
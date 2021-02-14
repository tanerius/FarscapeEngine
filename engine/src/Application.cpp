#include "fspch.h"
#include "Farscape/Engine/Application.h"
#include "Farscape/Events/ApplicationEvent.h"
#include <GLFW/glfw3.h>

namespace Farscape {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = Window::Create();
		m_Window->SetEventCallbacks(BIND_EVENT_FN(Application::OnEvent));
	}


	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		FS_CORE_TRACE("{0}", e);
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
	}

	bool Application::OnWindowClose(WindowCloseEvent&)
	{
		m_IsRunning = false;
		return true;
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
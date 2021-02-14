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

	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_layerStack.PushOverlay(overlay);
	}

	void Application::OnEvent(Event& e)
	{
		FS_CORE_TRACE("{0}", e);
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

		for (auto it = m_layerStack.end(); it != m_layerStack.begin(); )
		{
			// handle events backwards so that when a front layer handles an event
			// the back will not get it again. i.e. break before propagating further
			(*--it)->OnEvent(e);
			if (e.Handled())
				break;
		}
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

			// run the onupdate on every layer in the layer stack
			for (Layer* layer : m_layerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}
}
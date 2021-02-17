#include "fspch.h"
#include "Core/Application.h"
#include "Core/ImGuiLayer.h"
#include "Core/Window.h"
#include "Events/ApplicationEvent.h"

#include <glad/glad.h>

namespace Farscape {


	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		FS_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;
		m_Window = Window::Create();
		m_Window->SetEventCallbacks(BIND_EVENT_FN(Application::OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushLayer(m_ImGuiLayer);

	}


	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.PushLayer(layer);
		layer->OnAttach();
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
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			// run the onupdate on every layer in the layer stack
			for (Layer* layer : m_layerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_layerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}
}

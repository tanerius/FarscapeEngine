#pragma once
#include "Core.h"
#include "Window.h"
#include "Farscape/Engine/LayerStack.h"
#include "Farscape/Events/Event.h"

namespace Farscape {
	class WindowCloseEvent;
	class FARSCAPE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Execute();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);

	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		// a platform agnostic window - consider a unique pointer
		Window* m_Window = nullptr;
		bool m_IsRunning = true;
		LayerStack m_layerStack;
	};

	// Should be defined in a client
	Application* CreateApplication();
}
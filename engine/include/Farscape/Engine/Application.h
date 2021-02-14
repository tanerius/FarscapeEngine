#pragma once
#include "Core.h"
#include "Window.h"

namespace Farscape {
	class WindowCloseEvent;
	class FARSCAPE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Execute();

		void OnEvent(Event& e);

	private:
		bool OnWindowClose(WindowCloseEvent& e);
	private:
		// a platform agnostic window - consider a unique pointer
		Window* m_Window = nullptr;
		bool m_IsRunning = true;
	};

	// Should be defined in a client
	Application* CreateApplication();
}
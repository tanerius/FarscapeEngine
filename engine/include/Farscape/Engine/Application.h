#pragma once
#include "Core.h"
#include "Window.h"

namespace Farscape {
	class FARSCAPE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Execute();
	private:
		// a platform agnostic window - consider a unique pointer
		Window* m_Window = nullptr;
		bool m_IsRunning = true;
	};

	// Should be defined in a client
	Application* CreateApplication();
}
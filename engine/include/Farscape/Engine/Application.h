#pragma once
#include "Core.h"

namespace Farscape {
	class FARSCAPE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Execute();
	};

	// Should be defined in a client
	Application* CreateApplication();
}
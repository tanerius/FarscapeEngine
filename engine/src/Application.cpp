#include "fspch.h"
#include "Farscape/Engine/Application.h"
#include "Farscape/Events/ApplicationEvent.h"
#include "Farscape/Engine/Log.h"

namespace Farscape {
	Application::Application()
	{

	}


	Application::~Application()
	{
	}


	void Application::Execute()
	{
		WindowResizeEvent e(1200, 720);
		FS_TRACE(e);
		while (true);
	}
}
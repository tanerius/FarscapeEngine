#include <Farscape.h>
#include <Core/EntryPoint.h>

#include "EditorLayer.h"

class PilotApplication: public Farscape::Application
{
public:
	PilotApplication(const Farscape::ApplicationProps& props)
		: Application(props)
	{
	}

	virtual void OnInit() override
	{
		PushLayer(new Farscape::EditorLayer());
	}
};

Farscape::Application* Farscape::CreateApplication()
{
	return new PilotApplication({"Pilot - The Farscape Engine Editor", 1600, 900});
}
#include <Farscape.h>
#include <Core/EntryPoint.h>

#include "EditorLayer.h"

class HazelnutApplication : public Farscape::Application
{
public:
	HazelnutApplication(const Farscape::ApplicationProps& props)
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
	return new HazelnutApplication({"Pilot - Farscape Editor", 1600, 900});
}
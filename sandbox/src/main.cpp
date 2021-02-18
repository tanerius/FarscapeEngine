#include "Farscape.h"

// create an example layer
class ExampleLayer : public Farscape::Layer
{
public:
	ExampleLayer()
		: Layer("Example") {}

	void OnUpdate() override
	{
		//FS_INFO("ExampleLayer::Update");
		if (Farscape::Input::IsKeyPressed(FS_KEY_TAB))
			FS_TRACE("PRESSING TAB...");
	}

	void OnEvent(Farscape::Event& event) override
	{
		//FS_TRACE("{0}", event);
	}
};

class Sandbox : public Farscape::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		//ushLayer(new Farscape::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Farscape::Application* Farscape::CreateApplication()
{
	return new Sandbox();
}
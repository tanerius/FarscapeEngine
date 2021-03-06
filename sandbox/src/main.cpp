#include "Farscape.h"
#include <Core/EntryPoint.h>

#include <imgui.h>




class Sandbox : public Farscape::Application
{
public:
    Sandbox()
    {
        //PushLayer(new ExampleLayer());
        //PushLayer(new DemoLayer2D());
    }

    ~Sandbox()
    {

    }
};

Farscape::Application* Farscape::CreateApplication()
{
    return new Sandbox();
}
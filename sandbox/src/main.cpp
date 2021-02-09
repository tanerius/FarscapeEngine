#include "Farscape/Farscape.h"

class Sandbox : public Farscape::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Farscape::Application* Farscape::CreateApplication()
{
	return new Sandbox();
}
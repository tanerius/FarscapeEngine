#pragma once

extern Farscape::Application* Farscape::CreateApplication();

#if defined(_WIN32)

int main(int argc, char** argv)
{
	Farscape::Log::Init();
	auto app = Farscape::CreateApplication();
	app->Execute();
	delete app;
	return 0;
}

#else

int main(int argc, char** argv)
{
	Farscape::Log::Init();
	auto app = Farscape::CreateApplication();
	app->Execute();
	delete app;
	return 0;
}

#endif
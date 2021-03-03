#pragma once

extern Farscape::Application* Farscape::CreateApplication();
extern void Farscape::Initialize();

#if defined(_WIN32)

int main(int argc, char** argv)
{
    Farscape::Initialize();
    auto app = Farscape::CreateApplication();
    app->Execute();
    delete app;
    return 0;
}

#else

int main(int argc, char** argv)
{
    Farscape::Initialize();
    auto app = Farscape::CreateApplication();
    app->Execute();
    delete app;
    return 0;
}

#endif
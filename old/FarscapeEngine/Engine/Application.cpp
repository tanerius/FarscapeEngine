//
//  Application.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/25/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#include "Application.h"
#include "Core/Event.h"
#include "States/PlayingState.h"
#include "Core/TestGL.h"

void Farscape::Application::Test()
{
    TestDraw(m_Context->GetContext().GLFWWindowPtr);
}

void Farscape::Application::popState()
{
    m_isPopState = true;
}

Farscape::Application::Application(std::string&& name)
{
    // Context must come first
    m_Context = new Farscape::ContextWrapper(name, 1280, 720);
    printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));
    m_TimeSinceAppStart = glfwGetTime();
    glfwSetTime(0);
}

void Farscape::Application::Start()
{
    Initialize();
    RunMainLoop();
    Shutdown();
}

void Farscape::Application::Initialize()
{
    m_quad = new Farscape::QuadRenderer();
    m_masterRenderer = new Farscape::MasterRenderer(m_quad);
    m_events = Farscape::Event::GetInstance();
    m_Context->ShowStartupInfo();
    m_camera = new Farscape::Camera();
    
    if (!m_Context->GetContext().hasContext)
    {
        printf("Error: Could not get a context ready\n");
        exit(0);
    }
    ShutdownRequested = false;
    pushState<PlayingState>(*this);
}

void Farscape::Application::RunMainLoop()
{
    // Start main loop
    double currentFrame;
    double lastFrame = 0.0;
    double deltaTime = 0.0;
    
    
    
    while(!ShutdownRequested && !m_states.empty())
    {
        
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        auto& state = *m_states.back();
        
        state.HandleInput();
        state.Update(deltaTime);
        m_camera->Update();
        state.Render(m_masterRenderer);
        m_masterRenderer->FinishRender(m_camera);
        
        HandleEvents();
        
        // This swaps the frame buffer
        m_Context->Update();
        
        if (m_isPopState)
        {
            m_isPopState = false;
            m_states.pop_back();
        }
    }
}

void Farscape::Application::HandleEvents()
{
    if (m_events->CheckPressed(GLFW_KEY_ESCAPE)){
        ShutdownRequested = true;
    }
    
    if (m_events->CheckOncePressed(GLFW_KEY_I)){
        EnableContextInfo = !EnableContextInfo;
        m_Context->SetShowInfo(EnableContextInfo);
    }
    
    // Toggle full screen mode
    if (m_events->CheckOncePressed(GLFW_KEY_F)){
        // TODO: fix this 
        m_Context->ToggleFullscreen();
    }
}

void Farscape::Application::Shutdown()
{
    // Shutdown/cleam the context
    m_Context->Shutdown();
    delete m_Context;
}


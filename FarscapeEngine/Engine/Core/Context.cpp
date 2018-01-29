//
//  Context.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/25/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//


#include "Context.h"

#ifdef WINDOWS
#include<windows.h>
#endif
#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <string>

#include "Event.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void Farscape::ContextWrapper::Shutdown()
{
    assert(m_context.GLFWWindowPtr != 0);
    // Destroy the display
    glfwDestroyWindow(m_context.GLFWWindowPtr);
    glfwTerminate();
    m_context.GLFWWindowPtr = 0;
}

void Farscape::ContextWrapper::ToggleFullscreen()
{
    m_isFullscreen = !m_isFullscreen;
    if(m_isFullscreen)
    {
        GLFWmonitor* CurrentMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* VideoMode = glfwGetVideoMode(CurrentMonitor);
        
        glfwSetWindowMonitor(    m_context.GLFWWindowPtr,
                                      glfwGetPrimaryMonitor(),
                                      0,
                                      0,
                                      m_context.ScreenWidth,
                                      m_context.ScreenHeight,
                                      VideoMode->refreshRate
                             );
    }
    else
    {
        
        glfwSetWindowMonitor(m_context.GLFWWindowPtr,
                             NULL,
                             0,
                             0,
                             m_context.ScreenWidth,
                             m_context.ScreenHeight,
                             GLFW_DONT_CARE
                             );
    }
}

void Farscape::ContextWrapper::ShowContextInfo()
{
    double current_seconds;
    
    current_seconds = glfwGetTime ();
    delta_time = current_seconds - previous_seconds;
    if (delta_time > 0.25) {
        double fps;
        char tmp[256];
        
        previous_seconds = current_seconds;
        fps = (double)frame_count / delta_time;
        sprintf (tmp, "%s - fps: %.2f; GLSL ver: %s; openGL: %s",
                 m_windowTitle.c_str(),
                 fps,
                 glGetString (GL_SHADING_LANGUAGE_VERSION),
                 glGetString(GL_VERSION));
        glfwSetWindowTitle (m_context.GLFWWindowPtr, tmp);
        frame_count = 0;
    }
    frame_count++;
}

Farscape::ContextWrapper::ContextWrapper(const std::string& name, const int& w, const int& h)
{
    m_context.ScreenHeight = h;
    m_context.ScreenWidth = w;
    m_context.AspectRatio = (float)w / (float)h;
    m_windowTitle = name;
    // Creating a display - make sure there isnt one already
    assert(m_context.GLFWWindowPtr == 0);
    
    // Initialize GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        exit(EXIT_FAILURE);
    }
    
    // Setup cnotext and window properties/hints
    #ifdef APPLE
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Try 4
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1); // try 1
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #endif
    glfwWindowHint (GLFW_SAMPLES, 4);
    
    // Create a window to put our stuff in.
    m_context.GLFWWindowPtr = glfwCreateWindow(m_context.ScreenWidth, m_context.ScreenHeight, m_windowTitle.c_str(), NULL, NULL);
    
    if( m_context.GLFWWindowPtr == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. \n" );
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    // Make the newly created window the current context
    glfwMakeContextCurrent(m_context.GLFWWindowPtr);
    
    // Set the Keyboard event callback
    glfwSetKeyCallback(m_context.GLFWWindowPtr, Farscape::Event::KeyCallback);
    glfwSetErrorCallback(Farscape::Event::ErrorCallback);
    
    // Initialize GLEW
    glewExperimental = GL_TRUE; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        exit(EXIT_FAILURE);
    }
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(m_context.GLFWWindowPtr, GLFW_STICKY_KEYS, GL_TRUE);
    
    // Set the hasContext flag to indicate that we can now work with a window
    m_context.hasContext = true;
}

void Farscape::ContextWrapper::Update()
{
    assert(m_context.GLFWWindowPtr != 0);
    // Swap the buffers so that what we drew will appear on the screen.
    glfwSwapBuffers(m_context.GLFWWindowPtr);
    glfwPollEvents();
    if (m_showInfo)
    {
        ShowContextInfo();
        m_UpdateTitle = true;
    }
    else {
        if (m_UpdateTitle)
        {
            char tmp[256];
            sprintf (tmp, "%s ", m_windowTitle.c_str());
            glfwSetWindowTitle (m_context.GLFWWindowPtr, tmp);
            m_UpdateTitle = false;
        }
    }
}

void Farscape::ContextWrapper::ShowStartupInfo()
{
    printf("GL Information:\n");
    printf("Supported GL version: %s \n",glGetString(GL_VERSION));
    printf("Supported shading lang: %s \n",glGetString (GL_SHADING_LANGUAGE_VERSION));
    printf("Current GL vendor: %s \n",glGetString(GL_VENDOR));
    printf("Current GL renderer: %s \n",glGetString(GL_RENDERER));
    
    GLint num=0;
    GLuint i;
    glGetIntegerv(GL_NUM_EXTENSIONS, &num);
    printf("GL extensions supported: %d\n", num);
    if (num < 1) {
        return;
    }
    
    for (i=0; i<(GLuint)num; i++) {
        const GLubyte *ext=glGetStringi(GL_EXTENSIONS,i);
        if (ext) {
            printf("  %s\n",ext);
        }
    }
}


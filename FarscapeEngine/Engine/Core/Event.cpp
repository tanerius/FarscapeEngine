//
//  Event.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/26/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#include "Event.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

bool Farscape::Event::HandledKeys[MAX_HANDLED_KEYS];

void Farscape::Event::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        HandledKeys[key] = true;
    }
    else if(action == GLFW_RELEASE)
    {
        HandledKeys[key] = false;
    }
    
    if(HandledKeys[GLFW_KEY_ESCAPE])
        glfwSetWindowShouldClose(window, GL_TRUE);
}

void Farscape::Event::ErrorCallback(int error, const char* description)
{
    // TODO: This event callback is called everytime an error happens in context. Do something informative here
}

bool Farscape::Event::CheckPressed(const int& key)
{
    return HandledKeys[key];
}

bool Farscape::Event::CheckOncePressed(const int& key)
{
    bool ret = HandledKeys[key];
    HandledKeys[key] = false;
    
    return ret;
}

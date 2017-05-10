#include "cgcallback.hpp"
#ifdef WINDOWS
#include<windows.h>
#endif
#include <cstdio>

#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace CGCore{

bool HandledKeys[MAX_HANDLED_KEYS];
double LastMouseX;
double LastMouseY;
bool FirstMouseEvent;
float MouseSensitivity;
double MouseOffsetX;
double MouseOffsetY;

TimePoint t1;
TimePoint t2; 
Duration time_span;

    
}

void CGCore::InitHighPrecisionTimers()
{
    CGCore::t1 = CGCore::Clock::now();
    CGCore::t2 = CGCore::Clock::now();
    CGCore::time_span = std::chrono::duration_cast<CGCore::Duration>(CGCore::t2 - CGCore::t1);
}

void CGCore::GetTimePassed(const char* m)
{
    CGCore::t2 = CGCore::Clock::now();
    CGCore::time_span = std::chrono::duration_cast<CGCore::Duration>(CGCore::t2 - CGCore::t1);
    printf("%s: %f s\n ", m, CGCore::time_span.count());
    CGCore::t1 = CGCore::Clock::now();
}

void CGCore::CGCallbacks::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        CGCore::HandledKeys[key] = true;
    } 
    else if(action == GLFW_RELEASE)
    {
        CGCore::HandledKeys[key] = false;
    }
}


void CGCore::CGCallbacks::MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if(CGCore::FirstMouseEvent)
    {
        CGCore::LastMouseX = xpos;
        CGCore::LastMouseY = ypos;
        CGCore::FirstMouseEvent = false;
    }
    
    CGCore::MouseOffsetX = xpos - CGCore::LastMouseX;
    CGCore::MouseOffsetY = CGCore::LastMouseY - ypos;
    CGCore::LastMouseX = xpos;
    CGCore::LastMouseY = ypos;
    
    if ((CGCore::MouseOffsetX > 0.000001f) || (CGCore::MouseOffsetX < -0.000001f))
    {
        CGCore::MouseOffsetX *= CGCore::MouseSensitivity;
    }
    else{
        CGCore::MouseOffsetX = 0.000000001f;
    }
    
    if ((CGCore::MouseOffsetY > 0.000001f) || (CGCore::MouseOffsetY < -0.000001f))
    {
        CGCore::MouseOffsetY *= CGCore::MouseSensitivity;
    }
    else{
        CGCore::MouseOffsetY = 0.000000001f;
    }

    
    //printf("Mouse( %f, %f ) \n",CGCore::MouseOffsetX,CGCore::MouseOffsetY);
}

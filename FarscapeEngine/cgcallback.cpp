#include "cgcallback.hpp"
#ifdef WINDOWS
#include<windows.h>
#endif
#include <cstdio>

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
    
    CGCore::MouseOffsetX *= CGCore::MouseSensitivity;
    CGCore::MouseOffsetY *= CGCore::MouseSensitivity;
    printf("Mouse( %f, %f ) \n",CGCore::MouseOffsetX,CGCore::MouseOffsetY);
}

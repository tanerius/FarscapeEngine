#include "cgcallback.hpp"
#ifdef WINDOWS
#include<windows.h>
#endif
#include <cstdio>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace CGCore{
bool HandledKeys[MAX_HANDLED_KEYS];
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
    printf("Mouse( %f, %f ) \n",xpos,ypos);
}

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
    /*
    if ((action == GLFW_PRESS) && (key == GLFW_KEY_Z))
    {
        for(int c=0;c<200;c++)
        {
            printf("Key %d = Val(%d)\n",c,CGCore::HandledKeys[c]);
        }
    }

    if ((action == GLFW_PRESS) && (key == GLFW_KEY_X))
    {
        printf("Pointer %ul \n",CGCore::HandledKeys);
    }
    */
}
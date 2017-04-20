//
//  cgcallback.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/20/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#ifndef cgcallback_hpp
#define cgcallback_hpp

#ifdef USE_GLM
    #include <glm/glm.hpp>
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Definitions for the callbacks
class CGCallbacks
{
    protected:
    GLFWwindow* GLFWWindowPtr = 0; // will hold our window pointer

    public:
    static void ErrorCallback(int error, const char* description)
    {
        fputs(description, stderr);
    }

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
    }

    GLFWwindow* GetWindow() const { return GLFWWindowPtr; }

    // Override in classes where the Keycallback needs to send event info
    virtual void Move(int key, int scancode, int action, int mods) { return; };
};

#endif
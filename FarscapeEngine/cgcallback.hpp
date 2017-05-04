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

#ifdef WINDOWS
#include<windows.h>
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define MAX_HANDLED_KEYS 1024

namespace CGCore
{
    extern bool HandledKeys[MAX_HANDLED_KEYS];
    extern double LastMouseX;
    extern double LastMouseY;
    extern bool FirstMouseEvent;
    extern float MouseSensitivity;
    extern double MouseOffsetX;
    extern double MouseOffsetY;
    
    // Definitions for the callbacks
    class CGCallbacks
    {
        protected:
        GLFWwindow* GLFWWindowPtr = 0; // will hold our window pointer
        
        public:

        static void ErrorCallback(int error, const char* description)
        {
            // printf("ERROR %d: %s",error,description);
        }

        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void MouseCallback(GLFWwindow* window, double xpos, double ypos);

        GLFWwindow* GetWindow() const { return GLFWWindowPtr; }

    };
}

#endif

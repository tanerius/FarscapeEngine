//
//  cgcamera.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/20/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#include "cgcamera.hpp"
#include "cghelper.hpp"
#include "cgdisplay.hpp"

#ifdef WINDOWS
    #include<windows.h>
#endif

#ifdef USE_GLM
    #include <glm/glm.hpp>
#endif

#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

CGCore::Camera::Camera(CGCore::DisplayManager* D)
{
    assert(Position == nullptr);
    Position = new glm::vec3(0.0f, 0.0f, 0.0f);
    Display = D;
}


CGCore::Camera::~Camera()
{
    delete Position;
    Position = nullptr;
}


glm::mat4 CGCore::Camera::GetViewMatrix() const
{
    glm::mat4 VM = CGCore::CreateViewMatrix(*Position, glm::vec3(Pitch, Yaw, Roll));
    return VM;
}


void CGCore::Camera::Move()
{
    int state = glfwGetKey(Display->GetWindow(), GLFW_KEY_W);
    if (state == GLFW_PRESS)
    {
        // Up key pressed
        Position->z -= 0.02f; 
    }

    state = glfwGetKey(Display->GetWindow(), GLFW_KEY_S);
    if (state == GLFW_PRESS)
    {
        // Up key pressed
        Position->z += 0.02f; 
    }

    state = glfwGetKey(Display->GetWindow(), GLFW_KEY_A);
    if (state == GLFW_PRESS)
    {
        // Up key pressed
        Position->x -= 0.02f; 
    }

    state = glfwGetKey(Display->GetWindow(), GLFW_KEY_D);
    if (state == GLFW_PRESS)
    {
        // Up key pressed
        Position->x += 0.02f; 
    }
}
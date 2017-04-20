//
//  cgcamera.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/20/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#include "cgcamera.hpp"

#include "cghelper.hpp"

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

CGCore::Camera::Camera(DisplayManager* D)
{
    assert(Position == nullptr)
    Position = new glm::vec3(0.0f, 0.0f, 0.0f);
    Display = D;
}


CGCore::Camera::~Camera()
{
    delete Position;
    Position = nullptr;
}

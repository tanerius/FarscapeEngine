//
//  cgcamera.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/20/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#include "cgcamera.hpp"

#ifdef WINDOWS
    #include<windows.h>
#endif

#ifdef USE_GLM
    #include <glm/glm.hpp>
#endif

#include <string>
#include <GL/glew.h>


void CGCore::Camera::MoveLeft(GLfloat cameraSpeed)
{
    pos -= glm::normalize(glm::cross(forward, up)) * cameraSpeed;
}


void CGCore::Camera::MoveRight(GLfloat cameraSpeed)
{
    pos += glm::normalize(glm::cross(forward, up)) * cameraSpeed;
}


void CGCore::Camera::MoveIn(GLfloat cameraSpeed)
{
    pos += cameraSpeed * forward;
}

void CGCore::Camera::MoveBack(GLfloat cameraSpeed)
{
    pos -= cameraSpeed * forward;
}


void CGCore::Camera::MoveUp(GLfloat cameraSpeed)
{
    pos += cameraSpeed * up;
}

void CGCore::Camera::MoveDown(GLfloat cameraSpeed)
{
    pos -= cameraSpeed * up;
}


void CGCore::Camera::Roll(int direction)
{
    // do roll
}

void CGCore::Camera::Pitch(int direction)
{
    // do pitch
}


void CGCore::Camera::Yaw(int direction)
{
    // do yaw
}



void CGCore::Camera::Reposition(glm::vec3& positionDelta)
{
    pos.x += positionDelta.x;
    pos.y += positionDelta.y;
    pos.z += positionDelta.z;
    return;
}


std::string CGCore::Camera::ToString() const
{
    std::string x = "Camera {\n";
#ifndef WINDOWS
    x = x + "ProjectionMatrix \n{\n";

    for(int j = 0; j < 4; j++)
    {
        for(int i = 0; i < 4; i++)
        {
            x += std::to_string(projection[i][j]) + "\t";
        }
        x += "\n";
    }
    x += "}\nPos(";
    x += std::to_string(pos.x) + ", " + std::to_string(pos.y) + ", " + std::to_string(pos.z) +")\n";
    x += "Fwd(";
    x += std::to_string(forward.x) + ", " + std::to_string(forward.y) + ", " + std::to_string(forward.z) +")\n";
    x += "Up(";
    x += std::to_string(up.x) + ", " + std::to_string(up.y) + ", " + std::to_string(up.z) +")\n";
#endif
    x += "}\n";

    return x;
}










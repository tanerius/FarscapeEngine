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

void CGCore::Camera::Rotate(const glm::vec3 angles)
{
    rotation += angles;
    
    
    if(rotation.x > 89.0f)
        rotation.x = 89.0f;
    if(rotation.x < -89.0f)
        rotation.x = -89.0f;
    
    glm::vec3 front;
    front.x = cos(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    front.y = sin(glm::radians(rotation.x));
    front.z = sin(glm::radians(rotation.y)) * cos(glm::radians(rotation.x));
    forward = glm::normalize(front);
}


void CGCore::Camera::Zoom(GLfloat zoomLevel)
{
    // printf("%f ->",this->fov);
    this->m_fov += zoomLevel;
    if(this->m_fov <= 1.0f)
        this->m_fov = 1.0f;
    if(this->m_fov >= 45.0f)
        this->m_fov = 45.0f;
    // printf(" %f \n...",this->fov);
    this->projection = glm::perspective(this->m_fov, this->m_aspect, this->m_near, this->m_far);
}


void CGCore::Camera::Roll(GLfloat angle)
{
    // do roll
    Rotate(glm::vec3(0.0f, 0.0f, angle));
}

void CGCore::Camera::Pitch(GLfloat angle)
{
    // do pitch
    Rotate(glm::vec3(angle, 0.0f, 0.0f));
}


void CGCore::Camera::Yaw(GLfloat angle)
{
    // do yaw
    Rotate(glm::vec3(0.0f, angle, 0.0f));
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










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


void CGCore::Camera::MoveLeft()
{
    glm::vec3 m(-MOVE_SPEED, 0.0f, 0.0f);
    Reposition(m);
}


void CGCore::Camera::MoveRight()
{
    glm::vec3 m(MOVE_SPEED, 0.0f, 0.0f);
    Reposition(m);
}


void CGCore::Camera::MoveUp()
{
    glm::vec3 m(0.0f, MOVE_SPEED, 0.0f);
    Reposition(m);
}

void CGCore::Camera::MoveDown()
{
    glm::vec3 m(0.0f, -MOVE_SPEED, 0.0f);
    Reposition(m);
}


void CGCore::Camera::MoveIn()
{
    glm::vec3 m(0.0f, 0.0f, MOVE_SPEED);
    Reposition(m);
}

void CGCore::Camera::MoveBack()
{
    glm::vec3 m(0.0f, 0.0f, -MOVE_SPEED);
    Reposition(m);
}

void CGCore::Camera::Roll(int direction)
{
    (direction < 0)?(this->up.x +=  MOVE_SPEED):(this->up.x -=  MOVE_SPEED);
}

void CGCore::Camera::Pitch(int direction)
{
    (direction < 0)?(this->forward.y +=  MOVE_SPEED):(this->forward.y -=  MOVE_SPEED);
}


void CGCore::Camera::Yaw(int direction)
{
    (direction < 0)?(this->forward.x +=  MOVE_SPEED):(this->forward.x -=  MOVE_SPEED);
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










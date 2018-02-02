//
//  Player.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#include "Player.h"
#include "../Core/Event.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtx/string_cast.hpp>

Farscape::Player::Player()
: Transform(Vector3d(0.0f , 0.0f , -5.0f),Vector3d(0.0f , 0.0f , 0.0f), Vector3d(1.0f , 1.0f , 1.0f))
{
    
}

void Farscape::Player::HandleInput()
{
    KeyboardInput();
    MouseInput();
}

void Farscape::Player::Update(float dt)
{
    // Slow down velocity over time
    AddPos(m_velocity * dt);

    // reset velocity
    m_velocity *= 0.95;
    
}

void Farscape::Player::KeyboardInput()
{
    Vector3d change = {0,0,0};
    float speed = 0.5;
    Event* m_events = Farscape::Event::GetInstance();
    
    
    if (m_events->CheckPressed(GLFW_KEY_W)){
        change.x += glm::cos(glm::radians(GetRot().y + 90)) * speed;
        change.z += glm::sin(glm::radians(GetRot().y + 90)) * speed;
    }
    
    // Toggle full screen mode
    if (m_events->CheckPressed(GLFW_KEY_S)){
        change.x += -glm::cos(glm::radians(GetRot().y + 90)) * speed;
        change.z += -glm::sin(glm::radians(GetRot().y + 90)) * speed;
    }
    if (m_events->CheckPressed(GLFW_KEY_A))
    {
        change.x += glm::cos(glm::radians(GetRot().y)) * speed;
        change.z += glm::sin(glm::radians(GetRot().y)) * speed;
    }
    if (m_events->CheckPressed(GLFW_KEY_D))
    {
        change.x += -glm::cos(glm::radians(GetRot().y)) * speed;
        change.z += -glm::sin(glm::radians(GetRot().y)) * speed;
    }
    
    
    m_velocity += change;

}

void Farscape::Player::MouseInput()
{
    Event* m_events = Farscape::Event::GetInstance();
    static auto const BOUND = 80;
    double deltaX, deltaY;
    // get mouse coords
    m_events->GetDeltaMouseXY(deltaX, deltaY);
    
    
    AddRot(Vector3d(deltaX * 0.05));
    AddRot(Vector3d(deltaY * 0.05));
    
    Vector3d temp;
    if      (GetRot().x >  BOUND)
    {
        temp = GetRot();
        temp.x = BOUND;
        SetRot(temp);
    }
    else if (GetRot().x < -BOUND)
    {
        temp = GetRot();
        temp.x = -BOUND;
        SetRot(temp);
        
    }
    
    if      (GetRot().y >  360)
    {
        temp = GetRot();
        temp.y = 0;
        SetRot(temp);
    }
    else if (GetRot().y < 0)
    {
        temp = GetRot();
        temp.x = 360;
        SetRot(temp);
        
    }
    
}


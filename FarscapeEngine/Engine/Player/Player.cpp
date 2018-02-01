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

Farscape::Player::Player()
{
    position = Vector3d(0.0f , 0.0f , -5.0f);
}

void Farscape::Player::HandleInput()
{
    KeyboardInput();
    MouseInput();
}

void Farscape::Player::Update(float dt)
{
    // Slow down velocity over time
    position += m_velocity * dt;
    // reset velocity
    m_velocity *= 0.95;
}

void Farscape::Player::KeyboardInput()
{
    Vector3d change = {0,0,0};
    float speed = 0.5;
    Event* m_events = Farscape::Event::GetInstance();
    
    if (m_events->CheckPressed(GLFW_KEY_W)){
        change.x = glm::cos(glm::radians(rotation.y + 90)) * speed;
        change.z = glm::sin(glm::radians(rotation.y + 90)) * speed;
        printf("Pressed W\n");
    }
    if (m_events->CheckPressed(GLFW_KEY_S)){
        change.x = -glm::cos(glm::radians(rotation.y + 90)) * speed;
        change.z = -glm::sin(glm::radians(rotation.y + 90)) * speed;
        printf("Pressed S\n");
    }
    if (m_events->CheckPressed(GLFW_KEY_A)){
        change.x = glm::cos(glm::radians(rotation.y)) * speed;
        change.z = glm::sin(glm::radians(rotation.y)) * speed;
        printf("Pressed A\n");
    }
    if (m_events->CheckPressed(GLFW_KEY_D)){
        change.x = -glm::cos(glm::radians(rotation.y)) * speed;
        change.z = -glm::sin(glm::radians(rotation.y)) * speed;
        printf("Pressed D\n");
    }
    
    
    
    
    m_velocity += change;
}

void Farscape::Player::MouseInput()
{
    
}


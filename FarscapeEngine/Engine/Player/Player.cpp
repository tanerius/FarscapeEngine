//
//  Player.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#include "Player.h"

Farscape::Player::Player()
{
    position = {0, 0, -5};
}

void Farscape::Player::HandleInput()
{
    KeyboardInput();
    MouseInput();
}

void Farscape::Player::Update(float dt)
{
    position += m_velocity * dt;
    m_velocity *= 0.95;
}

void Farscape::Player::KeyboardInput()
{
    Vector3d change = {0,0,0};
    //float speed = 0.5;
    
    
    m_velocity += change;
}

void Farscape::Player::MouseInput()
{
    
}


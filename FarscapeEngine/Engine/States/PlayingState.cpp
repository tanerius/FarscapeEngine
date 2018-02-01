//
//  PlayingState.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#include "PlayingState.h"

#include "../Renderer/MasterRenderer.h"
#include "../Application.h"


Farscape::PlayingState::PlayingState(Farscape::Application& app)
:   StateBase   (app)
{
    m_player = new Farscape::Player();
    app.GetCamera()->HookEntity(m_player);
}

Farscape::PlayingState::~PlayingState()
{
    // release memory
    delete m_player;
}

void Farscape::PlayingState::HandleEvent()
{
    
}

void Farscape::PlayingState::HandleInput()
{
    m_player->HandleInput();
}

void Farscape::PlayingState::Update(float deltaTime)
{
    m_player->Update(deltaTime);
}

void Farscape::PlayingState::Render(MasterRenderer* renderer)
{
    renderer->DrawMesh(Vector3d(0.0f, 0.0f, 0.0f));
}

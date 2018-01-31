//
//  Camera.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#include "Camera.h"

#include "../Math/Matrix.h"

Farscape::Camera::Camera()
{
    m_projectionMatrix = Farscape::Matrix::MakeProjectionMatrix(90.0f,              // field of view
                                                                1280.0f / 720.0f,   // w/h aspect ratio
                                                                0.1f,               // near
                                                                1000.0f);           // far
    
    position = {0, 0, -3.5};
}

void Farscape::Camera::Update()
{
    position = m_pEntity->position;
    rotation = m_pEntity->rotation;
    
    //m_viewMatrix = Farscape::Matrix::CreateCameraViewMatrix(position, rotation);
    m_viewMatrix = glm::lookAt(position, Vector3d(0.0f, 0.0f, 0.0f), Vector3d(0.0f, 1.0f, 0.0f));
    m_projViewMatrx = m_projectionMatrix * m_viewMatrix;
}

// Attach the camera to the player
void Farscape::Camera::HookEntity(const Entity& entity)
{
    m_pEntity = &entity;
}

const glm::mat4& Farscape::Camera::GetViewMatrix() const noexcept
{
    return m_viewMatrix;
}

const glm::mat4& Farscape::Camera::GetProjMatrix() const noexcept
{
    return m_projectionMatrix;
}

const glm::mat4& Farscape::Camera::GetProjectionViewMatrix() const noexcept
{
    return m_projViewMatrx;
}

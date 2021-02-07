//
//  Camera.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#include "Camera.h"

#include "../Math/Matrix.h"
#include <glm/gtx/string_cast.hpp>

void Farscape::Camera::AdjustCamera()
{
    
    
   
}

Farscape::Camera::Camera()
{
    m_projectionMatrix = Farscape::Matrix::MakeProjectionMatrix(90.0f,              // field of view
                                                                1280.0f / 720.0f,   // w/h aspect ratio
                                                                0.1f,               // near
                                                                300.0f);           // far
    
    this->forward = Vector3d(0.0f, 0.0f, 1.0f);
    this->up = Vector3d(0.0f, 1.0f, 0.0f);
    this->projection = Farscape::Matrix::MakeProjectionMatrix(90.0f,              // field of view
                                                              1280.0f / 720.0f,   // w/h aspect ratio
                                                              0.1f,               // near
                                                              300.0f);           // far
    this->m_fov = 90.0f;
    this->m_aspect = 1280.0f / 720.0f;
    this->m_near = 0.1f;
    this->m_far = 300.0f;
    
    position = Vector3d(0.0f, 0.0f, -5.0f);
    rotation = Vector3d(0.0f, 89.0f, 0.0f);
    scale = Vector3d(1.0f, 1.0f, 1.0f);

}

void Farscape::Camera::Update()
{
    position = m_pTransform->GetPos();
    Rotate(m_pTransform->GetRot());
    // set player to face the same way as camera
    //m_pTransform->SetPos(rotation);
    
    
}

// Attach the camera to the player
void Farscape::Camera::HookEntity(Farscape::Transform* t)
{
    m_pTransform = t;
}

const glm::mat4 Farscape::Camera::GetViewMatrix() const noexcept
{
    return glm::lookAt(position, position + forward, up);
}

const glm::mat4 Farscape::Camera::GetProjMatrix() const noexcept
{
    return projection;
}

const glm::mat4 Farscape::Camera::GetProjectionViewMatrix() const noexcept
{
    return GetProjMatrix() * GetViewMatrix();
}

////////////////////////// my implementation

void Farscape::Camera::MoveLeft(float cameraSpeed)
{
    position -= glm::normalize(glm::cross(forward, up)) * cameraSpeed;
}


void Farscape::Camera::MoveRight(float cameraSpeed)
{
    position += glm::normalize(glm::cross(forward, up)) * cameraSpeed;
}


void Farscape::Camera::MoveIn(float cameraSpeed)
{
    position += cameraSpeed * forward;
}

void Farscape::Camera::MoveBack(float cameraSpeed)
{
    position -= cameraSpeed * forward;
}


void Farscape::Camera::MoveUp(float cameraSpeed)
{
    position += cameraSpeed * up;
}

void Farscape::Camera::MoveDown(float cameraSpeed)
{
    position -= cameraSpeed * up;
}

void Farscape::Camera::Rotate(const Vector3d angles)
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


void Farscape::Camera::Zoom(float zoomLevel)
{

    this->m_fov += zoomLevel;
    if(this->m_fov <= 1.0f)
        this->m_fov = 1.0f;
    if(this->m_fov >= 45.0f)
        this->m_fov = 45.0f;

    this->projection = glm::perspective(this->m_fov, this->m_aspect, this->m_near, this->m_far);
}


void Farscape::Camera::Roll(float angle)
{
    // do roll
    Rotate(glm::vec3(0.0f, 0.0f, angle));
}

void Farscape::Camera::Pitch(float angle)
{
    // do pitch
    Rotate(glm::vec3(angle, 0.0f, 0.0f));
}


void Farscape::Camera::Yaw(float angle)
{
    // do yaw
    Rotate(glm::vec3(0.0f, angle, 0.0f));
}



void Farscape::Camera::Reposition(Vector3d& positionDelta)
{
    position.x += positionDelta.x;
    position.y += positionDelta.y;
    position.z += positionDelta.z;
    return;
}

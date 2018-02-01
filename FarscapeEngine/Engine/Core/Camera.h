//
//  Camera.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef Camera_h
#define Camera_h

#include "Entity.h"

namespace Farscape {
    class Camera : public Entity
    {
    public:
        Camera();
        
        void Update();
        // member that attaches a camera to the player
        void HookEntity(const Entity* entity);
        
        const glm::mat4 GetViewMatrix ()           const noexcept;
        const glm::mat4 GetProjMatrix ()           const noexcept;
        const glm::mat4 GetProjectionViewMatrix () const noexcept;
        
        
        void MoveLeft(float cameraSpeed);
        void MoveRight(float cameraSpeed);
        void MoveIn(float cameraSpeed);
        void MoveBack(float cameraSpeed);
        void MoveUp(float cameraSpeed);
        void MoveDown(float cameraSpeed);
        void Rotate(const Vector3d angles);
        void Zoom(float zoomLevel);
        void Roll(float angle);
        void Pitch(float angle);
        void Yaw(float angle);
        void Reposition(Vector3d& positionDelta);
        
        
    private:
        const Entity* m_pEntity;
        glm::mat4 projection;
        glm::vec3 forward;
        glm::vec3 up;

        float m_fov; // Field of view
        float m_aspect;
        float m_near;
        float m_far;
        
        glm::mat4 m_projectionMatrix;
        glm::mat4 m_viewMatrix;
        glm::mat4 m_projViewMatrx;
        
        
    };
}

#endif /* Camera_h */

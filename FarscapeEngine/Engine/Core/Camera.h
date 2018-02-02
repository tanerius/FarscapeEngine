//
//  Camera.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef Camera_h
#define Camera_h


#include "Transform.h"

namespace Farscape {
    class Camera
    {
    public:
        Camera();
        
        void Update();
        // member that attaches a camera to the player
        void HookEntity(Transform* transform);
        
        const glm::mat4 GetViewMatrix ()            const noexcept;
        const glm::mat4 GetProjMatrix ()            const noexcept;
        const glm::mat4 GetProjectionViewMatrix ()  const noexcept;
        
        
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
        
        Transform* m_pTransform;
        Matrix4 projection;
        Vector3d forward;
        Vector3d up;
        
        
        Vector3d position;
        Vector3d rotation;
        Vector3d scale;

        float m_fov; // Field of view
        float m_aspect;
        float m_near;
        float m_far;
        
        Matrix4 m_projectionMatrix;
        Matrix4 m_viewMatrix;
        Matrix4 m_projViewMatrx;
        
        
    };
}

#endif /* Camera_h */

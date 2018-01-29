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
        void HookEntity(const Entity& entity);
        
        const glm::mat4& GetViewMatrix ()           const noexcept;
        const glm::mat4& GetProjMatrix ()           const noexcept;
        const glm::mat4& GetProjectionViewMatrix () const noexcept;
        
    private:
        const Entity* m_pEntity;
        
        glm::mat4 m_projectionMatrix;
        glm::mat4 m_viewMatrix;
        glm::mat4 m_projViewMatrx;
        
        
    };
}

#endif /* Camera_h */

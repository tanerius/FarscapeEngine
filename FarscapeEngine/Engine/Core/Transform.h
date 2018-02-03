//
//  Transform.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/29/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef Transform_hpp
#define Transform_hpp

#include "../Math/Definitions.h"
#include "Entity.h"

namespace Farscape {
    // Representation for the transformations
    class Transform
    {
    public:

        Transform(const Vector3d& pos = Vector3d(), const Vector3d& rot = Vector3d(), const Vector3d& scale = Vector3d(1.0f, 1.0f, 1.0f))
        {
            this->position = position;
            this->rotation = rotation;
            this->scale = scale;
        }
        
        
        // Generate transformation matrix
        inline glm::mat4 GetModelMatrix() const
        {
            Matrix4 posMat = glm::translate(position); // Translation matrix
            Matrix4 scaleMat = glm::scale(scale);
            Matrix4 rotX = glm::rotate(rotation.x, Vector3d(1.0, 0.0, 0.0));
            Matrix4 rotY = glm::rotate(rotation.y, Vector3d(0.0, 1.0, 0.0));
            Matrix4 rotZ = glm::rotate(rotation.z, Vector3d(0.0, 0.0, 1.0));
            Matrix4 rotMat = rotX * rotY * rotZ;
            return posMat * rotMat * scaleMat;
        }
        
        
        inline Matrix4 GetMVP(const Matrix4& VP) const
        {
            Matrix4 M = GetModelMatrix();
            
            return VP * M;
            // for camera.GetViewProjection() * GetModel(); do return glm::mat4&
        }
        
        inline const Vector3d& GetPos() { return position; }
        inline const Vector3d& GetRot() { return rotation; }
        inline const Vector3d& GetScale() { return scale; }
        
        inline void SetPos(const Vector3d& pos) { this->position = pos; }
        inline void SetRot(const Vector3d& rot) { this->rotation = rot; }
        inline void SetScale(const Vector3d& scale) { this->scale = scale; }
        
        inline void AddPos(const Vector3d& pos) { this->position += pos; }
        inline void AddRot(const Vector3d& rot) { this->rotation += rot; }
        inline void AddScale(const Vector3d& scale) { this->scale += scale; }
    protected:
    private:
        Vector3d position;
        Vector3d rotation;
        Vector3d scale;
    };
}

#endif /* Transform_hpp */

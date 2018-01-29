//
//  Matrix.hpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/25/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#ifndef Matrix_h
#define Matrix_h

#include "Definitions.h"


namespace Farscape
{
    // This class offers static stuff to deal with making matrices
    class Matrix
    {
    public:
        static Matrix4 CreateTransformationMatrix(
                                                    const Vector3d& Translation,
                                                    const Vector3d& RotAxis,
                                                    const float& RotAngle,
                                                    const Vector3d& Scale
                                                    );
        
        static Matrix4 CreateModelMatrix(
                                        const Vector3d& Position,
                                        const Vector3d& Orientation // (pitch,yaw,roll) angles
        )
        {
            return CreateViewMatrix(Position, Orientation);
        }
        
        static Matrix4 CreateViewMatrix(
                                       const Vector3d& Position,
                                       const Vector3d& Orientation // (pitch,yaw,roll) angles
                                        );
        
        static Matrix4 CreateViewMatrixDefaultPosition(
                                        const Vector3d& Position,
                                        const Vector3d& Rotation // (pitch,yaw,roll) angles
        );
        
        static Matrix4 MakeProjectionMatrix(
                                            const float& fov,
                                            const float& ratio,   // w/h
                                            const float& near,    // 0.5
                                            const float& far)     // 1000
        {
            return glm::perspective(glm::radians(fov), ratio, near, far);
        }
    };
}

#endif /* Matrix_h */

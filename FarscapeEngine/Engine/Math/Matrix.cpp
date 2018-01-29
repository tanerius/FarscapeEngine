//
//  Matrix.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/25/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#include "Matrix.h"

Farscape::Matrix4 Farscape::Matrix::CreateTransformationMatrix(const Vector3d& Translation,
                                                               const Vector3d& RotAxis,
                                                               const float& RotAngle,
                                                               const Vector3d& Scale)
{
    Farscape::Matrix4 TranslationMat = glm::translate(Farscape::Matrix4(1.0f), Translation);
    Farscape::Matrix4 RotMat = glm::rotate(Farscape::Matrix4(1.0f), RotAngle, RotAxis);
    Farscape::Matrix4 ScaleMat = glm::scale(Farscape::Matrix4(1.0f), Scale);
    Farscape::Matrix4 TransformationMat = TranslationMat * RotMat * ScaleMat;
    return TransformationMat;
}

Farscape::Matrix4 Farscape::Matrix::CreateViewMatrix(const Vector3d& Position,
                                                     const Vector3d& Orientation)
{
    Vector3d NegativePos = Vector3d(-1 * Position.x, -1 * Position.y, -1 * Position.z);
    Farscape::Matrix4 T = glm::translate(Farscape::Matrix4(1.0f), NegativePos); // Camera postion
    Farscape::Matrix4 RotMat = glm::rotate(Farscape::Matrix4(1.0), Orientation.x, Vector3d(1.0f,0.0f,0.0f)); // Pitch
    RotMat = glm::rotate(RotMat, Orientation.y, Vector3d(0.0f,1.0f,0.0f)); // Yaw
    RotMat = glm::rotate(RotMat, Orientation.z, Vector3d(0.0f,0.0f,1.0f)); // Roll
    Farscape::Matrix4 ViewMatrix = T * RotMat;
    return ViewMatrix;
}

Farscape::Matrix4 Farscape::Matrix::CreateViewMatrixDefaultPosition(const Vector3d& Position,
                                                     const Vector3d& Rotation)
{
    Farscape::Matrix4 matrix;
    
    matrix = glm::rotate(matrix, glm::radians(Rotation.x), {1, 0, 0});
    matrix = glm::rotate(matrix, glm::radians(Rotation.y), {0, 1, 0});
    matrix = glm::rotate(matrix, glm::radians(Rotation.z), {0, 0, 1});
    
    matrix = glm::translate(matrix, Position);
    
    return matrix;
}

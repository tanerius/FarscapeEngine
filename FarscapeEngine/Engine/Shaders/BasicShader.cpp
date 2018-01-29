//
//  MeshShader.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#include "BasicShader.h"

Farscape::BasicShader::BasicShader(const std::string& vertexFile, const std::string& fragmentFile)
:   Shader(vertexFile, fragmentFile)
{
    GetUniforms();
}

void Farscape::BasicShader::LoadProjectionViewMatrix(const glm::mat4& pvMatrix)
{
    LoadMatrix4(m_locationProjectionViewMatrix,
                pvMatrix);
}

void Farscape::BasicShader::LoadModelMatrix(const glm::mat4& matrix)
{
    LoadMatrix4(m_locationModelMatrix, matrix);
}

void Farscape::BasicShader::GetUniforms()
{
    UseProgram();
    m_locationProjectionViewMatrix = glGetUniformLocation(m_id, "projViewMatrix");
    m_locationModelMatrix          = glGetUniformLocation(m_id, "modelMatrix");
}

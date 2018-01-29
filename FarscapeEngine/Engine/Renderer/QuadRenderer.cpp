//
//  QuadRenderer.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#include "QuadRenderer.h"

#include <iostream>

#include "../Core/Camera.h"
#include "../Math/Matrix.h"

Farscape::QuadRenderer::QuadRenderer()
{
    m_basicTexture.LoadFromFile("test");
    
    m_quadModel.AddData(
                        {
                            -0.5,  0.5, 0,
                            0.5,  0.5, 0,
                            0.5, -0.5, 0,
                            -0.5, -0.5, 0,
                        },
                        {
                            0, 1,
                            1, 1,
                            1, 0,
                            0, 0,
                        },
                        {
                            0, 1, 2,
                            2, 3, 0
                        });
}

void Farscape::QuadRenderer::AddMesh(const glm::vec3& position)
{
    m_quads.push_back(position);
}

void Farscape::QuadRenderer::RenderMeshes(const Camera& camera)
{
    m_shader.UseProgram();
    m_quadModel.BindVAO();
    m_basicTexture.BindTexture();
    
    m_shader.LoadProjectionViewMatrix(camera.GetProjectionViewMatrix());
    
    for (auto& quad : m_quads)
    {
        m_shader.LoadModelMatrix(Farscape::Matrix::CreateModelMatrix(quad, {0,0,0}));
        
        glDrawElements(GL_TRIANGLES, m_quadModel.GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
    }
    
    m_quads.clear();
}

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

Farscape::QuadRenderer::~QuadRenderer()
{
    m_quads.clear();
    delete m_shader;
    delete m_basicTexture;
    delete m_quadModel;
}

Farscape::QuadRenderer::QuadRenderer()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_TEXTURE_2D);
    
    m_basicTexture = new Farscape::BasicTexture();
    m_basicTexture->LoadFromFile("test");
    m_shader = new Farscape::BasicShader("BasicVertex", "BasicFragment");
    
    m_quadModel = new Farscape::Model(
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
                            0, 2, 1,
                            0, 3, 2
                        });
    
    
}

void Farscape::QuadRenderer::AddMesh(const glm::vec3& position)
{
    m_quads.push_back(position);
}

void Farscape::QuadRenderer::RenderMeshes(const Camera* camera)
{
    //printf("Rendering meshes...\n");
    m_shader->UseProgram();
    m_quadModel->BindVAO();
    m_basicTexture->BindTexture();
    
    m_shader->LoadProjectionViewMatrix(camera->GetProjectionViewMatrix());
    
    for (auto& quad : m_quads)
    {
        m_shader->LoadModelMatrix(Farscape::Matrix::CreateModelMatrix(quad, {0,0,0}));
        
        glDrawElements(GL_TRIANGLES, m_quadModel->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
        //glDrawElementsBaseVertex(GL_TRIANGLES, m_quadModel.GetIndicesCount(), GL_UNSIGNED_INT, 0, 0);
    }
    
    m_quads.clear();
}

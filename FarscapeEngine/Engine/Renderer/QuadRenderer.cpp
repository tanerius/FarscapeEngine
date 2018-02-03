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
#include "../Core/Transform.h"



Farscape::QuadRenderer::~QuadRenderer()
{
    m_quads.clear();
    delete m_shader;
    delete m_basicTexture;
    delete m_quadModel;
}

Farscape::QuadRenderer::QuadRenderer()
{
    
    
    m_basicTexture = new Farscape::BasicTexture();
    m_basicTexture->LoadFromFile("test");
    
    
    m_shader = new Farscape::BasicShader("BasicVertex", "BasicFragment");
    
    m_quadModel = new Farscape::Model({
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
                            0, 1, 2, // Use CW winding in opengl
                            2, 3, 0
                        }});
    
    
}

void Farscape::QuadRenderer::AddMesh(const Vector3d& position, const Vector3d& rotation, const Vector3d& scale)
{

    m_quads.push_back(std::unique_ptr<Transform>(new Transform(
                                                                position, // Position
                                                                rotation, // Rotation
                                                                scale // Scale
                                                                )
                                                 )
                      );
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
        //m_shader->LoadModelMatrix(Farscape::Matrix::CreateModelMatrix(quad, {0,0,0}));
        m_shader->LoadModelMatrix(quad->GetModelMatrix());
        
        glDrawElements(GL_TRIANGLES, m_quadModel->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
        //glDrawElementsBaseVertex(GL_TRIANGLES, m_quadModel.GetIndicesCount(), GL_UNSIGNED_INT, 0, 0);
    }
    
    m_quads.clear();
}

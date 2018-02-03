//
//  CubeRenderer.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 2/4/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#include "CubeRenderer.h"
#include <iostream>

#include "../Core/Camera.h"
#include "../Math/Matrix.h"
#include "../Core/Transform.h"

Farscape::CubeRenderer::~CubeRenderer()
{
    m_quads.clear();
    delete m_shader;
    delete m_basicTexture;
    delete m_quadModel;
    delete m_atlasTest;
}

Farscape::CubeRenderer::CubeRenderer()
: m_atlasTest(new Farscape::TextureAtlas("DefaultPack"))
{
    m_basicTexture = new Farscape::BasicTexture();
    m_basicTexture->LoadFromFile("test");
    m_shader = new Farscape::BasicShader();
    
    std::vector<GLfloat> vertexCoords
    {
        //Back
        1, 0, 0,
        0, 0, 0,
        0, 1, 0,
        1, 1, 0,
        
        //Front
        0, 0, 1,
        1, 0, 1,
        1, 1, 1,
        0, 1, 1,
        
        //Right
        1, 0, 1,
        1, 0, 0,
        1, 1, 0,
        1, 1, 1,
        
        //Left
        0, 0, 0,
        0, 0, 1,
        0, 1, 1,
        0, 1, 0,
        
        //Top
        0, 1, 1,
        1, 1, 1,
        1, 1, 0,
        0, 1, 0,
        
        //Bottom
        0, 0, 0,
        1, 0, 0,
        1, 0, 1,
        0, 0, 1.
    };
    
    auto top    = m_atlasTest->GetTexture({0, 0});
    auto side   = m_atlasTest->GetTexture({1, 0});
    auto bottom = m_atlasTest->GetTexture({2, 0});
    
    std::vector<GLfloat> texCoords;
    texCoords.insert(texCoords.end(), side.begin(),     side.end());
    texCoords.insert(texCoords.end(), side.begin(),     side.end());
    texCoords.insert(texCoords.end(), side.begin(),     side.end());
    texCoords.insert(texCoords.end(), side.begin(),     side.end());
    texCoords.insert(texCoords.end(), top.begin(),      top.end());
    texCoords.insert(texCoords.end(), bottom.begin(),   bottom.end());
    
    
    std::vector<GLuint> indices
    {
        0, 1, 2,
        2, 3, 0,
        
        4, 5, 6,
        6, 7, 4,
        
        8, 9, 10,
        10, 11, 8,
        
        12, 13, 14,
        14, 15, 12,
        
        16, 17, 18,
        18, 19, 16,
        
        20, 21, 22,
        22, 23, 20
    };
    
    m_quadModel = new Farscape::Model({vertexCoords, texCoords, indices});
}

void Farscape::CubeRenderer::AddMesh(const Vector3d& position, const Vector3d& rotation, const Vector3d& scale)
{
    
    m_quads.push_back(std::unique_ptr<Transform>(new Transform(
                                                               position, // Position
                                                               rotation, // Rotation
                                                               scale // Scale
                                                               )
                                                 )
                      );
}

void Farscape::CubeRenderer::RenderMeshes(const Camera* camera)
{
    //printf("Rendering meshes...\n");
    m_shader->UseProgram();
    m_quadModel->BindVAO();
    m_basicTexture->BindTexture();
    
    m_shader->LoadProjectionViewMatrix(camera->GetProjectionViewMatrix());
    
    for (auto& quad : m_quads)
    {
        m_shader->LoadModelMatrix(quad->GetModelMatrix());
        glDrawElements(GL_TRIANGLES, m_quadModel->GetIndicesCount(), GL_UNSIGNED_INT, nullptr);
        
    }
    
    m_quads.clear();
}



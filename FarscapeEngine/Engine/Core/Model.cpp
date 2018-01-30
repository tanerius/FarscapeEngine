//
//  Model.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 1/28/18.
//  Copyright © 2018 Taner Selim. All rights reserved.
//

#include "Model.h"

Farscape::Model::Model(const std::vector<GLfloat>& vertexPositions,
             const std::vector<GLfloat>& textureCoords,
             const std::vector<GLuint>&  indices)
{
    AddData(vertexPositions, textureCoords, indices);
}

Farscape::Model::~Model()
{
    DeleteData();
}

void Farscape::Model::BindVAO() const
{
    glBindVertexArray(m_vao);
}

void Farscape::Model::AddData(const std::vector<GLfloat>& vertexPositions,
                    const std::vector<GLfloat>& textureCoords,
                    const std::vector<GLuint>&  indices)
{
    if (m_vao != 0)
        DeleteData();
    
    m_indicesCount = (GLsizei)indices.size();
    
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);
    
    AddVBO(3, vertexPositions);
    AddVBO(2, textureCoords);
    AddEBO(indices);
    glBindVertexArray(0);
}

void Farscape::Model::AddVBO(int dimensions, const std::vector<GLfloat>& data)
{
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 data.size() * sizeof(GLfloat),
                 data.data(),
                 GL_STATIC_DRAW);
    
    glVertexAttribPointer(m_vboCount,
                          dimensions,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          (GLvoid*) 0);
    
    glEnableVertexAttribArray(m_vboCount++);
    
    m_buffers.push_back(vbo);
}

void Farscape::Model::AddEBO(const std::vector<GLuint>& indices)
{
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indices.size() * sizeof(GLuint),
                 indices.data(),
                 GL_STATIC_DRAW);
}

void Farscape::Model::DeleteData()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers((GLsizei)m_buffers.size(),
                    m_buffers.data());
    
    m_buffers.clear();
    
    m_vboCount      = 0;
    m_vao           = 0;
    m_indicesCount  = 0;
}

int Farscape::Model::GetIndicesCount() const
{
    return m_indicesCount;
}

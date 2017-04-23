//
//  cgmesh.cpp
//  FarscapeEngine
//
//  Created by Taner Selim on 4/22/17.
//  Copyright © 2017 Taner Selim. All rights reserved.
//

#include "cgmesh.hpp"
#include <string>


#include <GL/glew.h>
#include <glm/glm.hpp>


std::string CGCore::Vertex::ToString() const
{
    std::string x = "V(" + std::to_string(Pos->x) +
        ", " + std::to_string(Pos->y) +
        ", " + std::to_string(Pos->z) + ")\n" +
        "UV(" + std::to_string(TexCoord->x) +
        ", " + std::to_string(TexCoord->y) + ")\n" +
        "N(" + std::to_string(Normal->x) +
        ", " + std::to_string(Normal->y) +
        ", " + std::to_string(Normal->z) + ")\n";
    
    return x;
}


CGCore::Vertex::~Vertex()
{
    delete this->Pos;
    delete this->TexCoord;
    delete this->Normal;
}


// *****************************************************
// ********* Indexed Model
// *****************************************************


void CGCore::IndexedModel::CalcNormals()
{
    // For each triangle
    for(unsigned int i = 0; i < Indices.size(); i += 3)
    {
        int i0 = Indices[i];
        int i1 = Indices[i + 1];
        int i2 = Indices[i + 2];
        
        glm::vec3 v1 = Positions[i1] - Positions[i0];
        glm::vec3 v2 = Positions[i2] - Positions[i0];
        
        glm::vec3 normal = glm::normalize(glm::cross(v1, v2));
        
        Normals[i0] += normal;
        Normals[i1] += normal;
        Normals[i2] += normal;
    }
    
    for(unsigned int i = 0; i < Positions.size(); i++)
        Normals[i] = glm::normalize(Normals[i]);
}


CGCore::Mesh::Mesh(
                   Vertex* Vertices,
                   unsigned int VertexCount,
                   unsigned int* Indices,
                   unsigned int IndexCount
                   )
{
    IndexedModel Model;
    
    for(unsigned int i = 0; i < VertexCount; i++)
    {
        Model.Positions.push_back(*Vertices[i].GetPos());
        Model.TexCoords.push_back(*Vertices[i].GetTexCoord());
        Model.Normals.push_back(*Vertices[i].GetNormal());
    }
    
    for(unsigned int i = 0; i < IndexCount; i++)
        Model.Indices.push_back(Indices[i]);
    
    InitMesh(Model);
}


CGCore::Mesh::~Mesh()
{
    glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
    glDeleteVertexArrays(1, &m_vertexArrayObject);
}


void CGCore::Mesh::Draw()
{
    glBindVertexArray(m_vertexArrayObject);
    
    //glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
    glDrawElementsBaseVertex(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0, 0);
    
    glBindVertexArray(0);
}


void CGCore::Mesh::InitMesh(const CGCore::IndexedModel& Model)
{
    m_numIndices = (unsigned int)Model.Indices.size();
    
    // Generate a VAO and bind it.
    glGenVertexArrays(1, &m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);
    
    // Generate 4 buffers (from size of E_BUFFER_POSITION)
    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
    
    // Bind and allocate the VBOs
    // Bind the Vertex Positions VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[static_cast<int>(E_BUFFER_POSITION::E_POSITION)]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Model.Positions[0]) * Model.Positions.size(), &Model.Positions[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    // Bind the Texture coordinate VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[static_cast<int>(E_BUFFER_POSITION::E_TEXCOORD)]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Model.TexCoords[0]) * Model.TexCoords.size(), &Model.TexCoords[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);
    
    // Bind the Vertex normals VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[static_cast<int>(E_BUFFER_POSITION::E_NORMAL)]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Model.Normals[0]) * Model.Normals.size(), &Model.Normals[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    // Bind the Vertex index VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[static_cast<int>(E_BUFFER_POSITION::E_INDEX)]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Model.Indices[0]) * Model.Indices.size(), &Model.Indices[0], GL_STATIC_DRAW);
    
    // Unbind VAO
    glBindVertexArray(0);
}


std::string CGCore::Mesh::ToString() const
{
    std::string x = "Mesh {} \n";
    return x;
}

#include "cgtexture.hpp"
#include "cgloader.hpp"

#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <png.h> // Ability to read png files for textures
#include "cgentity.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
*
* VBO optimization to make sure repeating vectors don't use up space
*
*/
void CGCore::Loader::BindIndicesBufferVBO(const GLuint Indices[], GLuint ArraySize)
{
    GLuint VboID; 
    glGenBuffers(1,&VboID);
    VBOContainer.push_back(VboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*ArraySize, Indices, GL_STATIC_DRAW);
}

void CGCore::Loader::CleanUp()
{
    
    for(GLuint n : VBOContainer) {
        glDeleteBuffers(1, &n);
    }
    
    for(GLuint n : VAOContainer) {
        glDeleteVertexArrays(1, &n);
    }

    VBOContainer.clear();
    VAOContainer.clear();
}

void CGCore::Loader::CreateBindVAO()
{
    GLuint VaoID;
    glGenVertexArrays(1, &VaoID); // create the VAO
    VAOContainer.push_back(VaoID);
    glBindVertexArray(VaoID); // bind the VAO
}


CGCore::Entity* CGCore::Loader::CreateEntity(
                     const GLfloat* Vertices, // The vertex buffer
                     const GLuint Vsize, // size of the vertex buffer
                     const GLuint* Indices, // the index buffer
                     const GLuint Isize, // size of the index buffer
                     const GLfloat* TexUV, // the texture mapping buffer
                     const GLuint Tsize, // size of the texture map buffer
                     const char* TexturePath
                     )
{
    CGCore::Entity* NewEntityModel = new CGCore::Entity();
    
    // Generate and load buffers (VBOs)
    GLuint ModelVertexBufferID = LoadToVBO(Vertices, Vsize);
    GLuint BufferIndex = LoadToVBO(Indices, Isize);
    GLuint TextureUV = LoadToVBO(TexUV, Tsize);
    // Load the VBOs to VAO
    // TODO: Store VAO index data
    GLuint VertexVAO = GetVAOindex();
    GLuint TextureVAO = GetVAOindex();
    LoadVboToVAO(VertexVAO, ModelVertexBufferID, 3, GL_FLOAT, GL_ARRAY_BUFFER);
    LoadVboToVAO(TextureVAO, TextureUV, 2, GL_FLOAT, GL_ARRAY_BUFFER);
    NewEntityModel->SetVertices(VertexVAO, ModelVertexBufferID, Vsize);
    NewEntityModel->SetIndices(BufferIndex, Isize);
    NewEntityModel->SetTexture(TextureVAO, TextureUV, Tsize, TexturePath);
    
    return NewEntityModel;
}


void CGCore::Loader::DisableVAO(GLuint VaoAttrNumber)
{
    glDisableVertexAttribArray(VaoAttrNumber);
}


void CGCore::Loader::LoadVboToVAO(const GLuint VaoAttrNumber, const GLuint BufferID, const GLuint ElementSize, GLenum BufferType, GLenum BufferTarget)
{
    // 1rst attribute buffer : vertices
    // glEnableVertexAttribArray(VaoAttrNumber); // DO THIS FROM THE ENTITY CLASS
    glBindBuffer(BufferTarget, BufferID);
    glVertexAttribPointer(
        VaoAttrNumber,      // attribute. No particular reason for 0, but must match the layout in the shader.
        ElementSize,        // size (x+y+z) = 3
        BufferType,         // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

}


int CGCore::Loader::GetVAOindex()
{
    // WARNING: Not thread safe
    int i = CurrentVAOindex;
    CurrentVAOindex++;
    return i;
}


// Creates a VBO and loads it with data and returns the name
GLuint CGCore::Loader::LoadToVBO(const GLfloat DataArray[], const GLuint DataSize)
{
    //printf("Data Loader\n");
    GLuint VboID; 
    glGenBuffers(1,&VboID);
    VBOContainer.push_back(VboID);
    glBindBuffer(GL_ARRAY_BUFFER, VboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*DataSize, DataArray, GL_STATIC_DRAW);
    return VboID;
}

GLuint CGCore::Loader::LoadToVBO(const GLuint Indices[], const GLuint ArraySize)
{
    // printf("Index Loader\n");
    GLuint VboID; 
    glGenBuffers(1,&VboID);
    VBOContainer.push_back(VboID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*ArraySize, Indices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind current VBO
    return VboID;
}

void CGCore::Loader::UnbindVAO()
{
    glBindVertexArray(0); // Unbind any VAOs
}

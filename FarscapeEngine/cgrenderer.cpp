#include "cgrenderer.hpp"
#include "cgdisplay.hpp"
#include "cgtexture.hpp"
#include "cgshader.hpp"
#include "cgentity.hpp"

#ifdef WINDOWS
#include<windows.h>
#endif

#include <cmath> // for creating projection matrix
#include "cghelper.hpp"
#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>



CGCore::Renderer::Renderer(const CGCore::DisplayManager* DM)
{

}


CGCore::Renderer::~Renderer()
{
    if (ProjectionMatrix != nullptr)
        delete ProjectionMatrix;
}


void CGCore::Renderer::CreateProjectionMatrix(const DisplayManager* DM)
{
    int ScreenWidth, ScreenHeight;
    DM->GetResolution(ScreenWidth, ScreenHeight);
    
    if (ProjectionMatrix != nullptr)
        delete ProjectionMatrix;
    ProjectionMatrix = new glm::mat4(1.0f);
    *ProjectionMatrix = glm::perspective( glm::half_pi<float>(), (float)ScreenWidth/(float)ScreenHeight, 0.1f, -100.0f);
   
}


void CGCore::Renderer::Prepare()
{
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}


void CGCore::Renderer::Render(GLenum RenderMode, GLuint StartIndex, GLuint NumberOfVertices)
{
    glDrawArrays(RenderMode, StartIndex, NumberOfVertices);
}

/*
void CGCore::Renderer::RenderFromBufferIndex(GLuint BufferIndex,GLenum RenderMode, GLenum DataType, GLuint NumberOfVertices)
{
    
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferIndex);
    glDrawElements(	RenderMode,
        NumberOfVertices,  // 3 cinse we want to draw 3 vetrices
        DataType,
        (void*)
        0
    );
}


void CGCore::Renderer::RenderFromBufferIndex(Entity* EntityObj, StaticShader* EntityShader)
{
    
    // Load sampler
    if(EntityObj->GetTextureObj() != nullptr)
    {
        // there is a texture load the uniform var
        //EntityShader->LoadTextureToSampler(EntityObj->GetTextureObj()->GetTextureID(), 0);
    }
 
    
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EntityObj->GetIndexBufferVBO());
    glDrawElements(	GL_TRIANGLES,
                   EntityObj->GetIBSize(),
                   GL_UNSIGNED_INT,
                   (void*)
                   0
                   );
}
*/

void CGCore::Renderer::SetStates()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_TEXTURE_2D);

}

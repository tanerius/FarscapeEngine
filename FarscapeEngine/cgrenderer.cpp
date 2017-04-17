#include "cgrenderer.hpp"
#include "cgtexture.hpp"
#include "cgshader.hpp"
#include "cgstaticshader.hpp"
#include "cgentity.hpp"

#ifdef WINDOWS
#include<windows.h>
#endif

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void CGCore::Renderer::Prepare()
{
    // Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

}


void CGCore::Renderer::Render(GLenum RenderMode, GLuint StartIndex, GLuint NumberOfVertices)
{
    glDrawArrays(RenderMode, StartIndex, NumberOfVertices);
}


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
        EntityShader->LoadTextureToSampler(EntityObj->GetTextureObj()->GetTextureID(), 0);
    }
    
    
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EntityObj->GetIndexBufferVBO());
    glDrawElements(	GL_TRIANGLES,
                   EntityObj->GetIBSize(),
                   GL_UNSIGNED_INT,
                   (void*)
                   0
                   );
}


void CGCore::Renderer::SetStates()
{
    // Dark blue background to start off with
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    // Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
}

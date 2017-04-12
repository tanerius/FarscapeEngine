#include "cgdisplay.hpp"
#include "cgrawmodel.hpp"
#include "cgtexture.hpp"
#include "cgshader.hpp"
#include "cgstaticshader.hpp"
#include "cgloader.hpp"
#include "cgrenderer.hpp"

const char* TextureFile = "/Users/tanerselim/Dev/Quadtree_LOD/res/tex512.png";

int main()
{
    // Initialize the display
    CGCore::DisplayManager* Display = new CGCore::DisplayManager();
    Display->CreateDisplay();
    Display->GetInfo();
    // Call a renderer to set states
    CGCore::Renderer* RendererObj = new CGCore::Renderer();
    RendererObj->SetStates();
    // Get a loader instance
    CGCore::Loader* LoaderObj = new CGCore::Loader();
    // Load relevant shaders
    CGCore::StaticShader* StaticShaderObj = new CGCore::StaticShader(); // generates ProgramID too
    // Get a ProgramID just in case
    GLuint ProgramID = StaticShaderObj->GetProgramID();
    // Get handles for any uniform shader vars which we may need
    // GLuint SomeUniform = glGetUniformLocation(ProgramID, "VarName");
    // Load a texture
    CGCore::Texture* TextureObj = new CGCore::Texture(TextureFile);
    // Get a handle for the "textureSampler" uniform
	GLuint TextureSamplerHnd  = glGetUniformLocation(ProgramID, "textureSampler");
    // Vertex data representing a rectangle
    const GLfloat VertexBufferData[] = {
        -0.5f,   0.5f, 0.0f, // v0 top left
        -0.5f,  -0.5f, 0.0f, // v1 bot left
         0.5f,   0.5f, 0.0f, // v2 top right
         0.5f,  -0.5f, 0.0f  // v3 bot right
    };
    /// indexes how to draw the triangle (in GL_CCW) forming a box
    const GLuint Indices[] = {
        2, 0, 1,    // first triangle
        1, 3, 2
        
    };
    // Two UV coordinates for each vertex. 
    const GLfloat TextureCoords[] = 
    {
        0.0f, 1.0f, // v0
        0.0f, 0.0f, // v1
        1.0f, 0.0f, // v3
        1.0f, 1.0f
    };

    LoaderObj->CreateBindVAO();
    // Generate and load buffers (VBOs)
    GLuint ModelVertexBufferID = LoaderObj->LoadToVBO(VertexBufferData, 12);
    GLuint BufferIndex = LoaderObj->LoadToVBO(Indices, 12); // Should use the GLuint version
    GLuint TextureUV = LoaderObj->LoadToVBO(TextureCoords, 8);
    
    // Start main loop
    while(!Display->CloseRequested())
    {
        RendererObj->Prepare();
        StaticShaderObj->StartProgram();
        //RendererObj->Render(TMObj);
        // Bind our texture in Texture Unit 0
        TextureObj->ApplyTexture(TextureSamplerHnd, 0);
		
        // 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, ModelVertexBufferID);
		glVertexAttribPointer(
			0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
			3,                  // size (x+y+z) = 3
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

        // 2nd attribute buffer : UVs
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, TextureUV);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

        // Draw the triangle !
		//glDrawArrays(GL_TRIANGLES, 0, 3*3); // 12*3 indices starting at 0 -> 12 triangles

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferIndex);
        glDrawElements(	GL_TRIANGLES, 
            6,  // 3 cinse we want to draw 3 vetrices
            GL_UNSIGNED_INT, 
            (void*) 
            0);

        glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

        Display->UpdateDisplay();
    }

    StaticShaderObj->CleanUp();
    LoaderObj->CleanUp();
    Display->DestroyDisplay();
    //delete ModelObj;
    delete TextureObj;
    delete StaticShaderObj;
    delete Display;
    delete LoaderObj;

    
    return 0;
}

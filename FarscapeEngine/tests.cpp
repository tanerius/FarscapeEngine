#include "cgdisplay.hpp"
#include "cgrawmodel.hpp"
#include "cgtexture.hpp"
#include "cgshader.hpp"
#include "cgstaticshader.hpp"
#include "cgloader.hpp"
#include "cgrenderer.hpp"

static const char* TEXTURE_FILE = "/Users/tanerselim/Dev/Quadtree_LOD/res/tex512.png";

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
    // Load a texture
    CGCore::Texture* TextureObj = new CGCore::Texture(TEXTURE_FILE);
    // Get a handle for the "textureSampler" uniform
    GLuint TextureSamplerHnd  = StaticShaderObj->GetUniformLocation("textureSampler");
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
    
    bool HasError = false;
    
    // Start main loop
    while(!Display->CloseRequested() && (!HasError))
    {
        RendererObj->Prepare();
        StaticShaderObj->StartProgram();
        //RendererObj->Render(TMObj);
        // Bind our texture in Texture Unit 0
        TextureObj->ApplyTexture(TextureSamplerHnd, 0);
        // 0th attribute buffer : vertices
        LoaderObj->LoadVboToVAO(0, ModelVertexBufferID, 3, GL_FLOAT, GL_ARRAY_BUFFER);
        // 1st attribute buffer : UVs
        LoaderObj->LoadVboToVAO(1, TextureUV, 2, GL_FLOAT, GL_ARRAY_BUFFER);
        
        HasError = StaticShaderObj->ValidateProgram();
        
        RendererObj->RenderFromBufferIndex(BufferIndex, GL_TRIANGLES, GL_UNSIGNED_INT, 6);

        LoaderObj->DisableVAO(0);
        LoaderObj->DisableVAO(1);

        Display->UpdateDisplay();
    }

    StaticShaderObj->CleanUp();
    LoaderObj->CleanUp();
    Display->DestroyDisplay();
    
    delete TextureObj;
    delete StaticShaderObj;
    delete Display;
    delete LoaderObj;

    
    return 0;
}

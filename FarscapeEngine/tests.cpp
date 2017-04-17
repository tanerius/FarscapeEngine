#include "cgdisplay.hpp"
#include "cgrawmodel.hpp"
#include "cgtexture.hpp"
#include "cgshader.hpp"
#include "cgstaticshader.hpp"
#include "cgloader.hpp"
#include "cgrenderer.hpp"
#include "cghelper.hpp"
#include "cgentity.hpp"

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
    LoaderObj->CreateBindVAO();
  
    // Vertex data representing a square / rectangle
    const GLfloat VertexBufferData[] = {
        -0.5f,   0.5f, 0.0f, // v0 top left
        -0.5f,  -0.5f, 0.0f, // v1 bot left
         0.5f,   0.5f, 0.0f, // v2 top right
         0.5f,  -0.5f, 0.0f  // v3 bot right
    };
    /// indexes how to draw the triangles (in GL_CCW) forming a square
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

    
    // Create the square entity
    CGCore::Entity *Square = LoaderObj->CreateEntity(VertexBufferData, 12, Indices, 6, TextureCoords, 8, TEXTURE_FILE);
    // Get a handle for the "textureSampler" uniform
    GLuint TextureSamplerHnd  = StaticShaderObj->GetUniformLocation("textureSampler");
    // Bind our texture in Texture Unit 0 -> DO THIS IN THE RENDERER
    Square->GetTextureObj()->ApplyTexture(TextureSamplerHnd, 0);
    // Enable the entity
    Square->EnableEntity();
    
    bool HasError = false;
    
   
    // Start main loop
    while(!Display->CloseRequested() && (!HasError))
    {
        RendererObj->Prepare();
        StaticShaderObj->StartProgram();

        
        
        HasError = StaticShaderObj->ValidateProgram();
        //RendererObj->RenderFromBufferIndex(Square, StaticShaderObj);
        
        RendererObj->RenderFromBufferIndex(Square->GetIndexBufferVBO(), GL_TRIANGLES, GL_UNSIGNED_INT, 6);

        

        Display->UpdateDisplay();
    }
    
    //Disable entity
    Square->DisableEntity();

    StaticShaderObj->CleanUp();
    LoaderObj->CleanUp();
    Display->DestroyDisplay();
    
    delete Square;
    delete StaticShaderObj;
    delete Display;
    delete LoaderObj;
    
    

    return 0;
}

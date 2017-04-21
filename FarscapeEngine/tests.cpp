#include "cgdisplay.hpp"
#include "cgtexture.hpp"
#include "cgshader.hpp"
#include "cgstaticshader.hpp"
#include "cgloader.hpp"
#include "cgrenderer.hpp"

#include "cgentity.hpp"
#include "cgcamera.hpp"


#ifdef WINDOWS
static const char* TEXTURE_FILE = "C:\\Users\\taner\\Documents\\Dev\\FarscapeEngine\\FarscapeEngine\\assets\\tex512.png";
#else
static const char* TEXTURE_FILE = "/Users/tanerselim/Dev/FarscapeEngine/FarscapeEngine/assets/tex512.png";
#endif

int main()
{
    // Initialize the display
    CGCore::DisplayManager* Display = new CGCore::DisplayManager();
    Display->CreateDisplay();
    Display->GetInfo();
    CGCore::Camera* MainCamera = new CGCore::Camera(Display);
    // Call a renderer to set states and create a projection matrix
    CGCore::Renderer* RendererObj = new CGCore::Renderer(Display);
    RendererObj->SetStates();
    // Get a loader instance
    CGCore::Loader* LoaderObj = new CGCore::Loader();
    // Load relevant shaders
    CGCore::StaticShader* StaticShaderObj = new CGCore::StaticShader(); // generates ProgramID too
    
    // Get the projection matrix and load it onto the shader once
    glm::mat4 ProjectionMatrix = RendererObj->GetProjection();
    StaticShaderObj->StartProgram();
    StaticShaderObj->LoadProjectionMatrix(ProjectionMatrix);
    StaticShaderObj->StopProgram();
    
    
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

    Square->EnableEntity();
    Square->SetTransform(
         glm::vec3(0.0f, 0.0f, -5.0f),       // Translation (x, y, z)
         glm::vec4(1.0f,1.0f,0.0f,0.0f),    // Rotate Quat (xAxis, yAxis, zAxis, rotAngle)
         glm::vec3(1.0f, 1.0f, 1.0f)        // Scaling (x, y, z)
     );


    bool HasError = false;


    // Start main loop
    while(!Display->CloseRequested() && (!HasError))
    {
        //Square->ChangeTranslation(glm::vec3(0.0f, 0.0f, -0.01f));
        Square->ChangeRotation(glm::vec4(1.0f, 1.0f, 1.0f, 0.02f));
        RendererObj->Prepare();
        
        StaticShaderObj->StartProgram();
        glm::mat4 V = MainCamera->GetViewMatrix();
        StaticShaderObj->LoadViewMatrix(V);
        glm::mat4 M = Square->CreateTransformationMatrix();
        StaticShaderObj->LoadTransformationMatrix(M);


        HasError = StaticShaderObj->ValidateProgram();
        RendererObj->RenderFromBufferIndex(Square, StaticShaderObj);
        MainCamera->Move();

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

/*
  Talk with Li

  - Draft of the circular 
  - and draft of the seating arrangements and suggest
  - Plata tetka lile! 12k vs 15k viki
  - 
*/

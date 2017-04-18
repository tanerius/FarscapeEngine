#include "cgdisplay.hpp"
#include "cgrawmodel.hpp"
#include "cgtexture.hpp"
#include "cgshader.hpp"
#include "cgstaticshader.hpp"
#include "cgloader.hpp"
#include "cgrenderer.hpp"
#include "cghelper.hpp"
#include "cgentity.hpp"


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

    Square->EnableEntity();

    bool HasError = false;
    glm::vec3 Translate(0.0f, 0.0f, 0.0f);
    glm::vec3 Rot(0.0f, 1.0f, 1.0f); // cant be 0 vectors or rotation matrix will fail
    glm::vec3 Scale(1.0f, 1.0f, 1.0f);
    float RotAngle = 0.0f;

    glm::mat4 M = CGCore::CreateTransformationMatrix(Translate, Rot, RotAngle, Scale);

    //CGCore::TestPrintMatrix4(M, "Transform Matrix");
    float Tx = 0.0f;
    // Start main loop
    while(!Display->CloseRequested() && (!HasError))
    {
        Tx = sin(Display->GetRunningTime());
        Translate.x = Tx;
        
        RendererObj->Prepare();
        
        if (RotAngle > 359.8f)
        {
            RotAngle = 0.0f;
        }
        else
        {
            RotAngle = RotAngle + 0.01f;
        }

        StaticShaderObj->StartProgram();
        M = CGCore::CreateTransformationMatrix(Translate, Rot, RotAngle, Scale);
        StaticShaderObj->LoadTransformationMatrix(M);


        HasError = StaticShaderObj->ValidateProgram();
        RendererObj->RenderFromBufferIndex(Square, StaticShaderObj);

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

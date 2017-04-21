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

    
    
    LoaderObj->CreateBindVAO();

    // Vertex data representing a 3D CUBE
    const GLfloat VertexBufferData[] = {
        // back side
        -0.5f,0.5f,-0.5f,	// top left back
        -0.5f,-0.5f,-0.5f,	// btm left back
        0.5f,-0.5f,-0.5f,	// btm right back
        0.5f,0.5f,-0.5f,	// top right back
        //front side
        -0.5f,0.5f,0.5f,	//top left front
        -0.5f,-0.5f,0.5f,	//btm left front
        0.5f,-0.5f,0.5f,	//btm right front
        0.5f,0.5f,0.5f     //top right front
    };
    /// indexes how to draw the faces (in GL_CCW) forming a cube
    const GLuint Indices[] = {
        1,0,3, // back face
        3,2,1, // back face	
        7,4,5, // front face
        5,6,7, // front face
        4,0,1, // left face
        1,5,4

    };
    // Two UV coordinates for each vertex.
    const GLfloat TextureCoords[] =
    {
        0.0f,0.0f,
        0.0f,1.0f,
        1.0f,1.0f,
        1.0f,0.0f,			
        0.0f,0.0f,
        0.0f,1.0f,
        1.0f,1.0f,
        1.0f,0.0f,			
        0.0f,0.0f,
        0.0f,1.0f,
        1.0f,1.0f,
        1.0f,0.0f,
        0.0f,0.0f,
        0.0f,1.0f,
        1.0f,1.0f,
        1.0f,0.0f,
        0.0f,0.0f,
        0.0f,1.0f,
        1.0f,1.0f,
        1.0f,0.0f,
        0.0f,0.0f,
        0.0f,1.0f,
        1.0f,1.0f,
        1.0f,0.0f
    };


    // Create the square entity
    CGCore::Entity *Square = LoaderObj->CreateEntity(VertexBufferData, 24, Indices, 18, TextureCoords, 48, TEXTURE_FILE);

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
        Square->ChangeRotation(glm::vec4(0.0f, 1.0f, 0.0f, 0.02f));
        RendererObj->Prepare();
        
        StaticShaderObj->StartProgram();
        StaticShaderObj->LoadProjectionMatrix(ProjectionMatrix);
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

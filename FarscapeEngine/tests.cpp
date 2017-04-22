#include "cgdisplay.hpp"
#include "cgtexture.hpp"
#include "cgshader.hpp"
#include "cgstaticshader.hpp"
#include "cgloader.hpp"
#include "cgrenderer.hpp"

#include "cgentity.hpp"
#include "cgcamera.hpp"
#include "cgmesh.hpp"

#ifdef WINDOWS
static const char* TEXTURE_FILE = "C:\\Users\\taner\\Documents\\Dev\\FarscapeEngine\\FarscapeEngine\\assets\\tex512.png";
#else
static const char* TEXTURE_FILE = "/Users/tanerselim/Dev/FarscapeEngine/FarscapeEngine/assets/tex512.png";
#endif

int main()
{
    
    CGCore::Vertex* V = new CGCore::Vertex(
                    glm::vec3(1.0f,2.0f,3.0f),
                    glm::vec2(4.0f,5.0f),
                    glm::vec3(6.0f,7.0f,8.0f));
    printf("Vertex info: \n%s",V->ToString().c_str());
    return 0;
    
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
        // front side
        -0.5f, -0.5f,  0.0f,    // left bot front
         0.5f, -0.5f,  0.0f,    // right bot front
         0.5f,  0.5f,  0.0f,    // right top front
        -0.5f,  0.5f,  0.0f,    // left top front
        // back side
        -0.5f,  0.5f, -0.5f,    // left top back
        -0.5f, -0.5f, -0.5f,    // left bot back
         0.5f, -0.5f, -0.5f,    // right bot back
         0.5f,  0.5f, -0.5f     // right top back
    };
    
    /// indexes how to draw the faces (in GL_CCW) forming a cube
    const GLuint Indices[] = {
        2,3,0, 0,1,2,   // front face
        2,1,6, 6,7,2,   // right face
        2,7,4, 3,2,4,   // top face
        4,5,0, 0,3,4,   // left face
        5,4,7, 7,6,5,   // back face
        5,6,1, 1,0,5    // bot face
    };
    // Two UV coordinates for each vertex.
    const GLfloat TextureCoords[] =
    {
        1.0f,1.0f,  // 2 -
        0.0f,1.0f,  // 3  |
        0.0f,0.0f,  // 0  |
        0.0f,0.0f,  // 0  |-- front face
        1.0f,0.0f,  // 1  |
        1.0f,1.0f,  // 2 -
        
        0.0f,1.0f,  // 2 -
        0.0f,0.0f,  // 1  |
        1.0f,0.0f,  // 6  |
        1.0f,0.0f,  // 6  |-- right face
        1.0f,1.0f,  // 7  |
        0.0f,1.0f,  // 2 -
    };


    // Create the square entity
    CGCore::Entity *Square = LoaderObj->CreateEntity(VertexBufferData, 24, Indices, 36, TextureCoords, 24, TEXTURE_FILE);
    //CGCore::Entity *Square = LoaderObj->CreateEntity(VertexBufferData, 24, Indices, 36, TextureCoords, 24);

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

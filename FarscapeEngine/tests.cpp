#include "cgdisplay.hpp"
#include "cgtransform.hpp"
#include "cgcamera.hpp"
#include "cgmesh.hpp"
#include "cgshader.hpp"
#include "cgtexture.hpp"
#include "cgrenderer.hpp"
#include "cgentity.hpp"

#include "cginput.hpp"

#ifdef WINDOWS
static const char* TEXTURE_FILE = "C:\\Users\\taner\\Documents\\Dev\\FarscapeEngine\\FarscapeEngine\\assets\\tex512.png";
static const char* OBJ_SAMPLE = "C:\\Users\\taner\\Documents\\Dev\\FarscapeEngine\\FarscapeEngine\\assets\\monkey.obj";
static const char* SHADER_FILE = "C:\\Users\\taner\\Documents\\Dev\\FarscapeEngine\\FarscapeEngine\\shaders\\hello_tex";

static const char* STALL_SAMPLE = "C:\\Users\\taner\\Documents\\Dev\\FarscapeEngine\\FarscapeEngine\\assets\\stall.obj";
static const char* STALL_TEXTURE = "C:\\Users\\taner\\Documents\\Dev\\FarscapeEngine\\FarscapeEngine\\assets\\stallTexture.png";
static const char* DRAGON_SAMPLE = "C:\\Users\\taner\\Documents\\Dev\\FarscapeEngine\\FarscapeEngine\\assets\\dragon.obj";
static const char* YELLOW_TEX = "C:\\Users\\taner\\Documents\\Dev\\FarscapeEngine\\FarscapeEngine\\assets\\yellow128tex.png";

#else
static const char* TEXTURE_FILE = "/Users/tanerselim/Dev/FarscapeEngine/FarscapeEngine/assets/tex512.png";
static const char* OBJ_SAMPLE = "/Users/tanerselim/Dev/FarscapeEngine/FarscapeEngine/assets/monkey3.obj";
static const char* STALL_SAMPLE = "/Users/tanerselim/Dev/FarscapeEngine/FarscapeEngine/assets/stall.obj";
static const char* STALL_TEXTURE = "/Users/tanerselim/Dev/FarscapeEngine/FarscapeEngine/assets/stallTexture.png";
static const char* DRAGON_SAMPLE = "/Users/tanerselim/Dev/FarscapeEngine/FarscapeEngine/assets/dragon.obj";
static const char* YELLOW_TEX = "/Users/tanerselim/Dev/FarscapeEngine/FarscapeEngine/assets/yellow128tex.png";

static const char* SHADER_FILE = "/Users/tanerselim/Dev/FarscapeEngine/FarscapeEngine/shaders/hello_tex";
#endif

int main()
{

    CGCore::DisplayManager* Display = new CGCore::DisplayManager();
    Display->CreateDisplay();
    Display->GetInfo();


    int w,h;
    Display->GetResolution(w, h);
    float aspectRatio = (float)w / (float)h;


    CGCore::Vertex vertices[] =
    {
        // front
        CGCore::Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1)),
        CGCore::Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1)),
        CGCore::Vertex(glm::vec3(1, 1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1)),
        CGCore::Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1)),
        // back
        CGCore::Vertex(glm::vec3(-1, -1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1)),
        CGCore::Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1)),
        CGCore::Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1)),
        CGCore::Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1)),
        // bottom
        CGCore::Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0)),
        CGCore::Vertex(glm::vec3(-1, -1, 1), glm::vec2(0, 0), glm::vec3(0, -1, 0)),
        CGCore::Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0)),
        CGCore::Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, -1, 0)),
        // top
        CGCore::Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0)),
        CGCore::Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0)),
        CGCore::Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0)),
        CGCore::Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0)),
        // left
        CGCore::Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0)),
        CGCore::Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0)),
        CGCore::Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0)),
        CGCore::Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0)),
        // right
        CGCore::Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0)),
        CGCore::Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0)),
        CGCore::Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0)),
        CGCore::Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0)),
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3,

        6, 5, 4,
        7, 6, 4,

        10, 9, 8,
        11, 10, 8,

        12, 13, 14,
        12, 14, 15,

        16, 17, 18,
        16, 18, 19,

        22, 21, 20,
        23, 22, 20
    };

    // TODO: Increment correctly texture samplers
    CGCore::Texture* grass = new CGCore::Texture(TEXTURE_FILE,0);
    CGCore::Texture* yellow = new CGCore::Texture(YELLOW_TEX,1);
    
    
    CGCore::Entity* dragon = new CGCore::Entity(DRAGON_SAMPLE,yellow);
    
    CGCore::Entity* monkey = new CGCore::Entity(OBJ_SAMPLE,grass);
    glm::vec3 monkeyPosition = glm::vec3(0.0f,5.0f,-5.0f);
    monkey->GetTransform()->SetPos(monkeyPosition);
    
    //CGCore::Mesh* mesh = new CGCore::Mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
    //CGCore::Mesh* monkey = new CGCore::Mesh(OBJ_SAMPLE);
    //CGCore::Mesh* stall = new CGCore::Mesh(STALL_SAMPLE);

    //CGCore::Mesh* dragon = new CGCore::Mesh(DRAGON_SAMPLE);
    CGCore::Shader* shader = new CGCore::Shader(SHADER_FILE);
    
    glm::vec3 light(0.0f,-1.0f,1.0f);
    shader->SetLightDirection(light);

    
    CGCore::Camera* camera = new CGCore::Camera(glm::vec3(0.0f, 5.0f, -25.0f), 70.0f, aspectRatio, 0.1f, 100.0f);
    CGCore::Input* input = new CGCore::Input(Display, camera);

    CGCore::Renderer* renderer = new CGCore::Renderer(Display);
    
    
    
    renderer->SetStates();

    bool HasError = false;
    float counter = 0.0f;

    // Start main loop
    while(!Display->CloseRequested() && (!HasError))
    {

        renderer->Prepare();
        counter = counter+0.01f;
        
        
        
        glm::vec3 x(0.0f,counter,0.0f);
        dragon->GetTransform()->SetRot(x);
        monkey->GetTransform()->SetRot(-x);
    
        // Get keys
        input->Move();
        glm::vec3 CameraDirection = glm::normalize(camera->GetPosition());
        shader->SetCamPosition(CameraDirection);

        shader->Bind();
        
        // Make the dragon shine
        shader->SetShineDamper(7.0f);
        shader->SetReflectivity(3.0f);
        grass->ApplyTexture(shader->GetUniformTexSampler());
        shader->Update(*(dragon->GetTransform()), camera->GetViewProjection());
        dragon->GetMesh()->Draw();
        
        
        // Make the monkey plastic without shine
        //shader->SetShineDamper(10.0f);
        //shader->SetReflectivity(0.0f);
        yellow->ApplyTexture(shader->GetUniformTexSampler());
        shader->Update(*(monkey->GetTransform()), camera->GetViewProjection());
        monkey->GetMesh()->Draw();
        
        shader->UnBind();
        Display->UpdateDisplay();
    }

    Display->DestroyDisplay();
    delete camera;
    delete shader;
    delete dragon;
    delete renderer;
    delete Display;


}

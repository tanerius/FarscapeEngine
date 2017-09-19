#include "cgobj.hpp"
#include "cgdisplay.hpp"
#include "cgtransform.hpp"
#include "cgcamera.hpp"
#include "cgmesh.hpp"
#include "cgshader.hpp"
#include "cgtexture.hpp"
#include "cgrenderer.hpp"
#include "cgentity.hpp"
#include <vector>
#include <ctime>
#include "cginput.hpp"

#include "farscape.hpp"

#include <iostream>

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
    CGCore::FarscapeEngine* engine = CGCore::FarscapeEngine::getInstance();
    
    

    CGCore::DisplayManager* Display = CGCore::DisplayManager::getInstance();
    Display->CreateDisplay();
    Display->GetInfo();


    int w,h;
    Display->GetResolution(w, h);
    float aspectRatio = (float)w / (float)h;
    CGCore::GetTimePassed("* Created the display");


    // TODO: Increment correctly texture samplers
    CGCore::Texture* grass = new CGCore::Texture(TEXTURE_FILE,0);
    CGCore::Texture* yellow = new CGCore::Texture(YELLOW_TEX,1);

    // Container for our same monkeys    
    std::vector <CGCore::Entity*> monkeys;
    

    CGCore::Transform* keyTransform = new CGCore::Transform();

    CGCore::GetTimePassed("* Created the textures and tranforms");
    

    // 500 monkeys, in random locations and randomly rotated
    
    srand(time(NULL));
    // create one monkey

    //double f = (double)rand() / RAND_MAX;
    double x = -100.0f + ((double)rand() / RAND_MAX) * (100.0f - (-100.0f));
    double y = -100.0f + ((double)rand() / RAND_MAX) * (100.0f - (-100.0f));
    double z = -100.0f + ((double)rand() / RAND_MAX) * (100.0f - (-100.0f));

    glm::vec3 objPosition = glm::vec3(x,y,z);
    keyTransform->SetPos(objPosition);
    objPosition = glm::vec3(z,x,y);
    keyTransform->SetRot(objPosition);
    
    // Load a model only once - no point to load a model more thanonce
    CGCore::IndexedModel* MonkeyModel = CGCore::OBJModel(OBJ_SAMPLE).ToIndexedModel();
    monkeys.push_back(new CGCore::Entity(MonkeyModel,yellow,keyTransform));
    
    CGCore::GetTimePassed("* Created and init a monkey entity");
    for (int c=0; c < 499 ; c++)
    {   
        x = -100.0f + ((double)rand() / RAND_MAX) * (100.0f - (-100.0f));
        y = -100.0f + ((double)rand() / RAND_MAX) * (100.0f - (-100.0f));
        z = -100.0f + ((double)rand() / RAND_MAX) * (100.0f - (-100.0f));

        glm::vec3 objPosition = glm::vec3(x,y,z);
        keyTransform->SetPos(objPosition);
        objPosition = glm::vec3(z,x,y);
        keyTransform->SetRot(objPosition);
        monkeys.push_back(new CGCore::Entity(MonkeyModel,yellow,keyTransform));
    }    
    CGCore::GetTimePassed("* Created and init additional 499 monkey entities");
   

    CGCore::Shader* shader = new CGCore::Shader(SHADER_FILE);
    
    glm::vec3 light(0.0f,-1.0f,1.0f);
    shader->SetLightDirection(light);

    
    CGCore::Camera* camera = new CGCore::Camera(glm::vec3(0.0f, 5.0f, -25.0f), 70.0f, aspectRatio, 0.1f, 300.0f);
    CGCore::Input* input = new CGCore::Input(Display, camera);

    CGCore::Renderer* renderer = new CGCore::Renderer(Display);
    
    renderer->SetStates();

    bool HasError = false;
    float counter = 0.0f;

    
    CGCore::Entity* e = nullptr;
    CGCore::GetTimePassed("* Initialized the engine");
  
    // Start main loop
    while(!Display->CloseRequested() && (!HasError))
    {

        renderer->Prepare();
    
        // Get keys
        input->Move();
        glm::vec3 CameraDirection = glm::normalize(camera->GetPosition());
        shader->SetCamPosition(CameraDirection);

        shader->Bind();
        
        // Make the dragon shine
        shader->SetShineDamper(7.0f);
        shader->SetReflectivity(3.0f);
        // for all objects on screen
        yellow->ApplyTexture(shader->GetUniformTexSampler());

        for (int c=0; c < monkeys.size() ; c++)
        {   
            e = monkeys[c];
            shader->Update(*(e->GetTransform()), camera->GetViewProjection());
            e->GetMesh()->Draw();
        }    

        shader->UnBind();
        Display->UpdateDisplay();
    }

    Display->DestroyDisplay();
    delete camera;
    delete shader;
    delete renderer;
    delete Display;
    CGCore::GetTimePassed("* Application time");

}

/*
 * Created the display: 0.991116 s
 * Created the textures and tranforms: 0.011737 s
 * Created and init a monkey entity: 0.038391 s
 * Created and init additional 499 monkey entities: 16.789991 s
 Checking shaders...
 Checking shaders...
 Checking shaders...
 Checking shaders...
 * Initialized the engine: 0.003222 s
 * Application time: 2.611147 s
 Program ended with exit code: 0
 
 
 
 * Created the display: 0.694693 s
 * Created the textures and tranforms: 0.008868 s
 * Created and init a monkey entity: 0.036070 s
 * Created and init additional 499 monkey entities: 16.906564 s
 Checking shaders...
 Checking shaders...
 Checking shaders...
 Checking shaders...
 * Initialized the engine: 0.003040 s
 * Application time: 4.854484 s
 Program ended with exit code: 0
 
 
 * Created the display: 0.723031 s
 * Created the textures and tranforms: 0.008789 s
 * Created and init a monkey entity: 0.035092 s
 * Created and init additional 499 monkey entities: 16.711917 s
 Checking shaders...
 Checking shaders...
 Checking shaders...
 Checking shaders...
 * Initialized the engine: 0.003197 s
 * Application time: 2.222323 s
 Program ended with exit code: 0
 
 
 * Created the display: 0.762908 s
 * Created the textures and tranforms: 0.009015 s
 * Created and init a monkey entity: 0.037832 s
 * Created and init additional 499 monkey entities: 0.172046 s
 Checking shaders...
 Checking shaders...
 Checking shaders...
 Checking shaders...
 * Initialized the engine: 0.004139 s
 * Application time: 2.253051 s
 Program ended with exit code: 0
 
 */


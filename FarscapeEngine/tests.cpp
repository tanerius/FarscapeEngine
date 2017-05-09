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


    // TODO: Increment correctly texture samplers
    CGCore::Texture* grass = new CGCore::Texture(TEXTURE_FILE,0);
    CGCore::Texture* yellow = new CGCore::Texture(YELLOW_TEX,1);

    // Container for our same monkeys    
    std::vector <CGCore::Entity*> monkeys;
    

    CGCore::Transform* keyTransform = new CGCore::Transform();

    // 500 monkeys, in random locations and randomly rotated
    srand(time(NULL));
    for (int c=0; c < 500 ; c++)
    {   
        //double f = (double)rand() / RAND_MAX;
        double x = -100.0f + ((double)rand() / RAND_MAX) * (100.0f - (-100.0f));
        double y = -100.0f + ((double)rand() / RAND_MAX) * (100.0f - (-100.0f));
        double z = -100.0f + ((double)rand() / RAND_MAX) * (100.0f - (-100.0f));

        glm::vec3 objPosition = glm::vec3(x,y,z);
        keyTransform->SetPos(objPosition);
        objPosition = glm::vec3(z,x,y);
        keyTransform->SetRot(objPosition);
        monkeys.push_back(new CGCore::Entity(OBJ_SAMPLE,yellow,keyTransform));
    }    


    CGCore::Shader* shader = new CGCore::Shader(SHADER_FILE);
    
    glm::vec3 light(0.0f,-1.0f,1.0f);
    shader->SetLightDirection(light);

    
    CGCore::Camera* camera = new CGCore::Camera(glm::vec3(0.0f, 5.0f, -25.0f), 70.0f, aspectRatio, 0.1f, 1000.0f);
    CGCore::Input* input = new CGCore::Input(Display, camera);

    CGCore::Renderer* renderer = new CGCore::Renderer(Display);
    
    renderer->SetStates();

    bool HasError = false;
    float counter = 0.0f;

    
    CGCore::Entity* e = nullptr;

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


}

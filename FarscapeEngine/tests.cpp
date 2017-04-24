#include "cgdisplay.hpp"
#include "cgtransform.hpp"
#include "cgcamera.hpp"
#include "cgmesh.hpp"
#include "cgshader.hpp"
#include "cgtexture.hpp"
#include "cgrenderer.hpp"

#ifdef WINDOWS
static const char* TEXTURE_FILE = "C:\\Users\\taner\\Documents\\Dev\\FarscapeEngine\\FarscapeEngine\\assets\\tex512.png";
#else
static const char* TEXTURE_FILE = "/Users/tanerselim/Dev/FarscapeEngine/FarscapeEngine/assets/tex512.png";
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
        CGCore::Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1)),
        CGCore::Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1)),
        CGCore::Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1)),
        CGCore::Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1)),
        
        CGCore::Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1)),
        CGCore::Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1)),
        CGCore::Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1)),
        CGCore::Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1)),
        
        CGCore::Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0)),
        CGCore::Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0)),
        CGCore::Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0)),
        CGCore::Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0)),
        
        CGCore::Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0)),
        CGCore::Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0)),
        CGCore::Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0)),
        CGCore::Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0)),
        
        CGCore::Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0)),
        CGCore::Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0)),
        CGCore::Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0)),
        CGCore::Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0)),
        
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
    
    
    CGCore::Mesh* mesh = new CGCore::Mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
    CGCore::Shader* shader = new CGCore::Shader(SHADER_FILE);
    CGCore::Texture* texture = nullptr;
    CGCore::Transform* transform = new CGCore::Transform();
    CGCore::Camera* camera = new CGCore::Camera(glm::vec3(0.0f, 0.0f, -5.0f), 70.0f, aspectRatio, 0.1f, 100.0f);
    
    CGCore::Renderer* renderer = new CGCore::Renderer(Display);
    renderer->SetStates();
    
    bool HasError = false;
    float counter = 0.0f;

    // Start main loop
    while(!Display->CloseRequested() && (!HasError))
    {
        
        renderer->Prepare();
        
        float sinCounter = std::sinf(counter);
        float absSinCounter = std::abs(sinCounter);
        
        //transform.GetPos()->x = sinCounter;
        transform->GetRot()->y = counter * 100;
        if(texture == nullptr)
        {
            texture = new CGCore::Texture(TEXTURE_FILE);
        }
        shader->Update(*transform, camera->GetViewProjection());
        mesh->Draw();
        
        
        Display->UpdateDisplay();
    }

    Display->DestroyDisplay();
    /*
    delete camera;
    delete transform;
    delete texture;
    delete shader;
    delete mesh;
    */
    delete renderer;
    delete Display;


}

#include "cgdisplay.hpp"
#include "cgtransform.hpp"
#include "cgcamera.hpp"
#include "cgmesh.hpp"
#include "cgshader.hpp"
#include "cgtexture.hpp"
#include "cgrenderer.hpp"

#include "cginput.hpp"

#ifdef WINDOWS
static const char* TEXTURE_FILE = "C:\\Users\\taner\\Documents\\Dev\\FarscapeEngine\\FarscapeEngine\\assets\\tex512.png";
static const char* OBJ_SAMPLE = "C:\\Users\\taner\\Documents\\Dev\\FarscapeEngine\\FarscapeEngine\\assets\\monkey3.obj";
static const char* SHADER_FILE = "C:\\Users\\taner\\Documents\\Dev\\FarscapeEngine\\FarscapeEngine\\shaders\\hello_tex";
#else
static const char* TEXTURE_FILE = "/Users/tanerselim/Dev/FarscapeEngine/FarscapeEngine/assets/tex512.png";
static const char* OBJ_SAMPLE = "/Users/tanerselim/Dev/FarscapeEngine/FarscapeEngine/assets/monkey3.obj";
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


    //CGCore::Mesh* mesh = new CGCore::Mesh(vertices, sizeof(vertices)/sizeof(vertices[0]), indices, sizeof(indices)/sizeof(indices[0]));
    CGCore::Mesh* monkey = new CGCore::Mesh(OBJ_SAMPLE);

    CGCore::Shader* shader = new CGCore::Shader(SHADER_FILE);
    CGCore::Texture* texture = nullptr;
    CGCore::Transform* transform = new CGCore::Transform(glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(1.0f,1.0f,1.0f));
    CGCore::Camera* camera = new CGCore::Camera(glm::vec3(0.0f, 0.0f, -15.0f), 70.0f, aspectRatio, 0.1f, 100.0f);
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

        glm::vec3 x(counter,0.0f,0.0f);
        transform->SetRot(x);

        if(texture == nullptr)
        {
            texture = new CGCore::Texture(TEXTURE_FILE);
        }

        // Get keys
        input->Move();

        shader->Bind();
        shader->Update(*transform, camera->GetViewProjection());
        //mesh->Draw();
        monkey->Draw();
        shader->UnBind();

        Display->UpdateDisplay();
    }

    Display->DestroyDisplay();
    delete camera;
    delete transform;
    delete texture;
    delete shader;
    delete monkey;
    delete renderer;
    delete Display;


}

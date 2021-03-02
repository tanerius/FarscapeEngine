#include "Farscape.h"
#include <Core/EntryPoint.h>

#include "Windows/OpenGLShader.h"
#include "Windows/OpenGLTexture.h"
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "DemoLayer2D.h"

// create an example layer
class ExampleLayer : public Farscape::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
        , m_CameraController(1280.0f / 720.0f) 
    {
        m_VertexArray = Farscape::VertexArray::Create();

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
        };

        Farscape::Ref<Farscape::VertexBuffer> triangleVertexBuffer;
        triangleVertexBuffer.reset(Farscape::VertexBuffer::Create(vertices, sizeof(vertices)));

        Farscape::BufferLayout layout = {
            {Farscape::ShaderDataType::Float3, "a_Position"},
            {Farscape::ShaderDataType::Float4, "a_Color"}
        };

        // make sure to set layout BEFORE adding the vertex buffer
        triangleVertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(triangleVertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        Farscape::Ref<Farscape::IndexBuffer> triangleIndexBuffer;
        triangleIndexBuffer.reset(Farscape::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(triangleIndexBuffer);



        // *********************************************************
        // *********  Make a square using the new system  **********
        // *********************************************************
        m_SquareVA = Farscape::VertexArray::Create();


        // 
        float squareVertices[5 * 4] = {	
                    /* Float3 : a_Position */       /* Float2 : a_TexCoord */
            /* bl */   -0.5f, -0.5f, 0.0f,             0.0f, 0.0f,
            /* tl */    0.5f, -0.5f, 0.0f,             1.0f, 0.0f,
            /* tr */    0.5f,  0.5f, 0.0f,             1.0f, 1.0f,
            /* br */   -0.5f,  0.5f, 0.0f,             0.0f, 1.0f
        };

        Farscape::Ref<Farscape::VertexBuffer> squareVB;
        squareVB.reset(Farscape::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        Farscape::BufferLayout squareLayout = {
            {Farscape::ShaderDataType::Float3, "a_Position"},
            {Farscape::ShaderDataType::Float2, "a_TexCoord"}
        };

        squareVB->SetLayout(squareLayout);
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        Farscape::Ref<Farscape::IndexBuffer> squareIndexBuffer;
        squareIndexBuffer.reset(Farscape::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIndexBuffer);

         std::string varColorVertexSrc = R"(

            #version 330 core

            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjectionMat;
            uniform mat4 u_Transform;

            out vec3 v_Position;
            
            void main()

            {
                v_Position = a_Position;
                gl_Position = u_ViewProjectionMat * u_Transform * vec4(a_Position, 1.0);
            }

    )";

        std::string varColorFragmentSrc = R"(

            #version 330 core

            layout(location = 0) out vec4 color;

            uniform vec3 u_Color;

            in vec3 v_Position;

            void main()
            {
                color = vec4(u_Color, 1.0);
            }

    )";


        m_ShaderBlue = Farscape::Shader::Create("transform_sample", varColorVertexSrc, varColorFragmentSrc); // std::make_unique<Farscape::Shader>(varColorVertexSrc, varColorFragmentSrc);
                
        //m_TextureShader.reset(Farscape::Shader::Create(textureShaderVertexSrc, textureShaderFragmentSrc));

#if defined(DEBUG_TEXTURE_PATH)
        m_ShaderLibrary.Load(DEBUG_SHADER_PATH);
        m_Texture = Farscape::Texture2D::Create(DEBUG_TEXTURE_PATH);
        m_RgbaTexture = Farscape::Texture2D::Create(DEBUG_TEXTURE_RGBA_PATH);
#else

        m_ShaderLibrary.Load("assets/Shaders/Texture.glsl");
        m_Texture = Farscape::Texture2D::Create("assets/textures/Checkerboard.png");
        m_RgbaTexture = Farscape::Texture2D::Create("assets/textures/rgba.png");
#endif

        auto textureSHader = m_ShaderLibrary.Get("Texture");

        std::dynamic_pointer_cast<Farscape::OpenGLShader>(textureSHader)->Bind();
        std::dynamic_pointer_cast<Farscape::OpenGLShader>(textureSHader)->UploadUniformInt("u_Texture", 0);
    }

    virtual void OnUpdate(Farscape::Timestep deltaTime) override
    {
        // Update 
        m_CameraController.OnUpdate(deltaTime);

        // Render
        Farscape::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Farscape::RenderCommand::Clear();

        Farscape::Renderer::BeginScene(m_CameraController.GetCamera());

        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        std::dynamic_pointer_cast<Farscape::OpenGLShader>(m_ShaderBlue)->Bind();
        std::dynamic_pointer_cast<Farscape::OpenGLShader>(m_ShaderBlue)->UploadUniformFloat3("u_Color", m_SquareColor);

        for (int y = 0; y < 10; y++)
        {
            for (int x = 0; x < 10 ; x++)
            {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Farscape::Renderer::Submit(m_ShaderBlue, m_SquareVA, transform);
            }
        }
        
        auto textureSHader = m_ShaderLibrary.Get("Texture");

        m_Texture->Bind();
        Farscape::Renderer::Submit(textureSHader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

        m_RgbaTexture->Bind();
        Farscape::Renderer::Submit(textureSHader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        
        Farscape::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Farscape Setting");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
        ImGui::End();
    }

    virtual void OnEvent(Farscape::Event& event) override
    {
        m_CameraController.OnEvent(event);
    }

    bool OnKeyPreddesHandler(Farscape::KeyPressedEvent& event)
    {
        return false;
    }
private:
    // use the new shader library 
    Farscape::ShaderLibrary m_ShaderLibrary;

    Farscape::Ref<Farscape::Texture2D> m_Texture;
    Farscape::Ref<Farscape::Texture2D> m_RgbaTexture;
    Farscape::Ref<Farscape::VertexArray> m_VertexArray;
    Farscape::Ref<Farscape::Shader> m_ShaderBlue;
    Farscape::Ref<Farscape::VertexArray> m_SquareVA;

    Farscape::OrthographicCameraController m_CameraController;

    glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

};

class Sandbox : public Farscape::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
        PushLayer(new DemoLayer2D());
    }

    ~Sandbox()
    {

    }
};

Farscape::Application* Farscape::CreateApplication()
{
    return new Sandbox();
}
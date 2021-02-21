#include "Farscape.h"

#include "Windows/OpenGLShader.h"
#include <imgui.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// create an example layer
class ExampleLayer : public Farscape::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
        , m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) 
        , m_cameraPosition {0.0f}
    {
        m_VertexArray.reset(Farscape::VertexArray::Create());

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



        // **********************
        // *********  Make a square using the new system
        // *************************************************
        m_SquareVA.reset(Farscape::VertexArray::Create());

        float squareVertices[4 * 3] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };

        Farscape::Ref<Farscape::VertexBuffer> squareVB;
        squareVB.reset(Farscape::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        Farscape::BufferLayout squareLayout = {
            {Farscape::ShaderDataType::Float3, "a_Position"}
        };

        squareVB->SetLayout(squareLayout);
        m_SquareVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        Farscape::Ref<Farscape::IndexBuffer> squareIndexBuffer;
        squareIndexBuffer.reset(Farscape::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIndexBuffer);

        // temp shader souece code
        std::string vertexSrc = R"(

            #version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjectionMat;
            uniform mat4 u_Transform;

            out vec3 v_Position;
            out vec4 v_Color;
            
            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjectionMat * u_Transform * vec4(a_Position, 1.0);
            }

    )";

        std::string fragmentSrc = R"(

            #version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;            

            void main()
            {
                color = vec4(v_Position * 0.5 + 0.5, 1.0);
                color = v_Color;
            }

    )";


        m_Shader.reset(Farscape::Shader::Create(vertexSrc, fragmentSrc));


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


        m_ShaderBlue.reset(Farscape::Shader::Create(varColorVertexSrc, varColorFragmentSrc)); // std::make_unique<Farscape::Shader>(varColorVertexSrc, varColorFragmentSrc);
    }

    virtual void OnUpdate(Farscape::Timestep deltaTime) override
    {
        if(Farscape::Input::IsKeyPressed(FS_KEY_A))
            m_cameraPosition.x -= m_cameraSpeed * deltaTime;
        if (Farscape::Input::IsKeyPressed(FS_KEY_D))
            m_cameraPosition.x += m_cameraSpeed * deltaTime;
        if (Farscape::Input::IsKeyPressed(FS_KEY_S))
            m_cameraPosition.y -= m_cameraSpeed * deltaTime;
        if (Farscape::Input::IsKeyPressed(FS_KEY_W))
            m_cameraPosition.y += m_cameraSpeed * deltaTime;

        if (Farscape::Input::IsKeyPressed(FS_KEY_E))
            m_cameraAngle -= m_degPerSecRotation * deltaTime;
        if (Farscape::Input::IsKeyPressed(FS_KEY_Q))
            m_cameraAngle += m_degPerSecRotation * deltaTime;
        

        Farscape::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Farscape::RenderCommand::Clear();

        m_Camera.SetPosition(m_cameraPosition);
        m_Camera.SetRotation(m_cameraAngle);


        Farscape::Renderer::BeginScene(m_Camera);

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
        
        Farscape::Renderer::Submit(m_Shader, m_VertexArray);
        
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
        Farscape::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Farscape::KeyPressedEvent>(BIND_EVENT_FN(ExampleLayer::OnKeyPreddesHandler));
    }

    bool OnKeyPreddesHandler(Farscape::KeyPressedEvent& event)
    {
        return false;
    }
private:
    Farscape::Ref<Farscape::Shader> m_Shader;
    Farscape::Ref<Farscape::VertexArray> m_VertexArray;

    Farscape::Ref<Farscape::Shader> m_ShaderBlue;
    Farscape::Ref<Farscape::VertexArray> m_SquareVA;

    Farscape::OrthographicCamera m_Camera;
    glm::vec3 m_cameraPosition;
    float m_cameraSpeed = 1.0f;
    float m_degPerSecRotation = 180.0f;
    float m_cameraAngle = 0.0f;

    glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };

};

class Sandbox : public Farscape::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
        // DO NOT CREATE AN IMGUI LAYER HERE
        // PushLayer(new Farscape::ImGuiLayer());
    }

    ~Sandbox()
    {

    }
};

Farscape::Application* Farscape::CreateApplication()
{
    return new Sandbox();
}
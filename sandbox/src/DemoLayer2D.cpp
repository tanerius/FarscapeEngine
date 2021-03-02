#include "DemoLayer2D.h"
#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Windows/OpenGLShader.h"

DemoLayer2D::DemoLayer2D()
	: Layer("DemoLayer2D"), m_CameraController(1280.0f / 720.0f)
{
}

void DemoLayer2D::OnAttach()
{
	m_SquareVA = Farscape::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Farscape::Ref<Farscape::VertexBuffer> squareVB;
	squareVB.reset(Farscape::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{ Farscape::ShaderDataType::Float3, "a_Position" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Farscape::Ref<Farscape::IndexBuffer> squareIB;
	squareIB.reset(Farscape::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squareIB);

	std::string ShaderFilePath = ASSETS_PATH;

	m_FlatColorShader = Farscape::Shader::Create(ShaderFilePath + "/Shaders/FlatColor.glsl");
}

void DemoLayer2D::OnDetach()
{
}

void DemoLayer2D::OnUpdate(Farscape::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Farscape::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Farscape::RenderCommand::Clear();

	Farscape::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Farscape::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Farscape::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Farscape::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Farscape::Renderer::EndScene();
}

void DemoLayer2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void DemoLayer2D::OnEvent(Farscape::Event& e)
{
	m_CameraController.OnEvent(e);
}
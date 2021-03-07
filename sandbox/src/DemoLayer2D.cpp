#include "DemoLayer2D.h"
#include <imgui.h>

#pragma warning(disable:4201)
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#pragma warning(default:4201)

#include "platform/Windows/OpenGLShader.h"

DemoLayer2D::DemoLayer2D()
	: Layer("DemoLayer2D")
	, m_CameraController(1280.0f / 720.0f, true)
{
}

void DemoLayer2D::OnAttach()
{

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

	Farscape::Renderer2D::BeginScene(m_CameraController.GetCamera());
	Farscape::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Farscape::Renderer2D::EndScene();
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
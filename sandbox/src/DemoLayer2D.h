#pragma once

#include "Farscape.h"

class DemoLayer2D : public Farscape::Layer
{
public:
	DemoLayer2D();
	virtual ~DemoLayer2D() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(Farscape::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Farscape::Event& e) override;
private:

	Farscape::Ref<Farscape::VertexArray> m_SquareVA;
	Farscape::Ref<Farscape::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
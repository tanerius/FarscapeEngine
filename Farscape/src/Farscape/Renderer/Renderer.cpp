#include "fspch.h"
#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Camera.h"
#include "Renderer/Shader.h"
#include <glm/glm.hpp>

#include "platform/Windows/OpenGLShader.h"
#include "Renderer/Renderer2D.h"

namespace Farscape {
    Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

    void Renderer::OnWindowResize(uint32_t width, uint32_t height)
    {
        RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        s_SceneData->ViewProjectionMatrix = camera.GetMatrix(EMatrixType::E_ViewProjection);
    }

    void Renderer::EndScene()
    {}

    void Renderer::Init()
    {
        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::Submit(
        const Farscape::Ref<Shader>& shader,
        const Farscape::Ref<VertexArray>& vertexArray,
        const glm::mat4& transform
    )
    {
        shader->Bind();
        // for now do this
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjectionMat", s_SceneData->ViewProjectionMatrix);
        std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

}

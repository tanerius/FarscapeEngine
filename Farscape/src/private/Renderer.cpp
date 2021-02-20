#include "fspch.h"
#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Camera.h"
#include "Renderer/Shader.h"
#include <glm/glm.hpp>

namespace Farscape {
	Renderer::SceneData* Renderer::s_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetMatrix(EMatrixType::E_ViewProjection);
	}

	void Renderer::EndScene()
	{}

	void Renderer::Submit(
		const std::shared_ptr<Shader>& shader, 
		const std::shared_ptr<VertexArray>& vertexArray,
		const glm::mat4& transform
	)
	{
		shader->Bind();
		shader->UPloadUniformMat4("u_ViewProjectionMat", s_SceneData->ViewProjectionMatrix);
		shader->UPloadUniformMat4("u_Transform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
	
}

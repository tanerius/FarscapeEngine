#include "fspch.h"
#include "Renderer/Renderer.h"
#include "Renderer/VertexArray.h"

namespace Farscape {

	void Renderer::BeginScene()
	{}

	void Renderer::EndScene()
	{}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
	
}

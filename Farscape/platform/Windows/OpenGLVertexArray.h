#pragma once 
#include <memory>
#include "Renderer/VertexArray.h"

namespace Farscape {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray() {}
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer) override;

		
	private:
		std::vector<std::shared_ptr<VertexBuffer>> m_VertexBufferRefList;
		std::shared_ptr<IndexBuffer> m_IndexBufferRef;
		uint32_t m_RendererID;
	};

}

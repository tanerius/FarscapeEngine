#pragma once
#include <memory>
#include "Renderer/Buffer.h"

namespace Farscape {

    // This is probably an OpenGL only thing so we need to think about the architecture here for platform agnosticnessnessness
    class VertexArray : public IVertexArray, public RefCounter
    {
    public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const SharedRef<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const SharedRef<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<SharedRef<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const SharedRef<IndexBuffer>& GetIndexBuffer() const = 0;

		virtual RendererID GetRendererID() const = 0;

		static SharedRef<VertexArray> Create();
    };

}

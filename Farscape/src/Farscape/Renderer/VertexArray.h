#pragma once
#include <memory>
#include "Renderer/Buffer.h"

namespace Farscape {

    // This is probably an OpenGL only thing so we need to think about the architecture here for platform agnosticnessnessness
    class VertexArray : public IVertexArray, public RefCounted
    {
    public:
        virtual ~VertexArray() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
        virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

        virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const Ref<IndexBuffer>& GetIndexBuffer() const = 0;

        virtual RendererID GetRendererID() const = 0;

        static Ref<VertexArray> Create();
    };

}

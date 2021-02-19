#pragma once
#include <memory>
#include "Buffer.h"

namespace Farscape {

	// This is probably an OpenGL only thing so we need to think about the architecture here for platform agnisticnessnessness
	class VertexArray
	{
	public:
		virtual ~VertexArray() {}
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& IndexBuffer) = 0;

		static VertexArray* Create();
	};

}

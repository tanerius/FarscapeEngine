#pragma once

namespace Farscape {

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void SetData() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;


		// Shouold not belong  to 
		static VertexBuffer* create(float* vertices, uint32_t arraySize);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;


		// Shouold not belong  to 
		static IndexBuffer* create(uint32_t* indices, uint32_t arraySize);
	};

}

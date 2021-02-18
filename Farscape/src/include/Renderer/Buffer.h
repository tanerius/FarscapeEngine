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
		static VertexBuffer* Create(float* vertices, uint32_t arraySize);
	};

	class IndexBuffer {
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		// Shouold not belong  to 
		static IndexBuffer* Create(uint32_t* indices, uint32_t count);
	};

}

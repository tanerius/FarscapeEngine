#include "Renderer/Buffer.h"

namespace Farscape {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		virtual ~OpenGLVertexBuffer() override {}

		virtual void SetData() {}

		virtual void Bind() const override;
		virtual void Unbind() const override;
	private:
		uint32_t m_RendererID;
	};

}

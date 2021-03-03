#pragma once
#include "Core/Core.h"
#include "fspch.h"

namespace Farscape {

    class RenderCommandQueue : public IRenderCommandQueue
    {
    public:
        using RenderCommand = std::function<unsigned int(void*)>;
        typedef unsigned int(*RenderCommandFn)(void*);

        RenderCommandQueue();
        ~RenderCommandQueue();

        void Submit(const RenderCommand& command);
        void SubmitCommand(RenderCommandFn fn, void* params, unsigned int size);
        void Execute();
    private:
        unsigned char* m_CommandBuffer;
        unsigned char* m_CommandBufferPtr;
        unsigned int m_RenderCommandCount = 0;
    };



}
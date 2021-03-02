#pragma once

#include "Core/Core.h"

namespace Farscape {

    class GfxContext : public IContext
    {
    public:
        virtual ~GfxContext() {}
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };

}

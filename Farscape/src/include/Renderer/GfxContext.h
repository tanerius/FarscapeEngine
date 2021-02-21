#pragma once

namespace Farscape {

    class GfxContext
    {
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };

}

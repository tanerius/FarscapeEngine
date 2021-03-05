#include "fspch.h"
#include "Core/Core.h"

namespace Farscape {

    void Initialize()
    {
        Log::Init();
        FS_CORE_TRACE("Farscape Engine v{0}", Farscape_VERSION);
        FS_CORE_TRACE("Initialize...");
    }

    void Shutdown()
    {
        FS_CORE_TRACE("Shutdown...");
    }
}

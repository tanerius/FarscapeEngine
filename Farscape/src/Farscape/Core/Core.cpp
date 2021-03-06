#include "fspch.h"
#include "Core/Core.h"

namespace Farscape {

    void InitializeEngine()
    {
        Log::Init();
        FS_CORE_TRACE("Farscape Engine v{0}", Farscape_VERSION);
        FS_CORE_TRACE("Initialize...");
    }

    void ShutdownEngine()
    {
        FS_CORE_TRACE("Shutdown...");
    }
}

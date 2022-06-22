#pragma once
#include "base/include/base_global.h"
#include "common/include/event/Event.h"

namespace base
{
    enum Type{
        AppStarted = 1,
        AppToExit = 2,
        ModuleLoaded = 3,
        ModuleUnloaded = 4,
        

    }
}

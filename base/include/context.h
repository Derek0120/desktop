#pragma once
#include "base/include/base_global.h"
#include "common/include/logger.h"
#include <memory>
namespace common
{
    class IEventDispatcher;
    class ITaskScheduler;
}


namespace base
{
class BASE_EXPORT IContext
{
public:
    virtual ~IContext();

    virtual common::IEventDispatcher* eventDispatcher() = 0;


    virtual common::ITaskScheduler* defaultScheduler() = 0;

    /*
        used for gui thread 
    */
    virtual common::ITaskScheduler* mainThreadScheduler() = 0;

    // logger
    virtual std::shared_ptr<ILogger> defaultLogger() = 0;

};
}

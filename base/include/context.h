#pragma once
#include "base/include/base_global.h"
#include "common/include/logger.h"
#include "common/include/concurrent/TaskScheduler.h"
#include <memory>
namespace common
{
    class IEventDispatcher;
}


namespace base
{
class BASE_EXPORT IContext
{
public:
    struct  Option{
            common::ITaskScheduler::Option task_option;
            common::ILogger::Option logger_option;
        };
    static IContext* get();

    virtual ~IContext();

    virtual common::IEventDispatcher* eventDispatcher() = 0;


    virtual common::ITaskScheduler* defaultScheduler() = 0;

    /*
        used for gui thread 
    */
    virtual common::ITaskScheduler* mainThreadScheduler() = 0;

    // logger
    virtual common::ILogger* defaultLogger() = 0;

};

    namespace context_builder{
        BASE_EXPORT void createContext(const IContext::Option& option);
        BASE_EXPORT void destroyContext();
    }
}

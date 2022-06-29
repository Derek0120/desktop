#include "base/include/context.h"
#include "common/include/event/EventDispatcher.h"
#include "base/include/impl/mainSchedeler_impl.h"
namespace base
{
    namespace internel{
        std::shared_ptr<IContext> kGlobalContext;
    }
    IContext* IContext::get(){
        return internel::kGlobalContext.get();
    }
    IContext::~IContext() = default;

    class Context : public IContext
    {
    public:
    explicit Context(const Option& option)
    {
        dispatcher_ = common::dispatcher_builder::createDispatcher();
        defaultScheduler_ = common::task_builder::createTaskScheduler(option.task_option);
        mainThreadScheduler_ = std::make_shared<internal::MainThreadSchedulerImpl>();
        defaultLogger_ = common::logger_builder::createLogger(option.logger_option);
    }
    common::IEventDispatcher* eventDispatcher() override{
        return dispatcher_;
    }


    common::ITaskScheduler* defaultScheduler() override{
        return defaultScheduler_.get();
    }


    common::ITaskScheduler* mainThreadScheduler() override{
        return mainThreadScheduler_.get();
    }

   common::ILogger* defaultLogger() override{
        return defaultLogger_.get();
    }
    private:
        common::IEventDispatcher* dispatcher_;
        std::shared_ptr<common::ITaskScheduler> defaultScheduler_;
        std::shared_ptr<common::ITaskScheduler> mainThreadScheduler_;
        std::shared_ptr<common::ILogger> defaultLogger_;
    };  


    void context_builder::createContext(const IContext::Option& option){
        if(internel::kGlobalContext == nullptr){
            internel::kGlobalContext = std::make_shared<Context>(option);
        }
    }

    void context_builder::destroyContext(){
         internel::kGlobalContext = nullptr;
    }
}
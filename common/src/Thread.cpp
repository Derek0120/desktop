#include "common/include/concurrent/Thread.h"
#include <atomic>
#include <thread>
#include <memory>
namespace common{
class Thread::Impl {
public:
    std::string thread_name{};
    std::shared_ptr<std::thread> thread_;
    std::atomic_bool stop_called{ false };
};

Thread::Thread(const std::string& name)
    :impl_(new Impl)
{
    impl_->thread_name = name;
    
}

std::string Thread::name() const {
    return impl_->thread_name;
}

Thread::~Thread()
{
    delete impl_;
}

bool Thread::start()
{
    if (!impl_->stop_called.load() && nullptr == impl_->thread_) {
        impl_->thread_ = std::make_shared<std::thread>(&Thread::exec, this);
        return true;
    } 
    return false;
}

bool Thread::stop()
{
    bool stop = false;
    if (impl_->stop_called.compare_exchange_strong(stop, true)) {
        if (impl_->thread_->joinable()) {
            impl_->thread_->join();
            impl_->thread_ = nullptr;
        }
        return true;
    }
    return false;
}

bool Thread::stopped() const
{
    return impl_->stop_called.load();
}

void Thread::exec()
{
    if (!impl_->thread_name.empty()) {
        // set thread name
    }
    if (!beforeRun()) {
        return;
    }
    run();

    afterRun();
}

class SimpleThreadImpl : public Thread
{
public:
    SimpleThreadImpl(const std::string& name, std::function<bool(Thread*)> beforeFunc,
        std::function<void(Thread*)> runFunc,
        std::function<void(Thread*)> afterFunc)
        :Thread(name){
        if (nullptr != beforeFunc) {
            beforeFunc_ = std::bind(beforeFunc, this);
        }
        if (nullptr != runFunc) {
            runFunc_ = std::bind(runFunc, this);
        }
        if (nullptr != afterFunc) {
            afterFunc_ = std::bind(afterFunc, this);
        }       
    }

    bool beforeRun() override {
        if (nullptr != beforeFunc_) {
            return beforeFunc_();
        }
        return true;
    }

    void run() override {
        if (nullptr != runFunc_) {
            return runFunc_();
        }
    }

    void afterRun() override {
        if (nullptr != afterFunc_) {
            return afterFunc_();
        }
    }

private:
    std::function<bool()> beforeFunc_;
    std::function<void()> runFunc_;
    std::function<void()> afterFunc_;
};


std::shared_ptr<Thread> thread_builder::createThread(const std::string& name, std::function<void(Thread*)> run) {
    return std::make_shared<SimpleThreadImpl>(name, nullptr, run, nullptr);
}

ThreadPtr thread_builder::createThreadWithFullParms(const std::string& name,
    std::function<bool(Thread*)> beforeFunc,
    std::function<void(Thread*)> runFunc,
    std::function<void(Thread*)> afterFunc) {
    return std::make_shared<SimpleThreadImpl>(name, beforeFunc, runFunc, afterFunc);
}

}
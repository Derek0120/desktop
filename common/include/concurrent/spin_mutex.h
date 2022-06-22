#pragma once
#include <atomic>
#include <thread>
namespace common{
class spin_mutex
{
public:
    spin_mutex() : flag_() {}

    void lock()
    {
        while (flag_.test_and_set())
        {
            std::this_thread::yield();
        }
    }
    void unlock() { flag_.clear(); }

    bool try_lock() { 
        return flag_.test_and_set();
    }

    spin_mutex(const spin_mutex&) = delete;
    spin_mutex& operator=(const spin_mutex&) = delete;
private:
    std::atomic_flag flag_;
};

}
#pragma once
#include "common/include/common_global.h"
#include <functional>
namespace common{
using TackClosure = std::function<void()>;

enum SpecialSequence : uint64_t {
    kNone = 0,  // at the end of the task queue
    KMax = UINT64_MAX  // with the high Priority
};

struct COMMON_EXPORT Task 
{
    Task();
    explicit Task(TackClosure task, uint64_t sequence = kNone);
    ~Task();
    Task(Task&& other);
    Task& operator=(Task&& other);
    Task(const Task& other);
    Task& operator=(const Task& other);
    bool operator<(const Task& other) const;
       
    uint64_t sequence() const;

    void exec();
private:
    TackClosure task_;
    int64_t sequence_;
};
}
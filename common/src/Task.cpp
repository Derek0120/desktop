#include "common/include/concurrent/Task.h"
namespace common{
Task::Task()
	:task_(), sequence_(kNone) {
}

Task::Task(TackClosure task, uint64_t sequence)
	:task_(std::move(task)), sequence_(sequence){
}

Task::~Task() = default;

Task::Task(Task&& other) = default;
Task& Task::operator=(Task&& other) = default;
Task::Task(const Task& other) = default;
Task& Task::operator=(const Task& other) = default;

bool Task::operator<(const Task& other) const
{
	return this->sequence() < other.sequence();
}

uint64_t Task::sequence() const
{
	return sequence_;
}

void Task::exec()
{
	if (task_) {
		task_();
	}
}

}
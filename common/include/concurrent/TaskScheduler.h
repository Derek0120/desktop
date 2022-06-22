#pragma once
#include "common/include/common_global.h"
#include "Task.h"
#include <string>
#include <vector>
#include <memory>
namespace common{
class COMMON_EXPORT ITaskScheduler
{
public:
	struct Options {
		//if 0 or 1 will create one thread, otherwise create thread_pool
		std::uint32_t thread_count;
		//task thread names if names.size() < thread_count
		// the last threads share the same name as before
		std::vector<std::string> names;
		//task thread sleep ms when task queue is empty
		//if ms = 0,  yield is executed
		uint32_t ms;
		//if true, the reserved task after stop executed will execute when TaskRunner before destoryed
		bool isExecuteOnDestory;
	};

	virtual ~ITaskScheduler();

	virtual void postTask(const Task& task) = 0;

	virtual bool start() = 0;

	virtual bool stop() = 0;

	virtual bool stopped() const = 0;
};

namespace task_builder {
	COMMON_EXPORT std::shared_ptr<ITaskScheduler> createTaskScheduler(const ITaskScheduler::Options& options);
}

}
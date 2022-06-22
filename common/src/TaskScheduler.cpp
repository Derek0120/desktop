#include "common/include/concurrent/TaskScheduler.h"
#include "common/include/concurrent/Queue.h"
#include "common/include/concurrent/Thread.h"
#include <atomic>
#include <exception>
namespace common{
struct Impl {
public:
	using Container = typename Priority_Queue<Task, std::mutex>;
	void run(Thread* pThread) {
		Task task;
		while (!pThread->stopped()){
			if (container_.try_pop(task)) {
				task.exec();
			}
			else {
				if (0 == msSleep_) {
					std::this_thread::yield();
				}
				else {
					std::this_thread::sleep_for(std::chrono::milliseconds(msSleep_));
				}
			}
		}
	}

	bool start() {
		if (stopped_.load()) {
			return false;
		}
		bool ret = true;
		for (auto threadPtr : threads_) {
			if (!threadPtr->start()) {
				ret = false;
			}
		}
		return ret;
	}

	bool stop() {
		if (stopped_.load()) {
			return false;
		}
		bool ret = true;
		for (auto threadPtr : threads_) {
			if (!threadPtr->stop()) {
				ret = false;
			}
		}
		stopped_.store(true);
		return ret;
	}

	bool stopped() const {
		return stopped_.load();
	}

	Container container_;
	std::vector<ThreadPtr> threads_;
	//ThreadPtr thread_;
	uint32_t msSleep_{0};
	bool executeOnDestory_{ false };
	std::atomic_bool stopped_{false};
};

class TaskScheduler : public ITaskScheduler
{
public:
	explicit TaskScheduler(const Options& options);
	~TaskScheduler();

	void postTask(const Task& task) override;

	bool start() override;

	bool stop() override;

	bool stopped() const override;

private:
	Impl* impl_;
};

TaskScheduler::TaskScheduler(const Options& options)
	:impl_(new Impl){
	impl_->msSleep_ = options.ms;
	impl_->executeOnDestory_ = options.isExecuteOnDestory;
	auto func = std::bind(&Impl::run, impl_, std::placeholders::_1);

	uint32_t count = options.thread_count > 0 ? options.thread_count : 1;
	impl_->threads_.reserve(count);
	auto nameCount = options.names.size();
	std::string name;
	for (uint32_t index = 0; index < count; ++index) {	
		if (nameCount > index) {
			name = options.names.at(index);
		}
		impl_->threads_ .push_back( thread_builder::createThread(name, func));
	}
	
}


TaskScheduler::~TaskScheduler(){
	if (!stopped()) {
		stop();
	}
	if (impl_->executeOnDestory_) {
		Task task;
		while (impl_->container_.try_pop(task)) {
			task.exec();
		}
	}
	delete impl_;
}

void TaskScheduler::postTask(const Task& task){
	if (stopped()) {
		throw std::runtime_error("task runner is stopped.");
	}
	bool ret = impl_->container_.try_push(task);
	if (!ret) {
		throw std::runtime_error("task queue is full");
	}
}


bool TaskScheduler::start(){
	return impl_->start();
}

bool TaskScheduler::stop()
{
	return impl_->stop();
}

bool TaskScheduler::stopped() const{
	return impl_->stopped();
}

ITaskScheduler::~ITaskScheduler() = default;


std::shared_ptr<ITaskScheduler> task_builder::createTaskScheduler(const ITaskScheduler::Options& options) {
	return std::make_shared<TaskScheduler>(options);
}

}
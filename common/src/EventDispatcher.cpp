#include "common/include/event/EventDispatcher.h"
#include "common/include/event/Event.h"
#include "common/include/event/EventListener.h"
#include "common/include/concurrent/TaskScheduler.h"
#include "common/include/concurrent/Task.h"
#include <unordered_map>
#include <vector>
#include <mutex>
namespace common{
IEventDispatcher::~IEventDispatcher() = default;

class EventDispatcherImpl : public IEventDispatcher
{
public:
	virtual ~EventDispatcherImpl(){}

	void registerEventListener(std::uint32_t type, IEventListener* listener) override {
		std::lock_guard<std::mutex> lk(mtx_);
		auto finder = std::find(mapListener_[type].begin(), mapListener_[type].end(), listener);
		if (mapListener_[type].end() == finder) {
			mapListener_[type].push_back(listener);
		}
	}
	void unregisterEventListener(std::uint32_t type, IEventListener* listener) override {
		std::lock_guard<std::mutex> lk(mtx_);
		auto findVs = mapListener_.find(type);
		if (findVs != mapListener_.end()) {
			auto finder = std::find(findVs->second.begin(), findVs->second.end(), listener);
			if (findVs->second.end() != finder) {
				findVs->second.erase(finder);
			}
			if (findVs->second.empty()) {
				mapListener_.erase(findVs);
			}
		}
	}
	void postEvent(std::shared_ptr<IEvent> eventPtr, std::shared_ptr<ITaskScheduler> scheduler) override {
		std::lock_guard<std::mutex> lk(mtx_);
		auto findVs = mapListener_.find(eventPtr->type());
		if (findVs != mapListener_.end()) {
			for (IEventListener* listener : findVs->second) {
				// 
				auto task = [listener, eventPtr]() {
					listener->onEvent(eventPtr);
				};
				if (scheduler) {
					scheduler->postTask(Task(task, 0));
				}
				else {
					task();
				}
			}
		}
	}

private:
	std::mutex mtx_;
	std::unordered_map< std::uint32_t, std::vector< IEventListener*> > mapListener_;
};

IEventDispatcher* dispatcher_builder::createDispatcher()
{
    return nullptr;
}
}
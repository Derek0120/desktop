#pragma once
#include "common/include/common_global.h"
#include <cstdint>
#include <memory>
namespace common{
class IEvent;
class IEventListener;
class ITaskScheduler;
class COMMON_EXPORT IEventDispatcher
{
public:
	virtual ~IEventDispatcher();

	virtual void registerEventListener(std::uint32_t type, IEventListener* listener) = 0;
	virtual void unregisterEventListener(std::uint32_t type, IEventListener* listener) = 0;

	/*
		if scheduler == nullptr, executed on current thread else send to the specified thread
	*/
	virtual void postEvent(std::shared_ptr<IEvent> eventPtr, std::shared_ptr<ITaskScheduler> scheduler) = 0;
};

namespace dispatcher_builder
{
	COMMON_EXPORT IEventDispatcher* createDispatcher();
}

}
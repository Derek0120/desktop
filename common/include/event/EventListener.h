#pragma once
#include "common/include/common_global.h"
#include <memory>
namespace common{
class IEvent;
class EventDispatcherImpl;
class COMMON_EXPORT IEventListener
{
public:
	friend class EventDispatcherImpl;

	virtual ~IEventListener();
protected:
	virtual void onEvent(std::shared_ptr<IEvent> eventPtr) = 0;
};

}
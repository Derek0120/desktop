#pragma once
#include <cstdint>
#include "common/include/common_global.h"
namespace common{
class COMMON_EXPORT IEvent
{
public:
	virtual ~IEvent();

	virtual std::uint32_t type() = 0;
};

}
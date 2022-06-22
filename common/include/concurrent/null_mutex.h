#pragma once
#include <mutex>

namespace common{

class null_mutex {
public:
	null_mutex() = default;
	~null_mutex() = default;
	void lock() {}

	bool try_lock() { return true; }

	void unlock() { }
	null_mutex(const null_mutex&) = delete;
	null_mutex& operator=(const null_mutex&) = delete;
};
}
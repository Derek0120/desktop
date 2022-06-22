#pragma once
#include <queue>
#include <list>
#include <mutex>
#include <stdint.h>
#include "common/include/concurrent/null_mutex.h"
namespace common{
template <typename T, typename MutexType = null_mutex>
class Queue
{
public:
	explicit Queue(std::size_t max = UINTMAX_MAX / sizeof(T))
		:max_(max){}

	bool try_push(const T& v) {
		std::lock_guard<MutexType> lk(mtx_);
		if (container_.size() < max_) {
			container_.push_back(v);
			return true;
		}
		return false;
	}

	bool try_pop(T& v) {
		std::lock_guard<MutexType> lk(mtx_);
		if (!container_.empty()) {
			v = container_.front();
			container_.pop();
			return true;
		}
		return false;
	}

	std::size_t size() const {
		std::lock_guard<MutexType> lk(mtx_);
		return container_.size();
	}

	bool empty() const {
		std::lock_guard<MutexType> lk(mtx_);
		return container_.empty();
	}


private:
	std::size_t max_;
	std::queue<T> container_;
	mutable MutexType mtx_;
	std::less<T> comp_;	
};

template <typename T, typename MutexType = null_mutex>
class Priority_Queue
{
public:
	explicit Priority_Queue(std::size_t max = UINT32_MAX / sizeof(T))
		:max_(max) {}

	bool try_push(const T& v) {
		std::lock_guard<MutexType> lk(mtx_);
		if (container_.size() < max_) {
			container_.push(v);
			return true;
		}
		return false;
	}

	bool try_pop(T& v) {
		std::lock_guard<MutexType> lk(mtx_);
		if (!container_.empty()) {
			v = container_.top();
			container_.pop();
			return true;
		}
		return false;
	}

	std::size_t size() const {
		std::lock_guard<MutexType> lk(mtx_);
		return container_.size();
	}

	bool empty() const {
		std::lock_guard<MutexType> lk(mtx_);
		return container_.empty();
	}


private:
	std::size_t max_;
	std::priority_queue<T> container_;
	mutable MutexType mtx_;
	std::less<T> comp_;
};

}
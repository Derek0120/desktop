#pragma once
#include "common/include/common_global.h"
#include <string>
#include <memory>
#include <functional>
namespace common{
class COMMON_EXPORT Thread
{
public:
	explicit Thread(const std::string& name);

	std::string name() const;

	virtual ~Thread();
	/*
		if return true, run will not be executed
	*/
	virtual bool beforeRun() = 0;

	/*
		the actual function run in the thread 
	*/
	virtual void run() = 0;

	virtual void afterRun() = 0;

	bool start();

	bool stop();

	bool stopped() const;
protected:
	void exec();

private:
	class Impl;
	Impl* impl_;
};

using ThreadPtr = std::shared_ptr<Thread>;

namespace thread_builder {
	COMMON_EXPORT ThreadPtr createThread(const std::string& name, std::function<void(Thread*)> run);

	COMMON_EXPORT ThreadPtr createThreadWithFullParms(const std::string& name,
							std::function<bool(Thread*)> beforeFunc,
							std::function<void(Thread*)> runFunc,
							std::function<void(Thread*)> afterFunc);
}

}
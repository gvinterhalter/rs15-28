#include "Worker.h"

namespace mfe{

	unsigned int Worker::workerCount = 0;
	std::queue<Task> Worker::taskQueue;

	Worker::Worker() :
		mId(++workerCount) // ovo bi kao trebalo da je atomicka operacija
	{

	}

}
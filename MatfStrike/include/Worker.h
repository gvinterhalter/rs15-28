#pragma once

#include <string>
#include <iostream>
#include <mutex>
#include <algorithm>

#include <thread>
#include <queue>

#include "Task.h"

namespace mfe {

	class Worker{
	public:
		Worker();

		void operator() ();

	protected:
		static std::queue<Task> taskQueue;
		static unsigned int workerCount;
		unsigned int mId;

	};
}
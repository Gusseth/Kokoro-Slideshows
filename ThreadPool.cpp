#include "ThreadPool.h"

namespace Shameimaru {
	void ThreadPool::Start() {
		stop = false;
		stopSignal.notify_all();
	}

	void ThreadPool::Enqueue(Task t)
	{
		tasks.enqueue(t);
	}

	void ThreadPool::Enqueue(vector<Task> t)
	{
		for (Task & task : t) {
			tasks.enqueue(task);
		}
	}

	void ThreadPool::threadExecutionLoop()
	{
		
	}

	void ThreadPool::Stop() {
		stop = true;
		stopSignal.notify_all();

		for (thread & t : threads) {
			t.join();
		}
	}
}
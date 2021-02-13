#include "ThreadPool.h"

namespace Shameimaru {
	/*
	ThreadPool::ThreadPool(unsigned threadCount)
	{
		threadNum = threadCount;
		threads = new thread[threadCount];
		threadsActivated = true;

		/*
		for (int i = 0; i < threadCount; i++) {
			lock_guard<mutex> lock(m);
			threads[i] = thread([=] { 
			printf("Thread %x is running.\n", this_thread::get_id());
			while (1) {
				function<void()> func;
				{
					// Threads have been deactivated. Terminate thread.
					if (!threadsActivated) {
						return;
					}

					// Grab a function from the pool
					func = move(queue.front());
					queue.pop();
					//queue.pop();
				}
				func();
			}
				});
		}
		
	}

	ThreadPool::~ThreadPool()
	{
		stop();
	}

	bool ThreadPool::enqueue(function<void()> enq)
	{
		{
			lock_guard<mutex> lock(m);
		}
		queue.emplace(move(enq));
		return true;
	}

	void ThreadPool::stop() noexcept
	{
		threadsActivated = false;
		for (int i = 0; i < threadNum; i++) {
			threads[i].join();
		}
	}

	void ThreadPool::start()
	{
		for (auto i = 0u; i < threadNum; ++i)
		{
			vec.emplace_back([=] {
				while (true)
				{
					function<void()> task;

					{
						std::unique_lock<std::mutex> lock{ m };

						threadEvent.wait(lock, [=] { return threadsActivated || !queue.empty(); });

						if (threadsActivated && queue.empty())
							break;

						task = std::move(queue.front());
						queue.pop();
					}

					task();
				}
				});
		}
	}

	void ThreadPool::executionLoop()
	{
		lock_guard<mutex> lock(m);
		function<void()> func;
		printf("Thread %x is running.", this_thread::get_id());
		while (1) {
			{
				// Threads have been deactivated. Terminate thread.
				if (!threadsActivated) {
					return;
				}

				// Do nothing if queue is empty.
				if (queue.empty()) {
					continue;
				}

				// Grab a function from the pool
				func = move(queue.front());
				queue.pop();
			}

			func();
		}
	}
	*/
}
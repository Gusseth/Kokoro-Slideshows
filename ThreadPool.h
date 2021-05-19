/*
*	Shameimaru thread pool library.
*	Please make sure to set cores less than or equal to the number of processors you have. You will have a bad time otherwise.
*
*	ありがとうございます。
*/

#pragma once
#include <functional>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <vector>
#include "SimpleQueue.h"
using namespace std;

namespace Shameimaru {
    class ThreadPool
    {
    public:
        using Task = function<void()>;

        /// <summary>
        /// Creates a new thread pool.
        /// </summary>
        /// <param name="num_threads">Number of threads dedicated for task execution.</param>
        /// <param name="cores">Number of cores/processors that the threads will run from (default: 2)</param>
        explicit ThreadPool(size_t num_threads, char cores = 2)
        {
            threads.reserve(num_threads);
            numThreads = num_threads;

            for (int i = 0; i < num_threads; i++) {
                thread newThread;    // stub
                threads.push_back(newThread);
            }
        }

        ~ThreadPool()
        {
            Stop();
        }
        
        /// <summary>
        /// Stops all threads in the pool. Waits the threads to finish before putting them to sleep.
        /// </summary>
        void Stop();

        /// <summary>
        /// Start the thread pool. All threads will begin executing tasks in the task pool.
        /// </summary>
        void Start();

        /// <summary>
        /// Enqueues a void function into the pool for execution.
        /// </summary>
        /// <param name="t">A non-returning function to add to the pool</param>
        void Enqueue(Task t);

        /// <summary>
        /// Enqueues a vector of void functions into the pool.
        /// </summary>
        /// <param name="t">Vector of tasks to add to the pool.</param>
        void Enqueue(vector<Task> t);

        /// <summary>
        /// Returns true if all threads are awaiting for a new task; empty task pool.
        /// </summary>
        /// <returns>True if the task pool is empty, false otherwise.</returns>
        bool IsPoolEmpty() { return !numTasks; };

    private:
        // Thread pool.
        vector<thread> threads;

        // Task pool.
        SimpleQueue<Task> tasks;

        // Main mutex for the pool.
        mutex m;

        // Condition variable that signals a stop.
        condition_variable stopSignal;

        // Number of threads dedicated for execution.
        unsigned numThreads;

        // Number of tasks awaiting execution.
        unsigned numTasks;

        // Bool to stop threads.
        bool stop = true;

        /// <summary>
        /// Main function that all threads in the pool loop over.
        /// </summary>
        void threadExecutionLoop();
    };
}


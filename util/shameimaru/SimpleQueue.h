/*
*	This is designed to be thread-safe. Use this instead of std::queue.
* 
*	Thank you.
*/


#pragma once
#include <mutex>
#include "SimpleStack.h"

using namespace std;

namespace Shameimaru {
	template <typename T>
	class SimpleQueue
	{
	public:
		SimpleQueue();
		
		bool enqueue(const T& element);

		T dequeue();

		//T peek() const;

		//unsigned size() { return !_size; }

	private:
		T moveStack();

		SimpleStack<T> stack1;
		SimpleStack<T> stack2;
		//unsigned _size;
		mutex m;
	};
}


/*
*	This is designed to be thread-safe. 
*	Use this instead of std::queue to save yourself from (some) segfaults.
* 
*	ありがとうございます。
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

		bool empty() const;

	private:
		unsigned queued = 0;
		SimpleStack<T> stack1;
		SimpleStack<T> stack2;
		//unsigned _size;
		mutex m;
	};
}


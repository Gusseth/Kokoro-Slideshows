#include "SimpleQueue.h"

template<typename T>
Shameimaru::SimpleQueue<T>::SimpleQueue()
{
}

template<typename T>
bool Shameimaru::SimpleQueue<T>::enqueue(const T& element)
{
	lock_guard<mutex> lock(m);
	stack1.push(element);
	return true;
}

template<typename T>
T Shameimaru::SimpleQueue<T>::dequeue()
{
	lock_guard<mutex> lock(m);
	T out = stack2.pop();

	if (stack2.empty())
		while (!stack1.empty())
			stack2.push(stack1.pop());

	return out;
}
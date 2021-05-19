#include "SimpleQueue.h"

template<typename T>
Shameimaru::SimpleQueue<T>::SimpleQueue()
{
	m = new mutex();
}

template<typename T>
bool Shameimaru::SimpleQueue<T>::enqueue(const T& element)
{
	lock_guard<mutex> lock(m);
	stack1.push(element);
	queued++;
	return true;
}

template<typename T>
T Shameimaru::SimpleQueue<T>::dequeue()
{
	lock_guard<mutex> lock(m);
	T out = stack2.pop();
	queued--;

	if (stack2.empty())
		while (!stack1.empty())
			stack2.push(stack1.pop());

	return out;
}

template<typename T>
bool Shameimaru::SimpleQueue<T>::empty() const
{
	lock_guard<mutex> lock(m);
	return !queued;
}

#include "SimpleStack.h"

template<typename T>
Shameimaru::SimpleStack<T>::SimpleStack()
{
	stack = new T[INIT_STACK_CAPACITY];
	_max = INIT_STACK_CAPACITY;
	_size = 0;
}

template<typename T>
bool Shameimaru::SimpleStack<T>::push(const T & element)
{
	stack[_size] = element;
	_size++;
	if (_size >= _max) resize(_max * 2)
}

template<typename T>
T Shameimaru::SimpleStack<T>::pop()
{
	_size--;
	T popped = stack[_size];

	if (_size < _max / 4 && _max > INIT_STACK_CAPACITY) {
		resize(_max / 2);
	}

	return T();
}

template<typename T>
bool Shameimaru::SimpleStack<T>::resize(unsigned size)
{
	T* newStack = new T[size];

	for (int i = 0; i < _size; i++)
		newStack[i] = stack[i];

	delete[] stack;
	stack = newStack;
	_max = size;
	return true;
}

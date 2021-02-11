#pragma once

#define INIT_STACK_CAPACITY 16

namespace Shameimaru {
	template <typename T>
	class SimpleStack
	{
	public:
		SimpleStack();

		~SimpleStack() { delete[] _stack; }

		bool push(const T& element);

		T pop();

		bool empty() { return !_size; }

		unsigned capacity() { return _max; }

		unsigned size() { return _size; }

	private:
		bool resize(unsigned size);
		T* _stack;
		unsigned _size;
		unsigned _max;
		//bool _fixed;
	};
}


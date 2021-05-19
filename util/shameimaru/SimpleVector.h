#pragma once

namespace Shameimaru {
	template <typename T>
	class SimpleVector
	{
	public:
		SimpleVector(unsigned max) { _max = max; vec = new T[max]; }

		~SimpleVector() { delete[] vec; }

		bool push_back(T element);

		T pop_back();

		unsigned capacity() { return _max; }

		unsigned size() { return _size;  }

		T SimpleVector::operator[](unsigned index) {
			return vec[index];
		}

	private:
		unsigned _size;
		unsigned _max;
		T* vec;
	};
}

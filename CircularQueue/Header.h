#ifndef HEADER_H_
#define HEADER_H_

namespace cQueue {
	template<typename T>
	class CircularQueue {
	private:
		T * Arr;
		int Size, Top, Head;
		int isEmpty();
		int isFull();
	public:
		CircularQueue(int s);
		void push_back(T value);
		void pop();
	};
}

#endif


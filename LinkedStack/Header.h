#ifndef HEADER_H_
#define HEADER_H_

namespace LinkedStack {
	template<typename T>
	class Stack {
	private:
		struct Node {
			T value;
			Node* prev;
		};
		Node* top;
		int StackSize;
		bool isEmpty();
	public:
		explicit Stack();
		void push(T value);
		void pop();
		T peek();
		~Stack();
	};
}
#endif

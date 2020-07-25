#include <iostream>
#include "Header.h"

namespace LinkedStack {
	template<typename T>
	Stack<T>::Stack() {
		top = nullptr;
		StackSize = 0;
	}

	template<typename T>
	bool Stack<T>::isEmpty() {
		if (StackSize == 0)
			return true;

		return false;
	}

	template<typename T>
	void Stack<T>::push(T value) {
		using std::cout; using std::endl;
		Node* temp = new Node;

		if (isEmpty()) {
			temp->value = value;
			top = temp;
			cout << "Pushed: " << value << endl;
			StackSize++;
		}
		else {
			temp->value = value;
			temp->prev = top;
			top = temp;
			cout << "Pushed: " << value << endl;
			StackSize++;
		}
	}

	template<typename T>
	void Stack<T>::pop() {
		using std::cout; using std::endl;
		Node* temp = new Node;
		T NodeVal;

		if (!isEmpty()) {
			NodeVal = top->value;
			temp = top->prev;
			top->prev = nullptr;
			top = temp;
			StackSize--;
			cout << "Poped: " << NodeVal << endl;
		}
		else {
			cout << "Stack is Empty" << endl;
			return;
		}
	}

	template<typename T>
	T Stack<T>::peek() {
		if (!isEmpty())
			return top->value;
		else {
			return -1;
		}
	}

	template<typename T>
	Stack<T>::~Stack() {
		delete top, this;
	}
}
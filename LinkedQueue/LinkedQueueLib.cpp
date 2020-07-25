#include <iostream>
#include "Header.h"

namespace Queue {
	template<typename T>
	LinkedQueue<T>::LinkedQueue() {
		head = nullptr;
		tail = nullptr;
		QueueSize = 0;
	}

	template<typename T>
	void LinkedQueue<T>::Push(T value) {
		Node* temp = new Node;
		temp->data = value;

		if (isEmpty()) {
			head = temp;
			tail = temp;
			temp->next = nullptr;
			QueueSize++;
		}
		else {
			tail->next = temp;
			tail = temp;
			temp->next = nullptr;
			QueueSize++;
		}
	}
	
	template<typename T>
	void LinkedQueue<T>::Pop() {
		using std::cout; using std::endl;
		Node* temp = new Node;

		if (!isEmpty()) {
			temp = head->next;
			head->next = nullptr;
			head = temp;
			QueueSize--;
		}
		else {
			cout << "Queue is empty" << endl;
		}
	}
	
	template<typename T>
	T LinkedQueue<T>::Front() {
		return head->data;
	}

	template<typename T>
	T LinkedQueue<T>::Back() {
		return tail->data;
	}

	template<typename T>
	LinkedQueue<T>::~LinkedQueue() {
		delete head, tail, this;
		QueueSize = 0;
	}
}
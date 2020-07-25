#include <iostream>
#include "Header.h"

namespace ListClass {
	template<typename T>
	DoubleLinkedList<T>::DoubleLinkedList() {
		head = nullptr;
		tail = nullptr;
		z = nullptr;
		ListSize = 0;
	}

	template<typename T>
	void DoubleLinkedList<T>::InsertBack(T value) {
		Node* temp = new Node;
		temp->data = value;
		temp->next = nullptr;
		temp->prev = nullptr;

		if (head != nullptr)
			z = tail;

		if (head == nullptr) {
			head = temp;
			tail = temp;
			z = head;
			temp->prev = nullptr;
			ListSize++;
		}
		else {
			temp->prev = z;
			z = temp;
			tail->next = temp;
			tail = temp;
			ListSize++;
		}
	}
	
	template<typename T>
	void DoubleLinkedList<T>::InsertFront(T value) {
		Node* temp = new Node;
		temp->data = value;
		temp->next = nullptr;
		temp->prev = nullptr;

		if (tail != nullptr)
			z = head;

		if (head == nullptr) {
			head = temp;
			tail = temp;
			z = temp;
			temp->prev = nullptr;
			ListSize++;
		}
		else {
			temp->next = z;
			z = temp;
			head = temp;
			temp = temp->next;
			temp->prev = head;
			ListSize++;
		}
	}
	
	template<typename T>
	void DoubleLinkedList<T>::InsertAt(T value, int position) {
		using std::cout; using std::endl;

		if (position > ListSize) {
			cout << "Can't insert \"" << value << "\" at position \"" << position << "\"" << endl;
			return;
		}
		Node* temp = new Node;
		Node* NewNode = new Node;
		temp = head;
		
		for (int i = 0; i < position - 1; i++)
			temp = temp->next;

		//Setting NewNode->next && NewNode->prev
		NewNode->data = value;
		NewNode->prev = temp->prev;
		NewNode->next = temp;
		
		//Modifing neighbor Nodes to refer to placeHolder
		temp->prev = NewNode;
		temp = temp->prev; temp = temp->prev;
		temp->next = NewNode;
		
		ListSize++;
	}

	template<typename T>
	void DoubleLinkedList<T>::MultiInsert(T value, int position) {
		if (position <= ListSize && position > 1) {
			Node* temp = new Node;
			Node* NewNode = new Node;
			temp = head;

			for (int i = 0; i < position - 1; i++)
				temp = temp->next;

			//Setting NewNode->next && NewNode->prev
			NewNode->data = value;
			NewNode->prev = temp->prev;
			NewNode->next = temp;

			//Modifing neighbor Nodes to refer to placeHolder
			temp->prev = NewNode;
			temp = temp->prev; temp = temp->prev;
			temp->next = NewNode;

			ListSize++;
		
		} else if(position == 1) {
			Node* temp = new Node;
			temp->data = value;
			temp->next = nullptr;
			temp->prev = nullptr;

			if (head != nullptr)
				z = tail;

			if (head == nullptr) {
				head = temp;
				tail = temp;
				z = head;
				temp->prev = nullptr;
				ListSize++;
			}
			else {
				temp->prev = z;
				z = temp;
				tail->next = temp;
				tail = temp;
				ListSize++;
			}
		}
		else if(position == 0){
			Node* temp = new Node;
			temp->data = value;
			temp->next = nullptr;
			temp->prev = nullptr;

			if (tail != nullptr)
				z = head;

			if (head == nullptr) {
				head = temp;
				tail = temp;
				z = temp;
				temp->prev = nullptr;
				ListSize++;
			}
			else {
				temp->next = z;
				z = temp;
				head = temp;
				temp = temp->next;
				temp->prev = head;
				ListSize++;
			}
		}
	}
	
	template<typename T>
	void DoubleLinkedList<T>::DeleteNode(T value) {
		using std::cout; using std::endl;

		Node* temp = new Node;
		Node* replacement = new Node;
		temp = head; int k = 1;

		while (temp->data != value) {
			temp = temp->next;
			k++;

			if (k > ListSize) {
				cout << "Can't find \"" << value << "\"" << endl;
				return;
			}
		}
		if (ListSize != 0) {
			
			if (k == 1) {
				replacement = temp->next;
				head = replacement;
				replacement->prev = nullptr;
				ListSize--;
			}
			else if (k == ListSize) {
				replacement = temp->prev;
				tail = replacement;
				replacement->next = nullptr;
				ListSize--;
			}
			else {
				replacement = temp->prev;
				temp = temp->next;
				replacement->next = temp;
				temp->prev = replacement;
				ListSize--;
			}
		}
		else {
			cout << "List is Empty" << endl;
			return;
		}
	}
	template<typename T>
	void DoubleLinkedList<T>::DisplayLinear() {
		using std::cout; using std::endl;

		Node* temp = new Node;
		temp = head;

		while (temp != nullptr) {
			cout << temp->data << endl;
			temp = temp->next;
		}
	}
	
	template<typename T>
	void DoubleLinkedList<T>::DisplayReverse() {
		using std::cout; using std::endl;

		Node* temp = new Node;
		temp = tail;

		while (temp != nullptr) {
			cout << temp->data << endl;
			temp = temp->prev;
		}
	}
	
	template<typename T>
	DoubleLinkedList<T>::~DoubleLinkedList() {
		delete head, tail, z;
	}
}

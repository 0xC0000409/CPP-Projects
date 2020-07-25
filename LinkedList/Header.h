#ifndef HEADER_H_
#define HEADER_H_

namespace ListClass {
	template<typename T>
	class DoubleLinkedList {
	private:
		struct Node {
			T data;
			Node* next;
			Node* prev;
		};

		Node* head;
		Node* tail;
		Node* z;
		int ListSize;
	
	public:
		explicit DoubleLinkedList();
		void InsertBack(T Value);
		void InsertFront(T value);
		void InsertAt(T value, int position);
		void MultiInsert(T value, int position = 1);
		void DeleteNode(T value);
		void DisplayLinear();
		void DisplayReverse();
		~DoubleLinkedList();
	};
}

#endif
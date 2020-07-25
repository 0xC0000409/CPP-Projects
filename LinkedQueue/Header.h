#ifndef HEADER_H_
#define HEADER_H_

namespace Queue {
	template<typename T>
	class LinkedQueue {
	private:
		struct Node {
			T data;
			Node* next;
		};
		Node* head;
		Node* tail;
		int QueueSize;
		
		int size() { return QueueSize; }
		bool isEmpty() { if (size() == 0) return true; return false; }
	public:
		LinkedQueue();
		void Push(T value);
		void Pop();
		T Front();
		T Back();
		~LinkedQueue();
	};
}

#endif // !HEADER_H_


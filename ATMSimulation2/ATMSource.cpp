#include "Header.h" 
#include <cstdlib>

queue::queue(int qs) : qsize(qs) {
	front = rear = nullptr;
	Items = 0;
}

bool queue::isEmpty() const {
	if (Items == 0)
		return true;

	return false;
}

bool queue::isFull() const {
	if (Items > qsize)
		return true;

	return false;
}

int queue::queueCount() const {
	return Items;
}

bool queue::enqueue(const Item& item) {
	if (isFull())
		return false;

	Node* add = new Node;
	add->item = item;
	add->next = nullptr;
	Items++;

	if (front == nullptr)
		front = add;
	else
		rear->next = add;

	rear = add;
	return true;
}

bool queue::dequeue(Item& item) {
	if (isEmpty() || front == nullptr)
		return false;

	item = front->item;
	Items--;
	Node* temp = front;
	front = front->next;
	delete temp;

	if (Items == 0)
		rear = nullptr;

	return true;
}

void Customer::set(long when) {
	processtime = rand() % 3 + 1;
	arrive = when;
}
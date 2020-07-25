#ifndef HEADER_H_
#define HEADER_H_

class Customer {
private:
	long arrive;
	int processtime;
public:
	Customer() { arrive = processtime = 0; }
	void set(long when);
	long when() const { return arrive; }
	int ptime() const { return processtime; }
};

typedef Customer Item;

class queue {
private:
	struct Node {
		Item item;
		struct Node* next;
	};
	enum { Q_SIZE = 10 };
	Node* front;
	Node* rear;
	queue(const queue& q) : qsize(0) {};
	queue& operator = (const queue& q) { return *this; }
	int Items;
	const int qsize;
public:
	queue(int qs = Q_SIZE);
	bool isEmpty() const;
	bool isFull() const;
	int queueCount() const;
	bool enqueue(const Item& item);
	bool dequeue(Item& item);
	~queue() {};
};

#endif

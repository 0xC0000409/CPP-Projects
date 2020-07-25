#ifndef HEAPHEADER_H_
#define HEAPHEADER_H_
#include "Header.h"
#include <vector>

class BinaryHeap {
public:
	typedef LinkedGraph::Node Node;
private:
	std::vector<Node*> heap_arr;
	int last_cell;
	int num_of_elements;
	const size_t heap_size;
public:
	BinaryHeap(const size_t size);
	void insert_val(Node* val);
	Node* extract();
	void balance();
	void balanceAlt();
	void balance_top(int cell = 1);
	void balance_bottom(int index);
	void triverse() const;
	bool isEmpty() const { return num_of_elements == 0; };
	~BinaryHeap() {};
};

#endif // !HEAPHEADER_H_
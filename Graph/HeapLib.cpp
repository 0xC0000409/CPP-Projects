#include "HeapHeader.h"
#include <iostream>
using std::cout; using std::endl;

BinaryHeap::BinaryHeap(const size_t size) : last_cell(0), num_of_elements(0), heap_size(size + 1) {
	//heap_arr[0] is empty
	size_t HeapSize = size + 1;
	heap_arr.resize(HeapSize);
}

void BinaryHeap::insert_val(Node* val) {
	if (last_cell >= heap_size) {
		cout << "Heap is full" << endl;
		return;
	}
	else {
		//Leaving heap_arr[0] empty
		num_of_elements++;
		heap_arr[++last_cell] = val;
		balance_bottom(last_cell);
	}
}

LinkedGraph::Node* BinaryHeap::extract() {
	//heap_arr[0] is empty
	Node* Element = heap_arr[1];
	heap_arr[1] = heap_arr[last_cell];
	last_cell--;
	num_of_elements--;
	balance_top();

	return Element;
}

void BinaryHeap::balance_top(int cell) {
	int left = cell * 2;
	int right = left + 1;

	if (left > last_cell)
		return;

	//DEBUG!
	//cout << "heap_arr[cell]->" << cell << " " << heap_arr[cell]->distance << "| ";
	//cout << "heap_arr[left]->" << left << " " << heap_arr[left]->distance << "| ";
	//cout << "heap_arr[right]->" << right << " " << heap_arr[right]->distance << endl;

	if (heap_arr[cell]->distance > heap_arr[left]->distance && heap_arr[left]->distance < heap_arr[right]->distance) {
		std::swap(heap_arr[cell], heap_arr[left]);
		balance_top(left);
	}
	else if (heap_arr[cell]->distance > heap_arr[right]->distance&& heap_arr[left]->distance > heap_arr[right]->distance) {
		std::swap(heap_arr[cell], heap_arr[right]);
		balance_top(right);
	}
}

void BinaryHeap::balance_bottom(int index) {
	int left = index / 2;

	if (left < 1)
		return;
	if (heap_arr[index]->distance < heap_arr[left]->distance) {
		std::swap(heap_arr[index], heap_arr[left]);
		balance_bottom(left);
	}
}

void BinaryHeap::balance() {
	BinaryHeap temp(heap_size);
	for (int i = 1; i <= this->last_cell; i++)
		temp.insert_val(this->heap_arr[i]);
	
	for (int i = 1; i <= this->last_cell; i++)
		this->heap_arr[i] = temp.heap_arr[i];
}

void BinaryHeap::balanceAlt() {
	for (size_t i = last_cell + 1; i --> 1 ;)
		balance_bottom(i);
}

void BinaryHeap::triverse() const {
	for (int i = 1; i <= num_of_elements; i++)
		cout << heap_arr[i]->data << " " << heap_arr[i]->distance << endl;
}
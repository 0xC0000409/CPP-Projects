#include "Header.h"
#include <iostream>
using std::cout; using std::endl;

BinaryHeap::BinaryHeap(const int size) : last_cell(0), num_of_elements(0), heap_size(size) {
	//heap_arr[0] is empty
	heap_arr = new int[size + __int64(1)];
}

void BinaryHeap::insert_val(const int value) {
	if (last_cell >= heap_size) {
		cout << "Heap is full" << endl;
		return;
	}
	else {
		//Leaving heap_arr[0] empty
		num_of_elements++;
		heap_arr[++last_cell] = value;
		balance_bottom(last_cell);
	}
}

int BinaryHeap::extract() {
	//heap_arr[0] is empty
	int Element = heap_arr[1];
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

	if (heap_arr[left] < heap_arr[right]) {
		std::swap(heap_arr[cell], heap_arr[left]);
		balance_top(left);
	}
	else {
		std::swap(heap_arr[cell], heap_arr[right]);
		balance_top(right);
	}
}

void BinaryHeap::balance_bottom(int index) {
	if (index <= 0)
		return;

	int left = index / 2;

	if (heap_arr[index] < heap_arr[left]) {
		std::swap(heap_arr[index], heap_arr[left]);
	}
	balance_bottom(left);

}

void BinaryHeap::delete_val(const int value) {
	for (int i = 1; i <= last_cell; i++) {
		if (heap_arr[i] == value) {
			heap_arr[i] = heap_arr[last_cell];
			last_cell--;
			num_of_elements--;
			balance_bottom(i);
			return;
		}
	}
	cout << "Value was not found" << endl;
	return;
}

void BinaryHeap::triverse(int cell) const {
	if (cell > last_cell)
		return;
	else {
		for (int i = 1; i <= last_cell; i++)
			cout << heap_arr[i] << " ";
		/*
		cout << heap_arr[cell] << endl;
		triverse(cell * 2);
		triverse((cell * 2) + 1);
		*/
	}
}

int BinaryHeap::peek() const {
	if (num_of_elements == 0) {
		cout << "Heap is Empty!" << endl;
		return INT_MIN;
	}
	else
		return heap_arr[1];
}

void BinaryHeap::modify(const int value, const int idx) {
	heap_arr[idx] = value; 
	//int sw = depthReplace(idx, idx); 
	//std::swap(heap_arr[idx], heap_arr[sw]); 
	balance_bottom(idx);
}

int BinaryHeap::depthReplace(const int arg, const int prev) const {
	int left = arg * 2;
	int right = left + 1;

	if (left > last_cell)
		return prev;

	if (heap_arr[left] > heap_arr[right])
		return depthReplace(right, arg);
	else
		return depthReplace(left, arg);
}

BinaryHeap::~BinaryHeap() {
	delete[] heap_arr;
}
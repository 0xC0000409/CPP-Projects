#include <algorithm>
#include <cmath>
#include <iostream>
#include "Header.h"
using std::cout; using std::endl;

BinaryHeap::BinaryHeap(const int size) : last_cell(0), num_of_elements(0), heap_size(size) {
	heap_arr = new int[size];
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

void BinaryHeap::balance_top(int cell) {
	int left = cell * 2;
	int right = (cell * 2)  + 1;
	
	if (left > last_cell && right > last_cell) //May cause problems :)
		return;
	else {
		if (heap_arr[cell] >= heap_arr[left] && heap_arr[left] <= heap_arr[right]) {
			cout << "L[" << heap_arr[cell] << " Left: " << heap_arr[left] << " Right: " << heap_arr[right] << "]" << endl;
			std::swap(heap_arr[cell], heap_arr[left]);
			balance_top(left);
		}
		else if (heap_arr[cell] >= heap_arr[right] && heap_arr[right] <= heap_arr[left]) {
			cout << "L[" << heap_arr[cell] << " Left: " << heap_arr[left] << " Right: " << heap_arr[right] << "]" << endl;
			std::swap(heap_arr[cell], heap_arr[right]);
			balance_top(right);
		}
	}
}

void BinaryHeap::balance_bottom(int index) {
	if (index <= 1)
		return;

	int left = index / 2;

	if (heap_arr[index] <= heap_arr[left]) {
		int temp = heap_arr[index];
		heap_arr[index] = heap_arr[left];
		heap_arr[left] = temp;
	}
	balance_bottom(left);
}

BinaryHeap::~BinaryHeap() {
	delete[] heap_arr;
}

void SortAlgos::BubbleSort(int* Arr, size_t length) {
	for (int i = 0; i < length - 1; i++)
		for (int j = 0; j < length - i - 1; j++)
			if (Arr[j] > Arr[j + 1])
				std::swap(Arr[j], Arr[j + 1]);
}

void SortAlgos::BubbleSortRecur(int* Arr, size_t length) {
	static int max = 0;

	if (length == 0)
		return;
	else if (max == Arr[length - 1])
		BubbleSortRecur(Arr, length - 1);
	else {
		for (int i = 0; i < length - 1; i++) {
			if (Arr[i] >= Arr[i + 1]) {
				std::swap(Arr[i], Arr[i + 1]);
				max = std::max(max, Arr[i + 1]);
			}
		}
		BubbleSortRecur(Arr, length - 1);
	}
}

void SortAlgos::SelectionSort(int* Arr, size_t length) {
	for (int i = 0; i < length; i++) {
		int min = i;
		
		for (int j = i + 1; j < length; j++)
			if (Arr[j] < Arr[min])
				min = j;

		if (min != i)
			std::swap(Arr[i], Arr[min]);
	}
}

void SortAlgos::SelectionSortRecur(int* Arr, size_t length, size_t srted) {
	int min = INT_MAX;
	size_t z = 0;

	if (length == srted)
		return;
	
	for (size_t i = srted; i < length; i++) {
		min = std::min(min, Arr[i]);
			
		if (min == Arr[i])
			z = i;
	}
		
	std::swap(Arr[srted], Arr[z]);
	SelectionSortRecur(Arr, length, srted + 1);
}
//Good when we have constant flow of numbers
void SortAlgos::InsertionSort(int* Arr, size_t length) {
	for (int i = 1; i < length; i++) {
		int currentNumber = Arr[i];
		int j = i;
		while (Arr[j - 1] > currentNumber && j > 0) {
			Arr[j] = Arr[j - 1];
			j--;
		}
		Arr[j] = currentNumber;
	}
}
//Good when we have constant flow of numbers
void SortAlgos::InsertionSortRecur(int* Arr, size_t length, size_t srted) {
	if (length == srted + 1)
		return;

	size_t i = srted + 1;
	int currentNumber = Arr[srted + 1];
	while (Arr[i - 1] > currentNumber && i > 0) {
			std::swap(Arr[i - 1], Arr[i]);
			i--;
	}
	InsertionSortRecur(Arr, length, srted + 1);
}
/*
Great for distributing values && finding ranges
(doesn't work with duplicates)
*/
void SortAlgos::BucketSort(int* Arr, size_t length) {
	
}
//MergeSort helper function(some hidden bug is lurking around)
void SortAlgos::Merge(int* Arr, size_t left, size_t middle, size_t right) {
	size_t Lsize = middle - left, Rsize = right - middle;
	
	int* leftArr = new int[Lsize] {};
	int* rightArr = new int[Rsize] {};
		
	for (size_t k = 0, i = left; k < Lsize && i < middle; k++, i++)
		leftArr[k] = Arr[i];

	for (size_t k = 0, i = middle; k < Rsize && i <= right; k++, i++)
		rightArr[k] = Arr[i];

	size_t l = 0, r = 0, i = left;
	while (l < Lsize && r < Rsize) {
		if (leftArr[l] <= rightArr[r]) {
			Arr[i] = leftArr[l];
			l++; i++;
		}
		else {
			Arr[i] = rightArr[r];
			r++; i++;
		}
	}
	
	while (l < Lsize) {
		Arr[i] = leftArr[l];
		l++; i++;
	}

	while (r < Rsize) {
		Arr[i] = rightArr[r];
		r++; i++;
	}
	
	delete[] leftArr;
	delete[] rightArr;
}
//Stable sort && speed(log(n)) (duplicates the duplicate value)
void SortAlgos::MergeSort(int* Arr, size_t left, size_t right) {
	if (right - 1 > left) {
		size_t mid = (left + right) / 2;
		MergeSort(Arr, left, mid);
		MergeSort(Arr, mid, right);
		Merge(Arr, left, mid, right);
	}
	else
		return;
}
//Unstable sort && quickest sort
void SortAlgos::QuickSort(int* Arr, size_t begin, size_t length) {
	if (length <= begin + 1)
		return;
	
	int z = begin - 1;
	int pivot = Arr[length - 1];
	for (int i = begin; i < length; i++)
		if (Arr[i] <= pivot)
			std::swap(Arr[i], Arr[++z]);

	QuickSort(Arr, begin, z);
	QuickSort(Arr, z, length);
}

void SortAlgos::HeapSort(int* Arr, size_t length) {
	BinaryHeap bh(length + 1);
	
	for (int i = 0; i < length; i++)
		bh.insert_val(Arr[i]);
	
	for (int i = 0; i < length; i++)
		Arr[i] = bh.extract();
}
#ifndef HEADER_H_
#define HEADER_H_

class BinaryHeap {
private:
	int* heap_arr;
	int last_cell;
	int num_of_elements;
	const size_t heap_size;
	static const int default_size = 20;
public:
	BinaryHeap(const int size = default_size);
	void insert_val(const int value);
	int extract();
	void delete_val(const int value);
	void triverse(int cell = 1) const;
	void balance_top(int cell = 1);
	void balance_bottom(int index);
	~BinaryHeap();
};

namespace SortAlgos {
	void BubbleSort(int* Arr, size_t length);
	void BubbleSortRecur(int* Arr, size_t length);
	void SelectionSort(int* Arr, size_t length);
	void SelectionSortRecur(int* Arr, size_t length, size_t srted = 0);
	void InsertionSort(int* Arr, size_t length);
	void InsertionSortRecur(int* Arr, size_t length, size_t srted = 0);
	void BucketSort(int* Arr, size_t length);
	void Merge(int* Arr, size_t left, size_t middle, size_t right);
	void MergeSort(int* Arr, size_t left, size_t right);
	void QuickSort(int* Arr, size_t begin, size_t length);
	void HeapSort(int* Arr, size_t length);
}

#endif // !HEADER_H_


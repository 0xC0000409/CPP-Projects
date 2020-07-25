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
	int peek() const;
	void modify(const int value, const int idx);
	int depthReplace(const int arg, const int prev) const;
	~BinaryHeap();
};


#endif // !HEADER_H_
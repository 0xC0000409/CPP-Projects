#include "Header.h";
#include <algorithm>
#include <iostream>
using std::cout; using std::endl;

Segment::Segment(int* arr, const size_t s) {
	array = arr;
	arrSize = s;
	size = pow(ceil(log2(arrSize)), 2) * 2 - 1;
	segmentArr.reset(new int[size]{}); //create new array
	
	for (size_t i = 0; i < size; i++)
		segmentArr.get()[i] = USHRT_MAX;

	create(0, s - 1);
}

void Segment::create(const int start, const int end, const int pos) {
	if (start == end) {
		segmentArr.get()[pos] = array[start];
		return;
	}
	int mid = (start + end) / 2;
	create(start, mid, 2 * pos + 1);
	create(mid + 1, end, 2 * pos + 2);
	segmentArr.get()[pos] = std::min(segmentArr.get()[2 * pos + 1], segmentArr.get()[2 * pos + 2]);
}

int Segment::getMin(const int sRange, const int eRange, const int start, const int end, int pos) const {
	if (start >= sRange && end <= eRange) //total overlap([start, end] must be inside [sRange, eRange] for total overlap)
		return segmentArr.get()[pos];
	else if(sRange > end || eRange < start) //no overlap
		return USHRT_MAX;
	
	int mid = (start + end) / 2;
	
	return std::min(getMin(sRange, eRange, start, mid, 2 * pos + 1),
		getMin(sRange, eRange, mid + 1, end, 2 * pos + 2)); //partial overlap
}
#pragma once

#include <climits>
#include <memory>

class Segment {
private:
	std::unique_ptr<int> segmentArr = nullptr;
	int* array = nullptr;
	size_t size = 0;
	size_t arrSize = 0; //size of a input array
private:
	int getMin(const int sRange, const int eRange, const int start, const int end, int pos = 0) const;
public:
	Segment(int* arr, const size_t s);
	void create(const int start, const int end, const int pos = 0);
	inline int getMin(const int sRange, const int eRange) const { return getMin(sRange, eRange, 0, arrSize - 1); }
};
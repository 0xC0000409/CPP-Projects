//fix broken sort algorithms
#include <iostream>
#include "Header.h"
using namespace std;

int main() {
	int Arr[] = { 307, 169, 758, 21, 540, 577, 479, 88, 457, 169 ,725, 997, 387, 574, 39, 502, 642, 307, 59, 211, 540, 597, 280 };
	SortAlgos::InsertionSort(Arr, sizeof(Arr) / sizeof(Arr[0]));

	for (int i : Arr)
		cout << i << " ";
	
}

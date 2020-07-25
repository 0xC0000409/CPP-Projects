#include <iostream>
#include "Header.h"
using namespace std;

int main() {
	int house[] = { -1, 2, 4, 0, -2, -5, 0, 0, 0, -3, -5, -4, 2, 4 };
	Segment alpha(house, 14);
	//for (size_t i = 0; i < 14; i++) {
	//	for (size_t j = 0; j < 14; j++) {
	//		cout << "i-> " << i << " j->" << j;
	//		cout << " :" << alpha.getMin(i, j) << endl;
	//	}
	//	cout << endl;
	//}
	cout << alpha.getMin(1, 5) << endl;
}
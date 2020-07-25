#include <iostream>
using namespace std;

const int Arr_size = 100;
int Tree_Arr[Arr_size];

int last_cell = 0;

void insertVal(int value) {
	if (last_cell > Arr_size) {
		cout << "Tree is full" << endl;
		return;
	}
	else {
		last_cell++;
		Tree_Arr[last_cell] = value;
	}
}

void deleteVal(int value) {
	for (int i = 1; i <= last_cell; i++) {
		if (Tree_Arr[i] == value) {
			Tree_Arr[i] = Tree_Arr[last_cell];
			last_cell--;
			return;
		}
	}
	cout << "value wasn't found" << endl;
	return;
}

void triverse(int Tree_Arr[], int cell = 1) {
	if (cell > last_cell)
		return;
	else {
		cout << Tree_Arr[cell] << endl;
		triverse(Tree_Arr, cell * 2);
		triverse(Tree_Arr, (cell * 2) + 1);
	}
}

int main()
{
	insertVal(3); insertVal(5); insertVal(7); insertVal(11); insertVal(13); insertVal(17);
	deleteVal(3);

	triverse(Tree_Arr);
}

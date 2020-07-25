#include <iostream>
#include "Header.h"

namespace cQueue {
	template<typename T>
	CircularQueue<T>::CircularQueue(int s) : Size(s) {
		Arr = new T[Size]{};
		Head = Top = -1;
	}

	template<typename T>
	int CircularQueue<T>::isFull() {
		int status = 0;

		if (Top != Size - 1 && Arr[Top + 1] == NULL) {
			status = 1;
			return status;
		}
		else if (Top == Size - 1 && Arr[0] == NULL) {
			status = 2;
			return status;
		}
		else if (Top == Size - 1 && Arr[0] != NULL) {
			status = 3;
			return status;
		}
		else {
			status = 3;
			return status;
		}
		
	}

	template<typename T>
	void CircularQueue<T>::push_back(T value) {
		using std::cout; using std::endl;

		if (isFull() == 1) {
			Arr[++Top] = value;
			cout << "Pushed Arr[" << Top << "]" << "->" << Arr[Top] << endl;
		}
		else if (isFull() == 2) {
			Top = -1;
			Arr[++Top] = value;
			cout << "Pushed Arr[" << Top << "]" << "->" << Arr[Top] << endl;
		}
		else if (isFull() == 3) {
			cout << "Queue is Full" << endl;
			return;
		}
	}
	
	template<typename T>
	int CircularQueue<T>::isEmpty() {
		int status = 0;

		if (Head != Size - 1 && Arr[Head + 1] != NULL) {
			status = 1;
			return status;
		}
		else if (Head == Size - 1 && Arr[Top] != NULL) {
			status = 2;
			return status;
		}
		else if (Head != Size - 1 && Arr[Top] == NULL) {
			status = 3;
			return status;
		}
		else {
			status = 3;
			return status;
		}
	}

	template<typename T>
	void CircularQueue<T>::pop() {
		using std::cout; using std::endl;
		
		if (isEmpty() == 1) {
			cout << "Poped Arr[" << Head + 1 << "]" << "->" << Arr[Head + 1] << endl;
			Arr[++Head] = NULL;
		}
		else if (isEmpty() == 2) {
			Head = -1;
			cout << "Poped Arr[" << Head + 1 << "]" << "->" << Arr[Head + 1] << endl;
			Arr[++Head] = NULL;
		}
		else if (isEmpty() == 3) {
			cout << "Queue is empty" << endl;
			return;
		}
	}
}
//DoubleLinkedList 0.6(Empting entire list may not be working)
#include "Header.cpp"
using namespace ListClass;

int main() {
	DoubleLinkedList<double> *dll = new DoubleLinkedList<double>();

	dll->InsertFront(11.1);
	dll->InsertBack(3.2);
	dll->InsertFront(13.3);
	dll->InsertFront(17.4);
	dll->InsertBack(7.5);
	dll->InsertFront(23.6);
	dll->InsertBack(2.7);
	dll->InsertBack(5.8);

	dll->InsertAt(31.9, 4);

	dll->MultiInsert(21.3);
	dll->MultiInsert(1.23);
	dll->MultiInsert(13.31, 2);
	dll->InsertFront(69.6969);
	dll->MultiInsert(0.02, 0);
	dll->MultiInsert(0.01, 0);
	
	dll->DeleteNode(0.01);
	dll->DeleteNode(21.3);
	dll->DeleteNode(1.23);
	dll->DeleteNode(5.8);
	dll->DeleteNode(2.7);
	dll->DeleteNode(7.5);
	dll->DeleteNode(0.02);
	
	dll->DisplayLinear();

	delete dll;

	return 0;
}
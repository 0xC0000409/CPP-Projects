#include "Header.h"
#include <iostream>
#include <algorithm>

//AbsHashing
AbsHashing::AbsHashing(const int TableSize) {
	hTableSize = TableSize;
}

int AbsHashing::HashFunc(const std::string& str) const {
	int sum = 0;

	for (int i = 0; i < str.length(); i++)
		sum += (int)str[i];

	sum %= tableSize();

	return sum;
}
//End of AbsHashing

//DirectHashing
DirectHashing::DirectHashing(const int TableSize) : AbsHashing(TableSize) {
	HashArr = new Node[tableSize()];
}

void DirectHashing::insertVal(const std::string& str) {
	//using cout affects memory usage(leakage)
	int index = HashFunc(str);
	
	if (HashArr[index].hashStr == "\0") {
		HashArr[index].hashStr = str;
		std::cout << HashArr[index].hashStr << index << std::endl;
	}
	else {
		Node* forwardIter = &HashArr[index];
		
		while (forwardIter->next != nullptr)
			forwardIter = forwardIter->next;
		
		Node* newNode = new Node;
		newNode->hashStr = str;
		newNode->next = nullptr;

		forwardIter->next = newNode;

		std::cout << "Collision: " << forwardIter->hashStr << "[" << index << "]" << std::endl;
	}
	
}
//Needs testing
DirectHashing::~DirectHashing() {
	Node* Z = nullptr;
	
	for (int i = 0; i < tableSize(); i++) {
		Z = HashArr[i].next;
		while (Z != nullptr) {
			Node* temp = Z->next;
			delete Z;
			Z = temp;
		}
	}
	delete[] HashArr;
}

//LinearHashing
LinearHashing::LinearHashing(const int TableSize) : AbsHashing(TableSize) {
	HashArr = new std::string[TableSize] {};
	NumOfElements = 0;
}

void LinearHashing::insertVal(const std::string& str) {
	int index = HashFunc(str);

	std::cout << "Number of Elements: " << NumOfElements << ", Table size: " << tableSize() << std::endl;

	if (HashArr[index] == "\0") {
		HashArr[index] = str;
		NumOfElements++;
		std::cout << "Inserted(no collision): " << HashArr[index] << ", Index: " << index << std::endl;
	}
	else {
		if (tableSize() <= NumOfElements) {
			std::string* newHashArr = new std::string[tableSize() * 2]{};

			for (int i = 0; i < tableSize(); i++) {
				if (HashArr[i] != "\0") {
					int newindex = AbsHashing::HashFunc(HashArr[i]);

					while (newindex < tableSize() * 2 && newHashArr[newindex] != "\0") {
						newindex++;

						if (newindex >= tableSize() * 2) {
							newindex %= tableSize() * 2;
							continue;
						}
					}
					newHashArr[newindex] = HashArr[i];
					std::cout << "Inserted old str(Full table): " << newHashArr[newindex] << ", newIndex: " << newindex << std::endl;
				}
			}
			delete[] HashArr;
			HashArr = newHashArr;
			hTableSize = tableSize() * 2;
			std::cout << "Inserted new str(Full table): " << HashArr[index] << ", Index: " << index << std::endl;
		}
		
		while (HashArr[index] != "\0") {
			index++;

			if (index >= tableSize()) {
				index %= tableSize();
				continue;
			}
		}

		HashArr[index] = str;
		NumOfElements++;
		std::cout << "Inserted new str(Collision): " << HashArr[index] << ", Index: " << index << std::endl;
		
	}
}

LinearHashing::~LinearHashing() {
	delete[] HashArr;
}

void QuadraticHashing::insertVal(const std::string& str) {
	int index = HashFunc(str);
	int indexRes = index;

	std::cout << "------Number of Elements: " << NumOfElements << ", Table size: " << tableSize() << "-----" << std::endl;

	if (HashArr[index] == "\0") {
		HashArr[index] = str;
		NumOfElements++;
		std::cout << "Inserted new str(No Collision): " << HashArr[index] << ", Index: " << index << std::endl;
	}
	else {
		if (tableSize() <= NumOfElements) {
			std::string* newHashArr = new std::string[tableSize() * 2] {};

			for (int i = 0; i < tableSize(); i++) {
				int newindex = AbsHashing::HashFunc(HashArr[i]);
				int newindexRes = newindex;

				int k = 1;
				while (newHashArr[newindex] != "\0") {
					newindex = int(newindexRes + pow(k, 2));
					k++;
					//Some solution when table lacks 1 Element
					if (newindex >= (tableSize() * 2)) {
						newindex %= (tableSize() * 2);
						continue;
					}
				}
				newHashArr[newindex] = HashArr[i];
			}
			delete[] HashArr;
			HashArr = newHashArr;
			hTableSize *= 2;
			std::cout << "Full Table(Copied old HashArr into newHashArr)" << std::endl;
		}
		
		int k = 1;
		while (HashArr[index] != "\0") {
			index = int(indexRes + pow(k, 2));
			k++;
			
			if (index >= tableSize()) {
				//Some solution when table lacks 1 Element
				std::cout << "Pre: " << index << std::endl;
				indexRes = (index + indexRes) % tableSize();
				index %= tableSize();
				std::cout << "Post: " << index << std::endl;
				continue;
			}
		}
		HashArr[index] = str;
		NumOfElements++;
		std::cout << "Inserted new str(Collision): " << HashArr[index] << ", Index: " << index << std::endl;
	}

}

//if NumOfElements > tableSize() modulos!!!
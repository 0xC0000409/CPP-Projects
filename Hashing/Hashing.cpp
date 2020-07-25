/*

!) Trouble with modulation(QuadraticHashing)
1) cout causing memory leaks in DirectHashing but not in LinearHashing and QuadraticHashing. 
2) Implement DoubleHashing, Deletion of hashStr && test.

*/
#include <iostream>
#include "Header.h"
using namespace std;

int main() {
	
	QuadraticHashing Direct(5);
	
	Direct.insertVal("Random_text_1");
	Direct.insertVal("Zuka");
	Direct.insertVal("Gio");
	
	Direct.insertVal("Random_text_1");
	Direct.insertVal("Zuka");
	Direct.insertVal("Gio");

	Direct.insertVal("Random_text_1");
	Direct.insertVal("Zuka");
	Direct.insertVal("Gio");

	Direct.insertVal("Random_text_1");
	Direct.insertVal("Zuka");
	Direct.insertVal("Gio");
	

	return 0;
}
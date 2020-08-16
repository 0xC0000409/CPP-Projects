/*
## AVL [0.0.1] - 8/16/2020
### Added
- separate header with template "AVL" class
- shared_ptr for better memory management
- search() function: 
	search(value) -> searches for value and if found, returns true.
	search(value, true) -> searches and erases value and if successful returns true on completion.
### Changed
- memory management for nodes
- more clear member functions
- more clear output
### Removed
- procedural code that was filled with bugs and memory leaks
### Fixed
- memory leaks in erase() function
- minor bugs
*/
#include <iostream>
#include <iomanip>
#include "AVLtree.h"
using namespace std;

int main() {
	{
		cout << setw(10) << setfill('-') << "" << "AVL<string>" << setw(10) << setfill('-') << "" << endl;
		AVL<string> s;
		s.insert("pam");
		s.insert("null-io");
		s.insert("michael");
		s.insert("dwight");
		s.erase("michael");
		s.erase("dwight");
		s.search("null-io", true);
		s.search("pam");
		s.insert("jim");
		s.triverse();
		cout << setw(10) << setfill('-') << "" << "END" << setw(10) << setfill('-') << "" << endl;
		
		cout << setw(10) << setfill('-') << "" << "AVL<int>" << setw(10) << setfill('-') << "" << endl;
		AVL<int> a;
		a.insert(40);
		a.insert(30);
		a.insert(20);
		a.insert(35);
		a.insert(60);
		a.insert(55);
		a.insert(75);
		a.insert(80);
		a.insert(90);
		a.insert(77);
		a.insert(76);
		a.erase(40);
		a.erase(55);
		a.erase(90);
		a.erase(31);
		a.erase(35);
		a.search(60, true);
		a.search(40);
		a.triverse();
		cout << setw(10) << setfill('-') << "" << "END" << setw(10) << setfill('-') << "" << endl;
	}
}

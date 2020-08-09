/* 
## Trie [0.0.1] - 8/9/2020

### Added
- separate header with "Trie" class
- shared_ptr for better memory management
- erase() function

### Changed
- memory management for nodes
- more clear member functions
- more clear output

### Removed
- procedural code that was filled with bugs and memory leaks

### Fixed
- bug in erase(), when deleted substring of existing string in Trie would cause function to output success on erase
- bug in erase(), when non-existent would make function to output nothing
- memory leaks in insert() and erase() functions
- minor bugs

*/
#include <iostream>
#include <map>
#include <iomanip>
#include "Header.h"
using namespace std;

int main() {
	{
		Trie tr;
		string text = "Dwight";
		string text2 = "Dwayne";
		string text3 = "Michael";
		string text4 = "Jim";
		string text5 = "Jimothy";
		cout << setw(15) << setfill('-') << "insert" << setw(15) << setfill('-') << "" << endl;
		tr.insert(text);
		tr.insert(text2);
		tr.insert(text3);
		tr.insert(text4);
		tr.insert(text5);
		cout << setw(22) << setfill('-') << "search" << setw(15) << setfill('-') << "" << endl;
		cout << tr.search(text) << endl;
		cout << tr.search(text3) << endl;
		cout << tr.search(text5) << endl;
		cout << tr.search("dwig") << endl;
		cout << tr.search("Null-IO") << endl;
		cout << setw(22) << setfill('-') << "erase" << setw(15) << setfill('-') << "" << endl;
		tr.erase(text2);
		tr.erase(text3);
		tr.erase(text5);
		tr.erase("dwig");
		tr.erase("Null-IO");
		tr.erase(text2);
		cout << setw(22) << setfill('-') << "search(again)" << setw(15) << setfill('-') << "" << endl;
		cout << tr.search(text) << endl;
		cout << tr.search(text3) << endl;
		cout << tr.search(text4) << endl;
		cout << tr.search(text5) << endl;
		cout << tr.search("dwig") << endl;
		cout << tr.search("Null-IO") << endl;
	}
}
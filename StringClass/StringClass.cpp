#include <cstdlib>
#include <ctime>
#include "Header.h"
const int ArSize = 10;
const int MaxLen = 81;

int main(int argc, char** argv) {
	using std::cout;
	using std::cin;
	using std::endl;
	String name;

	cout << "Hi, what's your name?\n>> ";
	cin >> name;
	cout << name << ", please enter up to " << ArSize
		<< " short sayings <empty line to quit>:\n";
	String sayings[ArSize]; // array of objects
	char temp[MaxLen]; // temporary string storage
	int i;
	for (i = 0; i < ArSize; i++)
	{
		cout << i + 1 << ": ";
		cin.get(temp, MaxLen);
		while (cin && cin.get() != '\n')
			continue;
		if (!cin || temp[0] == '\0') // empty line?
			break; // i not incremented
		else
			sayings[i] = temp; // overloaded assignment
	}
	int total = i; // total # of lines read
	if (total > 0)
	{
		cout << "Here are your sayings:\n";
		for (i = 0; i < total; i++)
			cout << sayings[i][0] /*first character in char string*/ << ": " << sayings[i] << endl;
		String* shortest = &sayings[0];
		String* first = &sayings[0];
		for (i = 1; i < total; i++)
		{
			if (sayings[i].length() < shortest->length())
				shortest = &sayings[i];
			if (sayings[i] < *first)
				first = &sayings[i];
		}
		cout << "Shortest saying:\n" << *shortest << endl;;
		cout << "First alphabetically:\n" << *first << endl;

		srand(time(0));
		int favIndex = rand() % total;
		String* favourite = new String(sayings[favIndex]);
		cout << "My favourite saying is: " << *favourite << endl;
		delete favourite;
	}
	else
		cout << "Nothing to say :|" << endl;

	cout << "Bye :)" << endl;

	return 0;
}
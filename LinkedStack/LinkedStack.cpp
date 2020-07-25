//LinkedStack 0.1(Simple Stack, everything works fine)
#include "LinkedStackLib.cpp"
using namespace LinkedStack;

int main()
{
	using std::cout; using std::endl;

	Stack<char>* st = new Stack<char>();
	st->push('z'); st->push('u');
	st->push('k'); st->push('a');
	st->pop(); st->pop(); st->pop();

	cout << "Top of the Stack: " << st->peek() << endl;

	st->push('g'); st->push('i'); st->push('o');
	st->pop(); st->pop(); st->pop();

	cout << "Top of the Stack: " << st->peek() << endl;
}
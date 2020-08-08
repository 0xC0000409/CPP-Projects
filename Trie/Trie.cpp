/*
1) more testing
2) comment everything
*/ 
#include <iostream>
#include <map>
#include <iomanip>
#include "Header.h"
using namespace std;

struct TrieNode {
	map<char, TrieNode*> Trie;
	bool isWord = 0;
};

TrieNode* Root = nullptr;

void insert(string s, TrieNode* Node = Root) {
	int i = 0;
	TrieNode* placeHolder = Node;

	if (Root == nullptr) {
		TrieNode* newNode = new TrieNode;
		Root = newNode;
		placeHolder = newNode;
	}
	
	if (Root != nullptr) {
		while (i <= s.size()) {
			TrieNode* newNode = new TrieNode;

			if (i == s.size())
				placeHolder->isWord = true;

			if (placeHolder->Trie.empty()) {
				placeHolder->Trie.insert(pair<char, TrieNode*>(s[i], newNode));
				cout << "inserted " << s[i] << " size: " << placeHolder->Trie.size() << " isWord: " << placeHolder->isWord << endl;
				placeHolder = newNode;
				i++;
			}
			else {
				if (placeHolder->Trie.find(s[i]) == placeHolder->Trie.end()) {
					placeHolder->Trie.insert(pair<char, TrieNode*>(s[i], newNode));
					cout << "inserted " << s[i] << " size: " << placeHolder->Trie.size() << " isWord: " << placeHolder->isWord << endl;
					placeHolder = newNode;
					i++;
				}
				else {
					placeHolder = placeHolder->Trie.at(s[i]);
					i++;
				}
			}
		}
	}
}

bool search(string s, TrieNode* Node = Root) {
	int i = 0;
	TrieNode* placeHolder = Node;
	
	if (Root == nullptr) {
		cout << "Trie is empty" << endl;
		return false;
	}
	else {
		while (i <= s.size()) {
			if (placeHolder->Trie.find(s[i]) == placeHolder->Trie.end())
				return false;
			else if (placeHolder->Trie.find(s[i]) != placeHolder->Trie.end() && placeHolder->Trie.at(s[i])->isWord == true && i == s.size() - 1)
				return true;

			placeHolder = placeHolder->Trie.at(s[i]);
			i++;
		}
	}
}

void Proto_func(string s, TrieNode* Node = Root, int i = 0) {
	static bool prefixRemoved = false;

	if (i == s.size() + 1) {
		cout << i << endl;
		prefixRemoved = false;
		return;
	}
	else if (Node->Trie.find(s[i]) == Node->Trie.end()) {
		prefixRemoved = true;
		i = s.size() + 1;
	}
	else {
		Proto_func(s, Node->Trie.at(s[i]), i + 1);

		if (i == s.size() && Node->Trie.size() > 1 && Node->isWord) {
			Node->Trie.erase(s[i]);
			Node->isWord = false;
			prefixRemoved = true;
		}
		
		if (Node->Trie.size() > 1 && !prefixRemoved) {
			Node->Trie.erase(s[i]);
			prefixRemoved = true;
		}

		if (!prefixRemoved)
			Node->Trie.erase(s[i]);
	}
}

int main() {
	{
		Trie tr;
		string text = "Dwight";
		string text2 = "Dwayne";
		string text3 = "Michael";
		string text4 = "Jim";
		string text5 = "Jimothy";
		cout << setw(15) << setfill('-') << "insert" << setw(15) << setfill('-') << "" << endl;
		insert(text);
		insert(text2);
		insert(text3);
		insert(text4);
		insert(text5);
		cout << setw(22) << setfill('-') << "insert(class)" << setw(15) << setfill('-') << "" << endl;
		tr.insert(text);
		tr.insert(text2);
		tr.insert(text3);
		tr.insert(text4);
		tr.insert(text5);
		cout << setw(15) << setfill('-') << "search" << setw(15) << setfill('-') << "" << endl;
		cout << search(text) << endl;
		cout << search(text3) << endl;
		cout << search(text5) << endl;
		cout << search("dwig") << endl;
		cout << search("Null-IO") << endl;
		cout << setw(22) << setfill('-') << "search(class)" << setw(15) << setfill('-') << "" << endl;
		cout << search(text) << endl;
		cout << search(text3) << endl;
		cout << search(text5) << endl;
		cout << search("dwig") << endl;
		cout << search("Null-IO") << endl;
		cout << setw(15) << setfill('-') << "erase" << setw(15) << setfill('-') << "" << endl;
		Proto_func(text2);
		Proto_func(text3);
		Proto_func(text4);
		Proto_func("dwig");
		Proto_func("Null-IO");
		cout << setw(22) << setfill('-') << "erase(class)" << setw(15) << setfill('-') << "" << endl;
		tr.erase(text2);
		tr.erase(text3);
		tr.erase(text4);
		tr.erase("dwig");
		tr.erase("Null-IO");
		cout << setw(22) << setfill('-') << "search(again)" << setw(15) << setfill('-') << "" << endl;
		cout << search(text) << endl;
		cout << search(text3) << endl;
		cout << search(text5) << endl;
		cout << search("dwig") << endl;
		cout << search("Null-IO") << endl;
		cout << setw(30) << setfill('-') << "search(class)(again)" << setw(15) << setfill('-') << "" << endl;
		cout << search(text) << endl;
		cout << search(text3) << endl;
		cout << search(text5) << endl;
		cout << search("dwig") << endl;
		cout << search("Null-IO") << endl;
	}
}
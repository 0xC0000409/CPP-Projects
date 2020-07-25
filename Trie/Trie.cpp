/*
1) more testing
2) comment everything
*/ 
#include <iostream>
#include <map>
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
	string text = "dito";
	string text2 = "dimitri";
	string text3 = "dito-gvrito";
	string text4 = "zujka";
	insert(text);
	insert(text2);
	insert(text3);
	insert(text4);
	Proto_func("dito-gvrito2132645+654");
	Proto_func("zujka");
	Proto_func("dito");
	Proto_func("dimitri");
	Proto_func("dito-gvrito");
	Proto_func("zujka");

	cout << "-----------Search-------------" << endl;
	cout << search("dito-gvrito") << endl;
	cout << search("zujka") << endl;
	cout << search("dito") << endl;
	cout << search("dimitri") << endl;
	cout << search("dito-gvrito") << endl;
}


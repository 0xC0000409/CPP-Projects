#include "Header.h"
#include <iostream>

Trie::Trie() {
	root = std::shared_ptr<Node>(new Node);
}

void Trie::insert(const std::string& s, std::shared_ptr<Node>&& node) {
	size_t it = 0;
	std::shared_ptr<Node> placeHolder(node);
	
	while (it <= s.size()) {
		if (it == s.size())
			placeHolder->isWord = true;

		if (placeHolder->trieMap.empty()) {
			std::shared_ptr<Node> newNode(new Node);
			placeHolder->trieMap.insert(std::pair<char, std::shared_ptr<Node>>(s[it], newNode));
			std::cout << "Inserted \"" << s[it] << "\"" << " with trieMap->size: " << placeHolder->trieMap.size() << ", trieMap->isWord: " << placeHolder->isWord << std::endl;
			placeHolder = newNode;
			it++;
		}
		else {
			std::shared_ptr<Node> newNode(new Node);
			if (placeHolder->trieMap.find(s[it]) == placeHolder->trieMap.end()) {
				placeHolder->trieMap.insert(std::pair<char, std::shared_ptr<Node>>(s[it], newNode));
				std::cout << "Inserted \"" << s[it] << "\"" << " with trieMap->size: " << placeHolder->trieMap.size() << ", trieMap->isWord: " << placeHolder->isWord << std::endl;
				placeHolder = newNode;
				it++;
			}
			else {
				placeHolder = placeHolder->trieMap.at(s[it]);
				it++;
			}
		}
	}
}

bool Trie::search(const std::string& s, std::shared_ptr<Node>&& node) const {
	size_t i = 0;
	std::shared_ptr<Node> placeHolder(node);

	while (i <= s.size()) {
		if (placeHolder->trieMap.find(s[i]) == placeHolder->trieMap.end())
			return false;
		else if (placeHolder->trieMap.at(s[i])->isWord == true && i == s.size() - 1)
			return true;

		placeHolder = placeHolder->trieMap.at(s[i]);
		i++;
	}
}

void Trie::erase(const std::string& s, std::shared_ptr<Node>&& node, size_t it) {
	static bool prefixRemoved = false;

	if (it == s.size() + 1) {
		std::cout << "Word: \"" << s << "\" has been successfully erased" << std::endl;
		prefixRemoved = false;
	}
	else if (node->trieMap.find(s[it]) == node->trieMap.end()) {		
		prefixRemoved = true;
		if (it != s.size() + 1 || !node->isWord) {
			std::cout << "Word: \"" << s << "\" doesn't exist in Trie" << std::endl;
			return;
		}
	}
	else {
		erase(s, move(node->trieMap.at(s[it])), it + 1);

		if (it == s.size() && node->trieMap.size() > 1 && node->isWord) {
			node->trieMap.erase(s[it]);
			node->isWord = false;
			prefixRemoved = true;
		}
		else if (node->trieMap.size() > 1 && !prefixRemoved) {
			node->trieMap.erase(s[it]);
			prefixRemoved = true;
		}
		else if (!prefixRemoved)
			node->trieMap.erase(s[it]);
	}
}
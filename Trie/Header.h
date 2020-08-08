#pragma once

#include <map>
#include <string>
#include <memory>

class Trie {
private:
	struct Node {
		std::map<char, std::shared_ptr<Node>> trieMap;
		bool isWord = false;
	};
	std::shared_ptr<Node> root = nullptr;
private:
	Trie(const Trie&) = delete;
	Trie& operator = (const Trie&) = delete;
	void insert(const std::string& s, std::shared_ptr<Node>&& node);
	bool search(const std::string& s, std::shared_ptr<Node>&& node) const;
	void erase(const std::string& s, std::shared_ptr<Node>&& node, size_t it);
public:
	Trie();
	inline void insert(const std::string& s) { insert(s, std::move(root)); }
	inline bool search(const std::string& s) { return search(s, std::move(root)); }
	inline void erase(const std::string& s) { erase(s, std::move(root), 0); }
};
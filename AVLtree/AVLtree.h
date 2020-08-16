#pragma once
#include <climits>
#include <memory>

template<typename T>
class AVL {
private:
	class Node {
	public:
		T data = T();
		int height = -1;
		std::shared_ptr<Node> left = nullptr;
		std::shared_ptr<Node> right = nullptr;
		Node(const T data_ = T(), const int height_ = - 1, std::shared_ptr<Node>&& left_ = nullptr, std::shared_ptr<Node>&& right_ = nullptr) : data(data_), height(height_), left(left_), right(right_) {};
		Node(const Node& n) = delete;
		Node& operator = (const Node& n) = delete;
	};
	std::shared_ptr<Node> root = nullptr;
private:
	const int getHeight(std::shared_ptr<Node>& node);
	const int checkBalance(std::shared_ptr<Node>&& left, std::shared_ptr<Node>&& right);
	std::shared_ptr<Node> leftRotate(std::shared_ptr<Node>&& node);
	std::shared_ptr<Node> rightRotate(std::shared_ptr<Node>&& node);
	std::shared_ptr<Node> find(std::shared_ptr<Node>&& node) const;
	std::shared_ptr<Node> insert(T& value, std::shared_ptr<Node>& node);
	std::shared_ptr<Node> erase(T& value, std::shared_ptr<Node>& node);
	bool search(T& value, bool extract, std::shared_ptr<Node>&& node);
	void triverse(std::shared_ptr<Node>&& node);
	void balance(std::shared_ptr<Node>&& node);
public:
	AVL();
	inline std::shared_ptr<Node> insert(T value) { return this->insert(value, root); };
	inline void triverse() { triverse(std::move(root)); };
	inline std::shared_ptr<Node> erase(T value) { return this->erase(value, root); };
	inline bool search(T value, bool extract = false) { return this->search(value, extract, std::move(root)); };
};

#include "Implementation.h"
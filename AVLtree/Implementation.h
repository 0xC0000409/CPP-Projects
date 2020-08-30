#pragma once
#include "AVLtree.h"
#include <iostream>
#include <algorithm>

template<typename T>
AVL<T>::AVL() {
	root = std::shared_ptr<Node>(new Node);
}

template<typename T>
const int AVL<T>::getHeight(std::shared_ptr<AVL<T>::Node>& node) {
	if (node.get() == nullptr)
		return 0;

	return 1 + std::max((node.get()->left != nullptr ? node.get()->left->height : -1),
		(node.get()->right != nullptr ? node.get()->right->height : -1));
}

template<typename T>
const int AVL<T>::checkBalance(std::shared_ptr<Node>&& left, std::shared_ptr<Node>&& right) {
	if (left.get() == nullptr && right.get() == nullptr)
		return 0;
	else if (left.get() == nullptr)
		return -1 * (right.get()->height + 1);
	else if (right.get() == nullptr)
		return left.get()->height + 1;
	
	return left.get()->height - right.get()->height;
}

template<typename T>
std::shared_ptr<typename AVL<T>::Node> AVL<T>::leftRotate(std::shared_ptr<Node>&& node) {
	std::shared_ptr<Node> temp = node.get()->right;
	node.get()->right = node.get()->right->left;
	temp.get()->left = node;
	node.get()->height = this->getHeight(node);
	temp.get()->height = this->getHeight(temp);

	if (node.get()->data == root.get()->data)
		root = temp;

	return temp;
}

template<typename T>
std::shared_ptr<typename AVL<T>::Node> AVL<T>::rightRotate(std::shared_ptr<Node>&& node) {
	std::shared_ptr<Node> temp = node.get()->left;
	node.get()->left = node.get()->left->right;
	temp.get()->right = node;
	node.get()->height = this->getHeight(node);
	temp.get()->height = this->getHeight(temp);

	if (node.get()->data == root.get()->data)
		root = temp;

	return temp;
}

template<typename T>
void AVL<T>::balance(std::shared_ptr<Node>&& node) {
	int balance = checkBalance(std::move(node.get()->left), std::move(node.get()->right));

	if (balance > 1) {
		if (checkBalance(std::move(node.get()->left->left), std::move(node.get()->left->right)) > 0)
			node = rightRotate(std::move(node));
		else {
			node.get()->left = leftRotate(std::move(node.get()->left));
			node = rightRotate(std::move(node));
		}
	}
	else if (balance < -1) {
		if (checkBalance(std::move(node.get()->right->right), std::move(node.get()->right->left)) > 0)
			node = leftRotate(std::move(node));
		else {
			node.get()->right = rightRotate(std::move(node.get()->right));
			node = leftRotate(std::move(node));
		}
	}

	if (node.get()->left != nullptr && node.get()->right == nullptr)
		node.get()->left->height = getHeight(node.get()->left);
	else if (node.get()->right != nullptr && node.get()->left == nullptr)
		node.get()->right->height = getHeight(node.get()->right);

	node->height = getHeight(node);
}

template<typename T>
std::shared_ptr<typename AVL<T>::Node> AVL<T>::find(std::shared_ptr<Node>&& node) const {
	static std::shared_ptr<Node> temp = node;

	if (node.get()->right == nullptr)
		return temp;
	else {
		temp = node;
		return find(std::move(node.get()->right));
	}
}

template<typename T>
std::shared_ptr<typename AVL<T>::Node> AVL<T>::insert(T& value, std::shared_ptr<Node>& node) {
	if (node.get() == nullptr) {
		std::shared_ptr<Node> nNode(new Node(value));
		node = nNode;
	}
	else if (node.get()->data == T()) {
		root.get()->data = value;
		node = root;
	}
	else if (value < node.get()->data)
		node.get()->left = insert(value, node.get()->left);
	else if (value > node.get()->data)
		node.get()->right = insert(value, node.get()->right);

	return node;
}

template<typename T>
std::shared_ptr<typename AVL<T>::Node> AVL<T>::erase(T& value, std::shared_ptr<Node>& node) {
	if (node.get() == nullptr) {
		std::cout << "value: \"" << value << "\" couldn't be found" << std::endl;
		return node;
	}
	else if (value < node.get()->data)
		node.get()->left = erase(value, node.get()->left);
	else if (value > node.get()->data)
		node.get()->right = erase(value, node.get()->right);
	else if (node.get()->data == value) {
		if (node.get()->left != nullptr && node.get()->right != nullptr) {
			if (node.get()->left->right != nullptr) {
				std::shared_ptr<Node> temp = find(std::move(node.get()->left));
				node.get()->data = temp.get()->right->data;
				temp.get()->right = nullptr;
			}
			else if (node.get()->left->right == nullptr) {
				node.get()->data = node.get()->left->data;
				node.get()->left = node.get()->left->left;
			}
		}
		else if (node.get()->left != nullptr && node.get()->right == nullptr) {
			if (root.get()->data == value)
				root = node.get()->left;
			else
				node = node.get()->left;
		}
		else if (node.get()->right != nullptr && node.get()->left == nullptr) {
			if (root.get()->data == value)
				root = node.get()->right;
			else
				node = node.get()->right;
		}
		else if (node.get()->left == nullptr && node.get()->right == nullptr)
			node.reset();

		return node;
	}

	balance(std::move(node));

	return node;
}

template<typename T>
bool AVL<T>::search(T& value, bool extract, std::shared_ptr<Node>&& node) {
	if (node == nullptr) {
		std::cout << "value: \"" << value << "\" couldn't be found" << std::endl;
		return false;
	}
	else if (value < node.get()->data)
		return search(value, extract, std::move(node.get()->left));
	else if (value > node.get()->data)
		return search(value, extract, std::move(node.get()->right));
	else if (value == node.get()->data) {
		if (extract) {
			std::cout << "value: \"" << value << "\" has been found and removed" << std::endl;
			erase(value, root); //starting from root node, in case it needs to be rebalanced
		}
		else
			std::cout << "value: \"" << value << "\" has been found" << std::endl;

		return true;
	}
}

template<typename T>
void AVL<T>::triverse(std::shared_ptr<Node>&& node) {
	if (node == nullptr)
		return;
	else {
		std::cout << "data: \"" << node.get()->data << "\", height: " << node.get()->height << std::endl;
		triverse(std::move(node.get()->left));
		triverse(std::move(node.get()->right));
	}
}
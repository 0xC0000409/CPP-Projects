//Insert and Deletion works. Clean up and memory managment is required.
#include <iostream>
#include <queue>
using namespace std;

struct Node {
	int data = 0;
	Node* left = nullptr; Node* right = nullptr;
};

Node* Root = nullptr;

void insert(int value) {
	static queue<Node*> q;
	Node* nNode = new Node;

	if (Root == nullptr) {
		nNode->data = value;
		nNode->left = nullptr;
		nNode->right = nullptr;
		Root = nNode;
		q.push(Root);

		return;
	}
	else {
		while (!q.empty()) {
			if (q.front()->left == nullptr) {
				nNode->data = value;
				q.front()->left = nNode;
				q.push(nNode);

				return;
			}
			else if (q.front()->right == nullptr) {
				nNode->data = value;
				q.front()->right = nNode;
				q.push(nNode);

				return;
			}
			if (q.front()->left != nullptr && q.front()->right != nullptr)
				q.pop();
		}
	}
}

Node* find_deepest(Node* Root) {
	static queue<Node*> q;
	Node* deepest_node = new Node;

	if (Root != nullptr)
		q.push(Root);
	else
		return nullptr;

	while (!q.empty()) {
		deepest_node = q.front();
		if (q.front()->left != nullptr)
			q.push(q.front()->left);

		if (q.front()->right != nullptr)
			q.push(q.front()->right);

		q.pop();
	}
	
}

void remove_deepest(Node* Root) {
	static queue<Node*> q;
	
	if (Root != nullptr)
		q.push(Root);
	else {
		cout << "Error" << endl;
		return;
	}
	while (!q.empty()) {
		if (q.front()->left == find_deepest(Root)) {
			q.front()->left = nullptr;
			return;
		} else if (q.front()->right == find_deepest(Root)) {
			q.front()->right = nullptr;
			return;
		}
		if (q.front()->left != nullptr)
			q.push(q.front()->left);

		if (q.front()->right != nullptr)
			q.push(q.front()->right);

		q.pop();
	}
}

void remove_node(Node* Root, int target_value) {
	static queue<Node*> q;

	if (Root != nullptr)
		q.push(Root);
	else {
		cout << "Tree is empty" << endl;
		return;
	}
	while (!q.empty()) {
		if (q.front()->data == target_value) {
			q.front()->data = find_deepest(Root)->data;
			remove_deepest(Root);
			return;
		}
		else {
			if (q.front()->left != nullptr)
				q.push(q.front()->left);

			if (q.front()->right != nullptr)
				q.push(q.front()->right);

			q.pop();
		}
	}
}

void triverse(Node* Root) {
	if (Root == nullptr)
		return;
	else {
		cout << Root->data << endl;
		triverse(Root->left);
		triverse(Root->right);
	}
}

int main(int argc, char** argv) {
	insert(20);
	insert(100);
	insert(3);
	insert(50);
	insert(15);
	insert(250);
	insert(35);
	insert(69);

	remove_node(Root, 250);

	triverse(Root);
}

//Memory managment + template
#include <iostream>
using namespace std;

struct Node {
	int data = INT_MIN;
	Node* left = nullptr;
	Node* right = nullptr;
};

Node* FindVal(Node* root);

Node* Root = new Node;

Node* insertVal(int value, Node* currentNode = Root) {
	if (Root->data == INT_MIN)
		Root->data = value;

	if (currentNode == nullptr) {
		Node* newNode = new Node;
		newNode->data = value;
		currentNode = newNode;
	}
	else if (value <= currentNode->data)
		currentNode->left = insertVal(value, currentNode->left);
	else if (value >= currentNode->data)
		currentNode->right = insertVal(value, currentNode->right);

	return currentNode;
}

Node* deleteNode(int value, Node* root = Root) {
	if (root == nullptr) {
		cout << "Value: " << value << " couldn't be found" << endl;
		return nullptr;
	}

	if (value < root->data)
		root->left = deleteNode(value, root->left);
	else if (value > root->data)
		root->right = deleteNode(value, root->right);
	else if (root->data == value && root->left != nullptr && root->right != nullptr) {
		if (root->left->right != nullptr) {
			Node* temp = FindVal(root->left);
			root->data = temp->right->data;
			temp->right = nullptr;
		}
		else if(root->left->right == nullptr) {
			root->data = root->left->data;
			root->left = root->left->left;
		}
	}
	else if (root->data == value && root->left != nullptr && root->right == nullptr) {
		if (Root->data == value)
			Root = root->left;
		else
			root = root->left;
	} 
	else if (root->data == value && root->right != nullptr && root->left == nullptr) {
		if (Root->data == value)
			Root = root->right;
		else
			root = root->right;
	}
	else if (root->data == value && root->left == nullptr && root->right == nullptr) {
		if (Root->data == value) {
			Root = nullptr;
			delete Root;
		}
		else
			root = nullptr;
	}
	
	return root;
}

void triverse(Node* root = Root) {
	if (root == nullptr)
		return;
	else {
		cout << root->data << endl;
		triverse(root->left);
		triverse(root->right);
	}
}

Node* FindVal(Node* root) {
	static Node* tmp = root;

	if (root->right == nullptr)
		return tmp;
	else {
		tmp = root;
		return FindVal(root->right);
	}
}

int main() {
	insertVal(100);
	insertVal(80);
	insertVal(110);
	insertVal(90);
	insertVal(250);
	insertVal(70);
	insertVal(105);
	insertVal(101);
	insertVal(300);
	insertVal(50);
	insertVal(108);
	deleteNode(70);
	deleteNode(80);
	deleteNode(235);
	deleteNode(110);

	triverse(Root);
}
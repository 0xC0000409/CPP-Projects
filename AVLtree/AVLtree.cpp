//Memory Managment sucks balls + implement template && .h file
#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
	int data = INT_MIN;
	int Height = -1;
	Node* left = nullptr;
	Node* right = nullptr;
};

Node* Root = new Node;

int getHeight(Node* currentNode) {
	if (currentNode == nullptr)
		return 0;
	
	return 1 + max((currentNode->left != nullptr ? currentNode->left->Height : -1),
					(currentNode->right != nullptr ? currentNode->right->Height : -1));
}

int checkBalance(Node* nodeLeft, Node* nodeRight) {
	if (nodeLeft == nullptr && nodeRight == nullptr)
		return 0;
	else if (nodeLeft == nullptr)
		return -1 * (nodeRight->Height + 1);
	else if (nodeRight == nullptr)
		return nodeLeft->Height + 1;
	else
		return nodeLeft->Height - nodeRight->Height;
}

Node* LeftRotate(Node* currentNode) {
	Node* nNode = currentNode->right;
	currentNode->right = currentNode->right->left;
	nNode->left = currentNode;
	currentNode->Height = getHeight(currentNode);
	nNode->Height = getHeight(nNode);

	if (currentNode->data == Root->data)
		Root = nNode;

	return nNode;
}

Node* RightRotate(Node* currentNode) {
	Node* nNode = currentNode->left;
	currentNode->left = currentNode->left->right;
	nNode->right = currentNode;
	currentNode->Height = getHeight(currentNode);
	nNode->Height = getHeight(nNode);

	if (currentNode->data == Root->data)
		Root = nNode;

	return nNode;
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

Node* insert(int value, Node* currentNode = Root) {
	if (Root->data == INT_MIN) {
		Root->data = value;
		currentNode = Root;
	}

	if (currentNode == nullptr) {
		Node* newNode = new Node;
		newNode->data = value;
		currentNode = newNode;
	}
	else if (value < currentNode->data) {
		currentNode->left = insert(value, currentNode->left);
	}
	else if (value > currentNode->data) {
		currentNode->right = insert(value, currentNode->right);
	}
	
	int balance = checkBalance(currentNode->left, currentNode->right);
	
	if (balance > 1) {
		if (checkBalance(currentNode->left->left, currentNode->left->right) > 0)
			currentNode = RightRotate(currentNode);
		else {
			currentNode->left = LeftRotate(currentNode->left);
			currentNode = RightRotate(currentNode);
		}
	}
	else if (balance < -1) {
		if (checkBalance(currentNode->right->right, currentNode->right->left) > 0)
			currentNode = LeftRotate(currentNode);
		else {
			currentNode->right = RightRotate(currentNode->right);
			currentNode = LeftRotate(currentNode);
		}
	}
	
	if(currentNode->left != nullptr && currentNode->right == nullptr)
		currentNode->left->Height = getHeight(currentNode->left);
	if (currentNode->right != nullptr && currentNode->left == nullptr)
		currentNode->right->Height = getHeight(currentNode->right);
	
	currentNode->Height = getHeight(currentNode);

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
	else {
		if (root->data == value && root->left != nullptr && root->right != nullptr) {
			if (root->left->right != nullptr) {
				Node* temp = FindVal(root->left);
				root->data = temp->right->data;
				temp->right = nullptr;
			}
			else if (root->left->right == nullptr) {
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

	int balance = checkBalance(root->left, root->right);

	if (balance > 1) {
		if (checkBalance(root->left->left, root->left->right) > 0)
			root = RightRotate(root);
		else {
			root->left = LeftRotate(root->left);
			root = RightRotate(root);
			}
		}
		else if (balance < -1) {
			if (checkBalance(root->right->right, root->right->left) > 0)
				root = LeftRotate(root);
			else {
				root->right = RightRotate(root->right);
				root = LeftRotate(root);
			}
		}

	if (root->left != nullptr && root->right == nullptr)
		root->left->Height = getHeight(root->left);
	if (root->right != nullptr && root->left == nullptr)
		root->right->Height = getHeight(root->right);
		
	root->Height = getHeight(root);

	return root;
}

void triverse(Node* root = Root) {
	if (root == nullptr)
		return;
	else {
		cout << "Data: " << root->data << " Height: " << root->Height << endl;
		triverse(root->left);
		triverse(root->right);
	}
}

int main() {
	insert(40);
	insert(30);
	insert(20);
	insert(35);
	insert(60);
	insert(55);
	insert(75);
	insert(80);
	insert(90);

	deleteNode(90);
	deleteNode(55);
	deleteNode(40);
	deleteNode(6969);
	deleteNode(35);

	triverse();
}

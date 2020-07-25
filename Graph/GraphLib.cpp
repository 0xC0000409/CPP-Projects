#include <iostream>
#include <new>
#include <algorithm>
#include "Header.h"
#include "HeapHeader.h"
using std::cout; using std::endl;

LinkedGraph::LinkedGraph(const int vNum) : vertic_num(vNum) {
	try {
		Graph = new Node * [vNum] {};
		tails = new Node * [vNum] {};

		for (int i = 0; i < vNum; i++) {
			Node* newNode = new Node(nullptr, i, INT_MAX, INT_MAX);
			Graph[i] = newNode;
		}
		for (int i = 0; i < vNum; i++)
			tails[i] = Graph[i];
	}
	catch (std::bad_alloc & ba) {
		throw;
	}
}

void LinkedGraph::insertVertic(int vertic, int edge, int dist, bool intrcnnted) {
	if ((vertic >= vertic_num || vertic < 0) || (edge >= vertic_num || edge < 0))
		throw LinkedGraph::GraphExc("Vertic or edge is more than vertic number, Insertation Aborted.");

	//Creating new Vertic
	Node* newV = new Node(Graph[edge], edge, dist, -1, tails[vertic]);

	DsjnstObj ob(vertic, dist, edge);
	ObjVec.push_back(ob);

	tails[vertic]->next = newV;
	tails[vertic] = newV;

	if (intrcnnted) {
		Node* newV = new Node(Graph[vertic], vertic, dist, -1, tails[edge]);
		tails[edge]->next = newV;
		tails[edge] = newV;
	}
}

bool LinkedGraph::Gphvisited() {
	for (int i = 0; i < vertic_num; i++)
		if (Graph[i]->visited == false)
			return false;

	return true;
}

void LinkedGraph::reset() {
	for (int i = 0; i < vertic_num; i++) {
		Graph[i]->visited = false;
		Graph[i]->parent = -1;
		Graph[i]->distance = INT_MAX;
	}
}

void LinkedGraph::PathFinder(const int destination) {
	if (Graph[destination]->parent == -1) {
		cout << Graph[destination]->data;
		return;
	}
	else {
		PathFinder(Graph[destination]->parent);
		cout << "->" << destination;
	}
}

int LinkedGraph::parentFinder(const int Vert) const {
	if (parent[Vert] < 0)
		return Vert;
	else
		return parentFinder(parent[Vert]);
}

void LinkedGraph::Union(const int p1, const int p2) {
	if (parent[p1] < parent[p2]) {
		parent[p1] += parent[p2];
		parent[p2] = p1;
	}
	else {
		parent[p2] += parent[p1];
		parent[p1] = p2;
	}
}

void LinkedGraph::BFS(const int vertic) {
	if (vertic >= vertic_num || vertic < 0) {
		throw LinkedGraph::GraphExc("Vertic or edge is more than vertic number, Insertation Aborted.");
	}
	std::queue<Node*> q;
	q.push(Graph[vertic]);

	cout << "BFS:" << endl;
	while (!Gphvisited()) {
		Node* temp = nullptr;

		while (!q.empty()) {
			if (!Graph[q.front()->data]->visited) {
				cout << q.front()->data << endl;
				Graph[q.front()->data]->visited = true;
				temp = Graph[q.front()->data];
			}
			while (temp != nullptr) {
				if (!Graph[temp->data]->visited)
					q.push(temp);

				temp = temp->next;
			}
			q.pop();
		}
	}
	reset();
}

void LinkedGraph::DFS(const int vertic) {
	if (vertic >= vertic_num || vertic < 0) {
		throw LinkedGraph::GraphExc("Vertic or edge is more than vertic number, Insertation Aborted.");
	}
	std::stack<Node*> st;
	st.push(Graph[vertic]);

	cout << "DFS:" << endl;
	while (!Gphvisited()) {
		Node* temp = nullptr;
		bool reverse = false;

		while (!st.empty()) {
			if (!Graph[st.top()->data]->visited) {
				cout << st.top()->data << endl;
				Graph[st.top()->data]->visited = true;
				temp = Graph[st.top()->data];
			}
			st.pop();
			
			while (temp != nullptr) {
				if (!Graph[temp->data]->visited)
					st.push(temp);

				temp = temp->next;
			}
			reverse = false;
		}
	}
	reset();
}

void LinkedGraph::topologicalSort() {
	std::stack<Node*> stck;
	cout << "MAYBE WORKS!!!(test topologicalVisit)" << endl;
	for (int i = 0; i < vertic_num; i++)
		if (!Graph[i]->visited)
			topologicalVisit(Graph[i], stck);

	while (!stck.empty()) {
		cout << stck.top()->data << endl;
		stck.pop();
	}
}

void LinkedGraph::topologicalVisit(Node* vertic, std::stack<Node*>& stck, int parent) {
	if (vertic->next == nullptr)
		return;

	cout << vertic->data << " <- " << parent << endl;

	if (!Graph[vertic->next->data]->visited && vertic->next->data != parent)
		topologicalVisit(Graph[vertic->next->data], stck, vertic->data);
	else if (vertic->next->data == parent) {
		Node* temp = vertic;
		while (temp->next->data == parent || temp->data == parent) {
			if (temp->next->next == nullptr) {
				Graph[vertic->data]->visited = true;
				stck.push(vertic);
				return;
			}

			temp = temp->next;
		}

		topologicalVisit(Graph[temp->data], stck, vertic->data);
	}

	Graph[vertic->data]->visited = true;
	stck.push(vertic);
	cout << "Stack top: " << stck.top()->data << endl;
}

void LinkedGraph::SSSP_BFS(const int vertic, const int dest) {
	if ((vertic >= vertic_num || vertic < 0) || (dest >= vertic_num || dest < 0)) {
		throw LinkedGraph::GraphExc("Vertic or edge is more than vertic number, Insertation Aborted.");
	}
	std::queue<Node*> q;
	q.push(Graph[vertic]);

	cout << "SSSP with BFS:" << endl;
	while (!Gphvisited()) {
		Node* temp = nullptr;

		while (!q.empty()) {
			if (!Graph[q.front()->data]->visited) {
				Graph[q.front()->data]->visited = true;
				temp = Graph[q.front()->data];
			}

			while (temp != nullptr) {
				if (!Graph[temp->data]->visited) {
					Graph[temp->data]->parent = q.front()->data;
					q.push(temp);
				}
				temp = temp->next;
			}
			q.pop();
		}
	}
	PathFinder(dest);
	reset(); //sets parents to -1, visited to false & Distance to INT_MAX
}

void LinkedGraph::Dijkstra(const int vertic, const int dest) {
	if ((vertic >= vertic_num || vertic < 0) || (dest >= vertic_num || dest < 0))
		throw LinkedGraph::GraphExc("Vertic or edge is more than vertic number, Insertation Aborted.");
	else
		Graph[vertic]->distance = 0;

	BinaryHeap bh(vertic_num);
	for (int i = 0; i < vertic_num; i++)
		bh.insert_val(Graph[i]);

	cout << "Dijstra:" << endl;
	while (!bh.isEmpty()) {
		Node* currNode = bh.extract();
		int currHead = currNode->data;

		while (currNode != nullptr) {
			if (Graph[currHead]->distance + currNode->distance < Graph[currNode->data]->distance) {
				currNode->vertic->distance = currNode->distance + Graph[currHead]->distance;
				currNode->vertic->parent = currHead;
			}
			currNode = currNode->next;
		}
		bh.balanceAlt();
	}

	if (Graph[dest]->distance == INT_MAX)
		Graph[dest]->distance = 0;

	cout << "Shortest Path from " << vertic << " to " << dest << ":" << endl;
	cout << "Path: "; PathFinder(dest); cout << endl;
	cout << "Length: " << Graph[dest]->distance << endl;
	reset();
}

void LinkedGraph::Bellman_Ford(int vertic, int dest) {
	if ((vertic >= vertic_num || vertic < 0) || (dest >= vertic_num || dest < 0))
		throw LinkedGraph::GraphExc("Vertic or edge is more than vertic number, Insertation Aborted.");
	else
		Graph[vertic]->distance = 0;

	cout << "Bellman_Ford:" << endl;
	for (int j = 0; j < vertic_num - 1; j++) {
		for (int i = 0; i < vertic_num; i++) {
			Node* temp = Graph[i]; //Skips itself
			while (temp != nullptr) {
				if (Graph[i]->distance != INT_MAX && (Graph[i]->distance + temp->distance < Graph[temp->data]->distance)) {
					Graph[temp->data]->distance = Graph[i]->distance + temp->distance;
					Graph[temp->data]->parent = Graph[i]->data;
				}
				temp = temp->next;
			}
		}
	}
	for (int i = 0; i < vertic_num; i++) {
		Node* temp = Graph[i]; //Skips itself
		while (temp != nullptr) {
			if (Graph[i]->distance != INT_MAX && (Graph[i]->distance + temp->distance < Graph[temp->data]->distance))
				throw LinkedGraph::GraphExc("Negative Cycle Detected! SSSP Can't be found!");

			temp = temp->next;
		}
	}
	if (Graph[dest]->distance == INT_MAX)
		Graph[dest]->distance = 0;


	cout << "Shortest Path from " << vertic << " to " << dest << ":" << endl;
	cout << "Path: "; PathFinder(dest); cout << endl;
	cout << "Length: " << Graph[dest]->distance << endl;
	reset();
}

const int LinkedGraph::Kruskal() {
	int length = 0;
	std::sort(ObjVec.begin(), ObjVec.end()); //Priority Queue can be used also
	parent = new int[vertic_num]; //Creates DisJointSet(Array implementation, cause it's faster and easier)
	for (int i = 0; i < vertic_num; i++)
		parent[i] = -1;

	for (int i = 0; i < ObjVec.size(); i++) {
		DsjnstObj temp = ObjVec[i];
		int p1 = parentFinder(temp.Vertic1);
		int p2 = parentFinder(temp.Vertic2);

		if (p1 != p2) {
			Union(p1, p2);
			length += temp.Dst;
		}
	}
	cout << "Total Length: ";
	reset();
	return length;
}

const long long LinkedGraph::Prim(const int Src) {
	if (Src >= vertic_num || Src < 0)
		throw LinkedGraph::GraphExc("Invalid Source, Prim Aborted.");
	else
		Graph[Src]->distance = 0;

	long long length = 0;
	BinaryHeap bh(vertic_num);
	for(int i = 0; i < vertic_num; i++)
		bh.insert_val(Graph[i]);

	cout << "Prim:" << endl;
	int lst = -1;
	while (!bh.isEmpty()) {
		Node* crntNode = bh.extract();
		crntNode->visited = true;
		int crntHead = crntNode->data;

		while (crntNode != nullptr) {
			if (!Graph[crntNode->data]->visited)
				if (crntNode->distance < crntNode->vertic->distance)
					crntNode->vertic->distance = crntNode->distance;
				
			crntNode = crntNode->next;
		}
		bh.balanceAlt();
		Graph[crntHead]->visited = true;
		length += Graph[crntHead]->distance;
	}
	for (int i = 0; i < vertic_num; i++)
		cout << "Vertic[" << i << "] with distance: " << Graph[i]->distance << endl;

	cout << "Total Length: ";
	reset();
	return length;
}

void LinkedGraph::tempFunc(int vertic) {
	
}

LinkedGraph::~LinkedGraph() {
	for (int i = 0; i < vertic_num; i++) {
		Node* node_holder = Graph[i];

		while (node_holder != nullptr) {
			Node* temp = node_holder;
			node_holder = node_holder->next;
			delete temp;
		}
	}
	delete[] Graph; delete[] tails;
	delete[] parent; //Deletes DisJointSet
}
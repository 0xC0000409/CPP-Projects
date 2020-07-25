#ifndef HEADER_H_
#define HEADER_H_
#include <stack>
#include <queue>
#include <climits>
#include <vector>

class DsjnstObj {
public:
	int Vertic1;
	int Dst;
	int Vertic2;
public:
	DsjnstObj(int v1 = -1, int d = 0, int v2 = -1) : Vertic1(v1), Dst(d), Vertic2(v2) {};
	friend bool operator < (const DsjnstObj& dj1, const DsjnstObj& dj2) { return dj1.Dst < dj2.Dst; };
	~DsjnstObj() {};
};

class LinkedGraph {
public:
	class GraphExc {
	private:
		const char* ErrMsg;
	public:
		GraphExc(const char* msg) : ErrMsg(msg) {};
		const char* what() const { return ErrMsg; }
		~GraphExc() {};
	};
private:
	class Node {
	public:
		Node* prev;
		Node* vertic;
		Node* next;
		int parent;
		bool visited;
		int data;
		long long distance;
	public:
		Node(Node* vrtc, int d = INT_MAX, int dist = INT_MAX, int parent = -1, Node* p = nullptr, Node* n = nullptr, bool vstd = false)
			: prev(p), vertic(vrtc), next(n), parent(-1), visited(vstd), data(d), distance(dist) {};
	};
private:
	friend class BinaryHeap;
	const int vertic_num;
	Node** Graph = nullptr;
	Node** tails = nullptr;
	int* parent = nullptr;
	std::vector<DsjnstObj> ObjVec;
	bool Gphvisited();
	void reset();
	void PathFinder(const int destination);
	int parentFinder(const int Vert) const;
	void Union(const int p1, const int p2);
public:
	LinkedGraph(const int vNum = 1);
	void insertVertic(const int vertic, const int edge, int dist = INT_MAX, bool intrcnnted = true);
	void BFS(const int vertic);
	void DFS(const int vertic);
	void topologicalSort(); //Needs Testing
	void topologicalVisit(Node* vertic, std::stack<Node*>& stck, int parent = INT_MIN); //Helper of topologicalSort
	void SSSP_BFS(const int vertic, const int dest);
	void Dijkstra(const int vertic, const int dest);
	void Bellman_Ford(const int vertic, const int dest);
	const int Kruskal();
	const long long Prim(const int Src);
	const int size() const { return vertic_num; }
	void tempFunc(int vertic); //testing function
	~LinkedGraph();
};

/*
V = Vertices, E = Edges

BFS {
	Time complexity of BFS is O(V + E) and for Matrix O(pow(v, 2)) 
	it's  while (!Gphvisited()) is only entered once. 
	Space is also O(V + E). Can be applied to
	all types of Graphs. Usage(When target vertex is close to starting point)
}

DFS {
	Time complexity of BFS is O(V + E), while (!Gphvisited())
	is only entered once. Space is also O(V + E). Can be applied on
	all graphs EXCEPT disconnected ones. Usage(When target vertex is buried deeply)
}

Topological Sort {
	topologicalSort()'s time complexity is O(V), cause
	all vertices are triversed. topologicalVisit(Node*)'s
	time complexity is O(E). Together it is O(V + E).
	Space complexity is O(E). In topologicalSort()
	recurssion call occurs only handful of times.
}

SSSP_BFS {
	Shows general path towards from source vertic to
	destination and often not optimal. Can be used only
	on Unweighted-(Un)Directed graphs!. Time and Space complexities
	are O(V + E). Not suitable for everyday use.
}

Dijstra {
	Dijstra's time complexity in the worst case is O(V^2)
	- V square, because in the worst case, one vertic could be
	connected to all other vertices. Space complexity is O(V), cause
	we store vertices in the minHeap. Disjtra can't be used on
	Negative cycle. If a graph contains a "negative cycle
	" (i.e. a cycle whose edges sum to a negative value) that is reachable 
	from the source, then there is no cheapest path: any path that has a point on the 
	negative cycle can be made cheaper by one more walk around the negative cycle.
}

Bellman-Ford {
	This algorithm takes O(VE) time complexity and if using
	table for vertices, the space complexity will be O(V). Altough,
	slower, than Dijstra, it detects negative cycle and aborts
	SSSP. Why it runs for V-1 times? -> The worst type of Graph
	(skewed/blased, where from source to destination distance will be only
	max(like a linked list)), will take V-1 edges to reach destination. Even with the worst
	type of graph and when edges are processed in unfavourable way,
	in the worst case it will take V-1 iteration to find an answer.
	V-th iteration is used to find negative cycle. If the answer
	can be improved after V-1 iteration, than for sure we are
	having negative cycle. Can be used on any Type of Graph
}

Kurskal {
	Algorithm for finding Minimum spanning tree for only
	weighted and undirected Graph. Uses DisjointSet data
	structure for identifing if there's a cycle. DisjointSet
	can be implemented with graph and array, but array is preferable,
	because find() operation than takes O(1) time. Kurskal
	algorithm takes O(E*logE) time complexity and O(V + E)
	space complexity.
}

Prim {
	Algorithm for finding Minimum spanning tree for only
	weighted and undirected Graph. Uses MinHeap for
	picking the minimum weight of a vertex each iteration.
	It takes O(E*logV) time to execute and O(V) space complexity,
	because of a Heap used.
}

*/

#endif // !HEADER_H_
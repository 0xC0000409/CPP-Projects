#ifndef MATRIXHEADER_H_
#define MATRIXHEADER_H_
#include <climits>

class MatrixGraph {
private:
	class Cell{
	public:
		int distance;
		int parent;
	public:
		Cell(int d = USHRT_MAX, int p = -1) : distance(d), parent(p) {};
		~Cell() {};
	};
public:
	class MatrixExc {
	private:
		const char* ErrMsg;
	public:
		MatrixExc(const char* msg) : ErrMsg(msg) {};
		const char* what() const { return ErrMsg; }
		~MatrixExc() {};
	};
private:
	Cell** GraphMrtx = nullptr;
	const int vertic_num;
public:
	MatrixGraph(const int verticNum);
	void insertVertic(const int vertic, const int edge, const int dist, bool intrcnnted = true);
	void Floyed_Warshall();
	void PrintMtrx() const;
	void tempFunc();
	~MatrixGraph();
};

/*
Floyed-Warshall {
	Algorithm for finding All Pair Shortest Path(APSP), which
	takes O(V^3) time to execute and uses Adjacency Matrix and
	because of that it takes O(V^2) space complexity. The reason
	it always works is that, it identifies all the possibilities
	of finding distance between source and destination(#1-They are
	not reachable, 2#-They are directly connected, 3#-They are
	reachable via some other node). Can't work on negative cycle,
	because in algorithm same vertex(the outest for()) is never
	visited, hence it can never identifie negative cycle. Priority-
	-queue slows down Dijstra for APSP as priority-queue is not
	needed and Bellman-Ford's time complexity becomes O(V^2*E)
	which is slower than O(V^3) for Floyed-Warshall, hence it's
	the best option if we don't have begative cycle.
}

*/

#endif // !MATRIXHEADER_H_

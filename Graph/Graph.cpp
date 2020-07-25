//Graph 0.1 Alpha(A lot of testing is needed)
#include <iostream>
#include <iomanip>
#include <chrono>
#include "Header.h"
#include "MatrixHeader.h"
using namespace std;

int main() {
	try {
		//insertVertic(x, y)-> x connects to y and vice versa.
		//insertVertic(x, y, false)-> x only connects to y.
		auto t0 = chrono::high_resolution_clock::now();
		LinkedGraph z0(7);
		z0.insertVertic(0, 1);
		z0.insertVertic(0, 2);
		z0.insertVertic(1, 3);
		z0.insertVertic(1, 6);
		z0.insertVertic(2, 4);
		z0.insertVertic(3, 5);
		z0.insertVertic(4, 5);
		z0.insertVertic(5, 6);
		z0.BFS(0);
		cout << setw(16) << setfill('#') << "" << endl;
		z0.DFS(0);
		cout << setw(32) << setfill('-') << "" << endl;

		LinkedGraph z1(8);
		z1.insertVertic(0, 1);
		z1.insertVertic(1, 2);
		z1.insertVertic(2, 3);
		z1.insertVertic(4, 1);
		z1.insertVertic(4, 5);
		z1.insertVertic(5, 6);
		z1.insertVertic(6, 2);
		z1.insertVertic(6, 7);
		z1.topologicalSort();
		cout << setw(32) << setfill('-') << "" << endl;

		LinkedGraph z2(10);
		z2.insertVertic(0, 8);
		z2.insertVertic(1, 3);
		z2.insertVertic(1, 7);
		z2.insertVertic(1, 9);
		z2.insertVertic(2, 1);
		z2.insertVertic(2, 4);
		z2.insertVertic(3, 5);
		z2.insertVertic(4, 3);
		z2.insertVertic(5, 6);
		z2.insertVertic(6, 7);
		z2.insertVertic(8, 2);
		z2.insertVertic(8, 9);
		z2.SSSP_BFS(2, 6);
		cout << endl << setw(16) << setfill('#') << "" << endl;
		z2.SSSP_BFS(0, 7);
		cout << endl << setw(32) << setfill('-') << "" << endl;

		MatrixGraph mg(4);
		mg.insertVertic(0, 1, 8, false);
		mg.insertVertic(0, 3, 1, false);
		mg.insertVertic(1, 2, 1, false);
		mg.insertVertic(2, 0, 4, false);
		mg.insertVertic(3, 2, 9, false);
		mg.insertVertic(3, 1, 2, false);
		mg.Floyed_Warshall();
		cout << setw(32) << setfill('-') << "" << endl;

		LinkedGraph z3(5);
		z3.insertVertic(0, 2, 4, false);
		z3.insertVertic(0, 4, 2, false);
		z3.insertVertic(1, 3, 6, false);
		z3.insertVertic(1, 4, 6, false);
		z3.insertVertic(2, 1, 3, false);
		z3.insertVertic(3, 4, 2, false);
		z3.insertVertic(4, 3, 1, false);
		z3.insertVertic(4, 2, 1, false);

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				z3.Dijkstra(i, j);
				z3.Bellman_Ford(i, j); cout << endl;
			}
		}
		cout << setw(32) << setfill('-') << "" << endl;
		
		LinkedGraph z4(5);
		z4.insertVertic(0, 1, 10);
		z4.insertVertic(0, 2, 20);
		z4.insertVertic(1, 2, 30);
		z4.insertVertic(1, 3, 5);
		z4.insertVertic(2, 3, 15);
		z4.insertVertic(2, 4, 6);
		z4.insertVertic(3, 4, 8);

		for (int i = 0; i < 5; i++)
			for (int j = 0; j < 5; j++)
				z4.Dijkstra(i, j);

		cout << endl;
		for(int i = 0; i < z4.size(); i++)
			cout << z4.Prim(i) << endl;
		cout << setw(16) << setfill('-') << "" << endl;
		cout << z4.Kruskal() << endl;
		/*
		int n = 0, m = 0, a = 0, b = 0, c = 0;
		cin >> n >> m;
		LinkedGraph lg(n);
		for (int i = 0; i < m; i++) {
			cin >> a >> b >> c;
			lg.insertVertic(a - 1, b - 1, c);
		}
		for(int i = 0; i < n; i++)
			cout << lg.Prim(i) << endl;
		*/
		auto t1 = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();
		cout << endl << "Program took: " << duration << "ms to execute" << endl;
	}
	catch (LinkedGraph::GraphExc & vee) {
		cout << vee.what() << endl;
	}
	catch (MatrixGraph::MatrixExc & me) {
		cout << me.what() << endl;
	}
	catch (std::bad_alloc & ba) {
		cout << ba.what() << endl;
		exit(EXIT_FAILURE);
	}
	catch (...) {
		cout << "Unknown Error" << endl;
		exit(EXIT_FAILURE);
	}
}
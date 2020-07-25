#include "MatrixHeader.h"
#include <iostream>
#include <iomanip>
using std::cout; using std::endl;

MatrixGraph::MatrixGraph(const int verticNum) : vertic_num(verticNum) {
	GraphMrtx = new Cell* [vertic_num];
	for(int i = 0; i < vertic_num; i++)
		GraphMrtx[i] = new Cell[vertic_num]();
	
	for (int i = 0; i < vertic_num; i++)
		GraphMrtx[i][i].distance = 0;
	
}

void MatrixGraph::insertVertic(const int vertic, const int edge, const int dist, bool intrcnnted) {
	if ((vertic >= vertic_num || vertic < 0) || (edge >= vertic_num || edge < 0))
		throw MatrixGraph::MatrixExc("Vertic or edge is more than vertic number, Insertation Aborted.");
	else if (vertic == edge)
		throw MatrixGraph::MatrixExc("vertic can't be equal to edge, Insertation Aborted.");
	
	GraphMrtx[vertic][edge] = dist;
	
	if(intrcnnted)
		GraphMrtx[edge][vertic] = dist;
}

void MatrixGraph::Floyed_Warshall() {
	for (int i = 0; i < vertic_num; i++) 
		for (int k = 0; k < vertic_num; k++) 
			for (int j = 0; j < vertic_num; j++) 
				if (GraphMrtx[k][j].distance > GraphMrtx[k][i].distance + GraphMrtx[i][j].distance)
					GraphMrtx[k][j].distance = GraphMrtx[k][i].distance + GraphMrtx[i][j].distance;
	
	cout << "Floyed Warshall:" << endl;
	PrintMtrx();
}

void MatrixGraph::PrintMtrx() const {
	//if output matrix contains -1 that node can't be reached from anywhere
	for (int i = 0; i < vertic_num; i++) {
		for (int j = 0; j < vertic_num; j++) {
			if (GraphMrtx[i][j].distance == USHRT_MAX)
				cout << -1 << " ";
			else
				cout << GraphMrtx[i][j].distance << " ";
		}
		cout << endl;
	}
}

void MatrixGraph::tempFunc() {
	for (int i = 0; i < vertic_num; i++)
		for (int k = 0; k < vertic_num; k++)
			std::cout << "Graph[" << i << "][" << k << "]: " << GraphMrtx[i][k].distance << " " << GraphMrtx[i][k].parent << std::endl;
}

MatrixGraph::~MatrixGraph() {
	for (int i = 0; i < vertic_num; i++)
			delete[] GraphMrtx[i];
		
	delete[] GraphMrtx;
}
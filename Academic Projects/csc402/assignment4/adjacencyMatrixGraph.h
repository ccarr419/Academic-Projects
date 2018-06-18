/*
	Author:		Christian Carreras
	File:		adjacencyMatrixGraph.h
	Class:		CSC 402
	Date:		10/04/2015
*/

#ifndef ADJACENCYMATRIXGRAPH_H
#define ADJACENCYMATRIXGRAPH_H

#include <iostream>
#include "graph.h"
using namespace std;

class adjacencyMatrixGraph : public graph {
	private:
		int** matrix;
		int numNodes;
		
	public:
		adjacencyMatrixGraph(int n);
		~adjacencyMatrixGraph();
		
		int numberOfVertices() const;
		int numberOfEdges() const;
		bool existsEdge(int, int) const;
		void insertEdge(int, int);
		void eraseEdge(int, int);
		int degree(int) const;
		
		/* Not a directed graph
		int inDegree(int) const;
		int outDegree(int) const;
		*/
		
		void output(ostream&) const;
};

#endif

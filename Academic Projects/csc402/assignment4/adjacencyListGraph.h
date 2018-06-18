/*
	Author:		Christian Carreras
	File:		adjacencyListGraph.h
	Class:		CSC 402
	Date:		10/04/2015
*/

#ifndef ADJACENCYLISTGRAPH_H
#define ADJACENCYLISTGRAPH_H

#include <iostream>
#include "graph.h"
using namespace std;

class adjacencyListGraph : public graph {
	private:
		int** aList;
		int numNodes;
		
	public:
		adjacencyListGraph(int n);
		~adjacencyListGraph();
		
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

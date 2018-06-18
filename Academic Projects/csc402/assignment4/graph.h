/*
	Author:		Christian Carreras
	File:		graph.h
	Class:		CSC 402
	Date:		10/04/2015
*/

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include "edge.h"
using namespace std;

class graph {
	public:
		// ADT methods
		virtual ~graph() {}
		virtual int numberOfVertices() const = 0;
		virtual int numberOfEdges() const = 0;
		virtual bool existsEdge(int, int) const = 0;
		virtual void insertEdge(int, int) = 0;
		virtual void eraseEdge(int, int) = 0;
		
		virtual int degree(int) const = 0;
		
		/* Not needed for now, not a directed or weighted graph
		virtual int inDegree(int) const = 0;
		virtual int outDegree(int) const = 0;
		virtual bool directed() const = 0;
		virtual bool weighted() const = 0;
		*/
		
		virtual void output(std::ostream&) const = 0;
};

#endif

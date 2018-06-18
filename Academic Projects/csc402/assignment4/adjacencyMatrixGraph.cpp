/*
	Author:		Christian Carreras
	File:		adjacencyMatrixGraph.cpp
	Class:		CSC 402
	Date:		10/04/2015
*/

#include <iostream>
#include "adjacencyMatrixGraph.h"
using namespace std;

adjacencyMatrixGraph::adjacencyMatrixGraph(int n)
{
	numNodes = n;
	matrix = new int*[numNodes];
	for(int i = 0; i < numNodes; i++)
		matrix[i] = new int[numNodes];
	for(int i = 0; i < numNodes; i++)
		for(int j = 0; j < numNodes; j++)
			matrix[i][j] = 0;
}
adjacencyMatrixGraph::~adjacencyMatrixGraph()
{	delete [] matrix; }
		
int adjacencyMatrixGraph::numberOfVertices() const
{
	int numVertices = 0;
	for(int i = 0; i < numNodes; i++)
	{
		for(int j = 0; j < numNodes; j++)
		{
			if(matrix[i][j] == 1)
			{
				numVertices++;
				break;
			}
		}
	}
	return numVertices;
}

int adjacencyMatrixGraph::numberOfEdges() const
{
	int numEdges = 0;
	for(int i = 0; i < numNodes; i++)
		for(int j = 0; j < numNodes; j++)
			if(matrix[i][j] == 1)
				numEdges++;
	return numEdges;
}

bool adjacencyMatrixGraph::existsEdge(int from, int to) const
{	return (matrix[from][to] || matrix[to][from]); }

void adjacencyMatrixGraph::insertEdge(int f, int t)
{	
	matrix[f][t] = 1;
	matrix[t][f] = 1;
}

void adjacencyMatrixGraph::eraseEdge(int f, int t)
{
	matrix[f][t] = 0;
	matrix[t][f] = 0;
}


int adjacencyMatrixGraph::degree(int from) const
{
	int degree = 0;
	for(int i = 0; i < numNodes; i++)
		if(matrix[from][i] == 1)
			degree++;
	return degree;
}

/* Not a directed graph
int adjacencyMatrixGraph::inDegree(int) const
{

}

int adjacencyMatrixGraph::outDegree(int) const
{

}
*/

void adjacencyMatrixGraph::output(ostream& out) const
{
	for(int i = 0; i < numNodes; i++)
	{
		for(int j = 0; j < numNodes; j++)
			out << matrix[i][j] << " "; 
		out << "\n";
	}
}

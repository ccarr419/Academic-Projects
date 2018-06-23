/*
	Author:		Christian Carreras
	File:		adjacencyListGraph.cpp
	Class:		CSC 402
	Date:		10/04/2015
*/

#include <iostream>
#include "adjacencyListGraph.h"
using namespace std;

adjacencyListGraph::adjacencyListGraph(int n)
{
	numNodes = n;
	aList = new int*[numNodes];
	for(int i = 0; i < numNodes; i++)
		aList[i] = new int[numNodes];
	for(int i = 0; i < numNodes; i++)
		for(int j = 0; j < numNodes; j++)
			aList[i][j] = -1;
}
adjacencyListGraph::~adjacencyListGraph()
{	delete [] aList; }
		
int adjacencyListGraph::numberOfVertices() const
{
	int numVertices = 0;
	for(int i = 0; i < numNodes; i++)
	{
		for(int j = 0; j < numNodes; j++)
		{
			if(aList[i][j] != -1)
			{
				numVertices++;
				break;
			}
		}
	}
	return numVertices;
}

int adjacencyListGraph::numberOfEdges() const
{
	int numEdges = 0;
	for(int i = 0; i < numNodes; i++)
		for(int j = 0; j < numNodes; j++)
			if(aList[i][j] != -1)
				numEdges++;
	return numEdges;
}

bool adjacencyListGraph::existsEdge(int from, int to) const
{	return (aList[from][to] != -1 && aList[to][from] != -1); }

void adjacencyListGraph::insertEdge(int f, int t)
{	
	aList[f][t] = t;
	aList[t][f] = f;
}

void adjacencyListGraph::eraseEdge(int f, int t)
{
	aList[f][t] = -1;
	aList[t][f] = -1;
}


int adjacencyListGraph::degree(int from) const
{
	int degree = 0;
	for(int i = 0; i < numNodes; i++)
		if(aList[from][i] != -1)
			degree++;
	return degree;
}

/* Not a directed graph
int adjacencyListGraph::inDegree(int) const
{

}

int adjacencyListGraph::outDegree(int) const
{

}
*/

void adjacencyListGraph::output(ostream& out) const
{
	for(int i = 0; i < numNodes; i++)
	{
		out << "[" << i << "] = ( ";
		for(int j = 0; j < numNodes; j++)
		{
			if(aList[i][j] != -1)
				out << aList[i][j] << " ";
		}
		out << ")\n";
	}
}

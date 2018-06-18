/*
	Author:		Christian Carreras
	File:		adjacencyListGraph.h
	Class:		CSC 402
	Date:		10/11/2015
*/

#include <iostream>
#include "graph.h"
using namespace std;

class adjacencyListGraph : public graph {
	private:
		int** aList;
		int numNodes;
		
		vector<int> adjacent(int) const;
		bool find(vector<int>, int) const;
		void BFSHelper(queue<int>, vector<int>&) const;
		
	public:
		adjacencyListGraph(int n);
		~adjacencyListGraph();
		
		int numberOfVertices() const;
		int numberOfEdges() const;
		bool existsEdge(int, int) const;
		void insertEdge(int, int);
		void eraseEdge(int, int);
		int degree(int) const;
		
		void BFS(int, vector<int>&) const;
		void DFS(int, vector<int>&) const;
		
		/* Not a directed graph
		int inDegree(int) const;
		int outDegree(int) const;
		*/
		
		void output(ostream&) const;
};

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

void adjacencyListGraph::BFS(int v, vector<int>& visited_list) const
{
	queue<int> q;
	q.push(v);
	visited_list.push_back(v);
	BFSHelper(q, visited_list);
}

void adjacencyListGraph::BFSHelper(queue<int> q, vector<int>& visited_list) const
{
	if(q.empty())
		return;
	vector<int> adjacent_vertices = adjacent(q.front());
	for(int i = 0; i < adjacent_vertices.size(); i++)
	{
		if(!find(visited_list, adjacent_vertices.at(i)))
		{	
			visited_list.push_back(adjacent_vertices.at(i));
			q.push(adjacent_vertices.at(i));
		}
	}
	q.pop();
	BFSHelper(q, visited_list);
}

void adjacencyListGraph::DFS(int v, vector<int>& visited_list) const
{
	visited_list.push_back(v);
	vector<int> adjacent_vertices = adjacent(v);
	for(int i = 0; i < adjacent_vertices.size(); i++)
	{
		int w = adjacent_vertices.at(i);
		if(find(visited_list, w))
			continue;
		else
			DFS(w, visited_list);
	}
}

vector<int> adjacencyListGraph::adjacent(int start) const
{
	vector<int> adjacent_list;
	for(int i = 0; i < numNodes; i++)
		if(aList[start][i] != -1)
			adjacent_list.push_back(i);
	return adjacent_list;
}

bool adjacencyListGraph::find(vector<int> list, int v) const
{
	for(int i = 0; i < list.size(); i++)
		if(list.at(i) == v)
			return true;
	return false;
}

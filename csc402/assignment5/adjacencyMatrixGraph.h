/*
	Author:		Christian Carreras
	File:		adjacencyMatrixGraph.h
	Class:		CSC 402
	Date:		10/11/2015
*/

#include <iostream>
#include "graph.h"
using namespace std;

class adjacencyMatrixGraph : public graph {
	private:
		int** matrix;
		int numNodes;
		
		vector<int> adjacent(int) const;
		bool find(vector<int>, int) const;
		void BFSHelper(queue<int>, vector<int>&) const;
		
	public:
		adjacencyMatrixGraph(int n);
		~adjacencyMatrixGraph();
		
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

void adjacencyMatrixGraph::BFS(int v, vector<int>& visited_list) const
{	
	queue<int> q;
	q.push(v);
	visited_list.push_back(v);
	BFSHelper(q, visited_list);
}

void adjacencyMatrixGraph::BFSHelper(queue<int> q, vector<int>& visited_list) const
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

void adjacencyMatrixGraph::DFS(int v, vector<int>& visited_list) const
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

vector<int> adjacencyMatrixGraph::adjacent(int start) const
{
	vector<int> adjacent_list;
	for(int i = 0; i < numNodes; i++)
		if(matrix[start][i] == 1)
			adjacent_list.push_back(i);
	return adjacent_list;
}

bool adjacencyMatrixGraph::find(vector<int> list, int v) const
{
	for(int i = 0; i < list.size(); i++)
		if(list.at(i) == v)
			return true;
	return false;
}

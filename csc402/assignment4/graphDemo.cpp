/*
	Author:		Christian Carreras
	File:		graphDemo.cpp
	Class:		CSC 402
	Date:		10/04/2015
*/

#include <iostream>
#include "adjacencyMatrixGraph.h"
#include "adjacencyListGraph.h"

using namespace std;

int main()
{
	graph *myGraph1, *myGraph2;
	myGraph1 = new adjacencyMatrixGraph(5);
	myGraph2 = new adjacencyListGraph(5);
	
	cout << "\nADJACENCY MATRIX GRAPH\n\n";
	
	//insertEdge check
	cout << "Insert edges into matrix graph: \n";
	myGraph1->insertEdge(1, 3);
	myGraph1->insertEdge(0, 4);
	myGraph1->insertEdge(0, 2);
	myGraph1->insertEdge(2, 4);
	myGraph1->output(cout);
	cout << endl;
	
	//degree check
	for(int i = 0; i < 5; i++)
		cout << "Vertex " << i << " has a degree of " << myGraph1->degree(i) << endl;
	cout << endl;
	
	//numberOfVertices and numberOfEdges check
	cout << "There are now " << myGraph1->numberOfVertices() << " vertices in the graph\n";
	cout << "The graph has a total of " << myGraph1->numberOfEdges() << " edges\n\n";
	
	//existsEdge check
	cout << "Does there exist an edge between 1 and 3?\n";
	if(myGraph1->existsEdge(1, 3))
		cout << "Yes\n";
	cout << "Does there exist an edge between 0 and 4?\n";
	if(myGraph1->existsEdge(0, 4))
		cout << "Yes\n";
		
	cout << "Does there exist an edge between 2 and 4?\n";
	if(myGraph1->existsEdge(2, 4))
		cout << "Yes\n";
	
	cout << "Does there exist an edge between 0 and 3?\n";
	if(myGraph1->existsEdge(0, 3))
		cout << "Yes\n\n";
	else
		cout << "No\n\n";		
	
	//eraseEdge check
	cout << "Remove the edges previously inserted: \n";
	myGraph1->eraseEdge(1, 3);
	myGraph1->eraseEdge(0, 4);
	myGraph1->eraseEdge(0, 2);
	myGraph1->eraseEdge(2, 4);
	myGraph1->output(cout);
	cout << endl;
	
	//degree check
	for(int i = 0; i < 5; i++)
		cout << "Vertex " << i << " has a degree of " << myGraph1->degree(i) << endl;
	cout << endl;
	
	//numberOfVertices and numberOfEdges check
	cout << "There are now " << myGraph1->numberOfVertices() << " vertices in the graph\n";
	cout << "The graph has a total of " << myGraph1->numberOfEdges() << " edges\n\n";
	
	cout << "ADJACENCY LIST GRAPH\n\n";
	
	//insertEdge check
	cout << "Insert edges into matrix graph: \n";
	myGraph2->insertEdge(1, 3);
	myGraph2->insertEdge(0, 4);
	myGraph2->insertEdge(0, 2);
	myGraph2->insertEdge(2, 4);
	myGraph2->output(cout);
	cout << endl;
	
	//degree check
	for(int i = 0; i < 5; i++)
		cout << "Vertex " << i << " has a degree of " << myGraph2->degree(i) << endl;
	cout << endl;
	
	//numberOfVertices and numberOfEdges check
	cout << "There are now " << myGraph2->numberOfVertices() << " vertices in the graph\n";
	cout << "The graph has a total of " << myGraph2->numberOfEdges() << " edges\n\n";
	
	//existsEdge check
	cout << "Does there exist an edge between 1 and 3?\n";
	if(myGraph2->existsEdge(1, 3))
		cout << "Yes\n";
	cout << "Does there exist an edge between 0 and 4?\n";
	if(myGraph2->existsEdge(0, 4))
		cout << "Yes\n";
		
	cout << "Does there exist an edge between 2 and 4?\n";
	if(myGraph2->existsEdge(2, 4))
		cout << "Yes\n";
	
	cout << "Does there exist an edge between 0 and 3?\n";
	if(myGraph2->existsEdge(0, 3))
		cout << "Yes\n\n";
	else
		cout << "No\n\n";		
	
	//eraseEdge check
	cout << "Remove the edges previously inserted: \n";
	myGraph2->eraseEdge(1, 3);
	myGraph2->eraseEdge(0, 4);
	myGraph2->eraseEdge(0, 2);
	myGraph2->eraseEdge(2, 4);
	myGraph2->output(cout);
	cout << endl;
	
	//degree check
	for(int i = 0; i < 5; i++)
		cout << "Vertex " << i << " has a degree of " << myGraph2->degree(i) << endl;
	cout << endl;
	
	//numberOfVertices and numberOfEdges check
	cout << "There are now " << myGraph2->numberOfVertices() << " vertices in the graph\n";
	cout << "The graph has a total of " << myGraph2->numberOfEdges() << " edges\n\n";
	
	cout << "TEST COMPLETE\n\n";
	
	return 0;
}

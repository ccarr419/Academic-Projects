/*
	Author:		Christian Carreras
	File:		graphDemo.cpp
	Class:		CSC 402
	Date:		10/11/2015
*/

#include <iostream>
#include <vector>
#include "adjacencyMatrixGraph.h"
#include "adjacencyListGraph.h"

using namespace std;

int main()
{
	graph *myGraph1, *myGraph2;
	vector<int> visited_list1, visited_list2;
	myGraph1 = new adjacencyMatrixGraph(9);
	myGraph2 = new adjacencyListGraph(11);
	
	cout << "\nADJACENCY MATRIX\n";
	myGraph1->insertEdge(0, 1);
	myGraph1->insertEdge(0, 3);
	myGraph1->insertEdge(1, 2);
	myGraph1->insertEdge(1, 4);
	myGraph1->insertEdge(1, 5);
	myGraph1->insertEdge(2, 4);
	myGraph1->insertEdge(3, 5);
	myGraph1->insertEdge(4, 6);
	myGraph1->insertEdge(4, 8);
	myGraph1->insertEdge(5, 6);
	myGraph1->insertEdge(5, 8);
	myGraph1->insertEdge(7, 8);
	
	myGraph1->output(cout);
	
	myGraph1->BFS(0, visited_list1);
	
	cout << "Breadth First Search Visited List: ";
	for(int i = 0; i < visited_list1.size(); i++)
		cout << visited_list1.at(i) << " ";
	cout << endl;
	
	visited_list1.clear();
	myGraph1->DFS(0, visited_list1);
	
	cout << "Depth First Search Visited List: ";
	for(int i = 0; i < visited_list1.size(); i++)
		cout << visited_list1.at(i) << " ";
	cout << endl;
	
	cout << "\nADJACENCY LIST\n";
	myGraph2->insertEdge(0, 1);
	myGraph2->insertEdge(0, 3);
	myGraph2->insertEdge(1, 4);
	myGraph2->insertEdge(2, 4);
	myGraph2->insertEdge(3, 5);
	myGraph2->insertEdge(4, 6);
	myGraph2->insertEdge(4, 8);
	myGraph2->insertEdge(5, 6);
	myGraph2->insertEdge(6, 10);
	myGraph2->insertEdge(7, 8);
	myGraph2->insertEdge(7, 10);
	myGraph2->insertEdge(10, 9);
	
	myGraph2->output(cout);
	
	myGraph2->BFS(0, visited_list2);
	
	cout << "Breadth First Search Visited List: ";
	for(int i = 0; i < visited_list2.size(); i++)
		cout << visited_list2.at(i) << " ";
	cout << endl;
	
	visited_list2.clear();
	myGraph2->DFS(0, visited_list2);
	
	cout << "Depth First Search Visited List: ";
	for(int i = 0; i < visited_list2.size(); i++)
		cout << visited_list2.at(i) << " ";
	cout << endl << endl;
	
	return 0;
}

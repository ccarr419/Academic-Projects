/*
	Author:		Christian Carreras
	File:		treeTest.cpp
	Date:		10/18/2015
	Class:		CSC 402
	About:		Tests the treeGraph by inserting a number of nodes
			into the tree and then printing the tree in order,
			pre order and post order.
*/

#include <iostream>
#include "arrayBsTree.h"
using namespace std;

int main()
{
	bsTree *myTree;
	myTree = new arrayBsTree;
	//Insert nodes into tree
	myTree->insert(22);
	myTree->insert(3);
	myTree->insert(75);
	myTree->insert(10);
	myTree->insert(7);
	myTree->insert(1);
	myTree->insert(2);
	myTree->insert(34);
	myTree->insert(57);
	myTree->insert(100);
	myTree->insert(81);
	myTree->insert(0);
	myTree->insert(14);
	myTree->insert(28);
	myTree->insert(105);
	myTree->insert(79);
	
	myTree->erase(22);
	myTree->erase(100);
	myTree->erase(3);
	myTree->erase(75);
	myTree->erase(0);
	
	cout << "In Order: ";
	myTree->inOrder(cout);
	cout << endl;
	
	cout << "Pre Order: ";
	myTree->preOrder(cout);
	cout << endl;
	
	cout << "Post Order: ";
	myTree->postOrder(cout);
	cout << endl;
	
	cout << "Level Order: ";
	cout << endl;
	myTree->lvlOrder(cout);
	
	if(myTree->find(22))
		cout << "Root 22 found\n";
	
	if(myTree->find(0))
		cout << "Leaf 0 found\n";
	
	if(myTree->find(10))
		cout << "Leaf 10 found\n";
	
	if(myTree->find(79))
		cout << "Leaf 79 found\n";
	
	if(myTree->find(105))
		cout << "Leaf 105 found\n";
	
	if(!myTree->find(88))
		cout << "Leaf 88 not found\n";
	
	return 0;
}
/*
	Author:		Christian Carreras
	File:		treeGraph.cpp
	Date:		10/18/2015
	Class:		CSC 402
	About:		Code file for the treeGraph class. treeGraph is able
			to instantiate itself through a constructor by first
			having the root point to null. After construction, the
			user may insert elements in the binary tree. If the user
			chooses, he or she may print the tree in the way of
			three traversals. In Order NRL (Node Right Left) prints
			the list from least to greatest. Pre Order LNR
			(Left Node Right) and Post Order LRN (Left Right Node)
			preserves the tree in list form.
*/

#include <iostream>
#include <queue>
#include "arrayBsTree.h"
using namespace std;

/*
	Function:	Constructor
	MemberType:	Constructor
	Permission:	Public
	Parameters:	N/A
	ReturnValue:	N/A
	About:		Constructs the treeGraph by pointing the root to null
*/
arrayBsTree::arrayBsTree()
{	root = NULL; }

/*
	Function:	find
	MemberType:	Inspector
	Permission:	Public
	Parameters:	int - import only
	ReturnValue:	true - if found
			false - if not found
	About:		Traverses the tree looking for a node's data that is 
			equal to the parameter's value
*/
bool arrayBsTree::find(int info) const
{
	treeNode<int> *currNode = root;
	while(currNode != NULL)
	{
		if(info == currNode->data)
			return true;
		else if(info < currNode->data)
			currNode = currNode->left;
		else
			currNode = currNode->right;
	}
	return false;
}

/*
	Function:	insert
	MemberType:	Mutator
	Permission:	Public
	Parameters:	int - import only
	ReturnValue:	void
	About:		Imports a given value into the tree. If the tree is
			empty, the root will create a new node with the
			value of the given value. If the tree is not empty,
			the given value will be compared to the data of
			each node by going the left child if the given value
			is less than the current node's data or right if
			the value is greater. NodeCount is incremented after
			a proper insertion point is found.
*/
void arrayBsTree::insert(int info)
{
	if(root == NULL) //if there is an empty tree
	{
		root = new treeNode<int>(info);
		return;
	}
	
	treeNode<int> *currNode = root, *parent;
	
	while(currNode != NULL) //while there isn't an empty space
	{
		parent = currNode;
		if(info < currNode->data) //Go left is lesser than
			currNode = currNode->left;

		else //Go right if greater than
			currNode = currNode->right;
	}
	
	if(info < parent->data)
		parent->left = new treeNode<int>(info);
	else
		parent->right = new treeNode<int>(info);
	
	nodeCount++;
}

/*
	Function:	erase
	MemberType:	Mutator
	Permission:	Public
	Parameters:	int - import only
	ReturnValue:	void
	About:		First checks if the node to be erased is in the tree,
			if the node is in the tree, the node is deleted and if
			necessary a replacement will fill its spot
*/
void arrayBsTree::erase(int doomed)
{
	if(!find(doomed))
		return;
	
	treeNode<int> *nodeWithData, *nodeToDelete, *p = root, *trailP = NULL;
	while(p->data != doomed)
	{
		trailP = p;
		if(doomed < p->data)
			p = p->left;
		else
			p = p->right;
	}
	nodeWithData = p;
	
	if(nodeWithData->left == NULL && nodeWithData->right == NULL) 
	{	
		if(nodeWithData == root)
			root = NULL;
		else if(trailP->right == nodeWithData) //Parent's right child
			trailP->right = NULL;
		else 
			trailP->left = NULL;
			nodeToDelete = nodeWithData; //free this at the end
	}
	
	else if(nodeWithData->left == NULL) 
	{
		if(trailP == NULL) 
		{ 	// Node to delete is root and there is no left subtree
			nodeToDelete = root;
			root = root->right;
		}
		else 
	//Point parent's pointer to this node to this node's right child
		{
			if(trailP->right == nodeWithData) 
				trailP->right = nodeWithData->right;
			else 
				trailP->left = nodeWithData->right;
			nodeToDelete = nodeWithData;
		}
	}
	
	else if(nodeWithData->right == NULL) 
	{
		if (trailP == NULL) 
		{ 	// Node to delete is root and there is no left subtree
			nodeToDelete = root;
			root = root->left;
		}
		else 
		{	// Otherwise, move up the right subtree
			if(trailP->right == nodeWithData) 
				trailP->right = nodeWithData->left;
			else 
				trailP->left = nodeWithData->left;
			nodeToDelete = nodeWithData;
		}
	}
	
	else 
	{ 
		for(trailP = nodeWithData, p = nodeWithData->left;
			p->right != NULL; trailP = p, p = p->right);

		nodeWithData->data = p->data;
		if(trailP == nodeWithData) 
			trailP->left = p->left;
		else 
			trailP->right = p->left;
		
		nodeToDelete = p;
	}
	
	delete nodeToDelete;
}

/*
	Function:	inOrder
	MemberType:	Inspector
	Permission:	Public
	Parameters:	ostream - export only
	ReturnValue:	void
	About:		Prints the tree in order by giving the helper function
			the starting point of the root
*/
void arrayBsTree::inOrder(ostream& out) const
{	printInOrder(root, out); }

/*
	Function:	printInOrder
	MemberType:	Inspector
	Permission:	Private
	Parameters:	treeNode<int>* - import only
			ostream - export only
	ReturnValue:	void
	About:		Recursively prints the tree by going the left child
			until a left child cannot be found. Then that node is
			put in the ostream. Last go right and start the
			process again. LNR (Left Node Right).
*/
void arrayBsTree::printInOrder(treeNode<int>* currNode, ostream& out) const
{
	if(currNode == NULL)
		return;
		
	printInOrder(currNode->left, out);
	out << currNode->data << " ";
	printInOrder(currNode->right, out);
}

/*
	Function:	preOrder
	MemberType:	Inspector
	Permission:	Public
	Parameters:	ostream - export only
	ReturnValue:	void
	About:		Prints the tree pre order by giving the helper function
			the starting point of the root
*/
void arrayBsTree::preOrder(ostream& out) const
{	printPreOrder(root, out); }

/*
	Function:	printPreOrder
	MemberType:	Inspector
	Permission:	Private
	Parameters:	treeNode<int>* - import only
			ostream - export only
	ReturnValue:	void
	About:		Recursively prints the tree by putting the current node
			in the ostream, then going to the left child. If no left
			child can be found, go to the right child and start the
			process again. NRL (Node Right Left).
*/
void arrayBsTree::printPreOrder(treeNode<int>* currNode, ostream& out) const
{
	if(currNode == NULL)
		return;
	
	out << currNode->data << " ";
	printPreOrder(currNode->left, out);	
	printPreOrder(currNode->right, out);
}

/*
	Function:	postOrder
	MemberType:	Inspector
	Permission:	Public
	Parameters:	ostream - export only
	ReturnValue:	void
	About:		Prints the tree post order by giving the helper function
			the starting point of the root
*/
void arrayBsTree::postOrder(ostream& out) const
{	printPostOrder(root, out); }

/*
	Function:	printPostOrder
	MemberType:	Inspector
	Permission:	Private
	Parameters:	treeNode<int>* - import only
			ostream - export only
	ReturnValue:	void
	About:		Recursively prints the tree by going the left child
			until a left child cannot be found. Then go to the right
			child and start the process again. If no more children
			can be found, both left and right, put the current node
			in the ostream. LRN (Left Right Node).
*/
void arrayBsTree::printPostOrder(treeNode<int>* currNode, ostream& out) const
{
	if(currNode == NULL)
		return;
		
	printPostOrder(currNode->left, out);	
	printPostOrder(currNode->right, out);
	out << currNode->data << " ";
}

/*
	Function:	lvlOrder
	MemberType:	Inspector
	Permission:	Public
	Parameters:	ostream - export only
	ReturnValue:	void
	About:		Prints the tree in order by height (level) starting at
			the root
*/
void arrayBsTree::lvlOrder(ostream& out) const
{	printLvlOrder(root, out); }

/*
	Function:	printLvlOrder
	MemberType:	Inspector
	Permission:	Private
	Parameters:	treeNode<int>* - import only
			ostream - export only
	ReturnValue:	void
	About:		Uses a queue to order the tree by level. The root is
			put in the queue, then the root's left child, then its
			right child. A dummy node is put in the queue to
			determine a new level in the tree. The process repeats
			for each child in the tree
*/
void arrayBsTree::printLvlOrder(treeNode<int>* root, ostream& out) const
{
	queue<treeNode<int> *> q;
	treeNode<int> *lvl = new treeNode<int>(-1);
	
	if(root != NULL)
	{
		out << root->data << endl;
		q.push(root->left);
		q.push(root->right);
		q.push(lvl);
	}
	
	treeNode<int> *currNode = root;
	while(!q.empty())
	{
		currNode = q.front();
		q.pop();
		if(currNode == lvl)
		{
			if(!q.empty())
			{
				q.push(lvl);
				out << endl;
			}
		}
		else if(currNode != NULL)
		{
			out << currNode->data << " ";
			q.push(currNode->left);
			q.push(currNode->right);
		}
	}
}

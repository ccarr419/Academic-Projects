/*
	Author:		Christian Carreras
	File:		treeGraph.h
	Date:		10/18/2015
	Class:		CSC 402
	About:		Header file for treeGraph. treeGraph is a binary tree
			that ties together nodes in accordance to their values.
			This basic binary tree can insert nodes into the tree
			and print the tree in order, pre order or post order.
*/

#ifndef ARRAYBSTREE_H
#define ARRAYBSTREE_H

#include <iostream>
#include "bsTree.h"

class arrayBsTree : public bsTree {
	public:
		arrayBsTree();
		
		bool find(int) const;
		void insert(int);
		void erase(int);
		
		void inOrder(std::ostream&) const; //NLR
		void preOrder(std::ostream&) const; //LNR
		void postOrder(std::ostream&) const; //LRN
		void lvlOrder(std::ostream&) const; //Print by height
	
	private:
		treeNode<int>* root;
		int nodeCount;
		
		//private helper functions for specific traversals
		void printInOrder(treeNode<int>*, std::ostream&) const;
		void printPreOrder(treeNode<int>*, std::ostream&) const;
		void printPostOrder(treeNode<int>*, std::ostream&) const;
		void printLvlOrder(treeNode<int>*, std::ostream&) const;
};

#endif

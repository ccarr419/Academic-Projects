/*
	Author:		Christian Carreras
	File:		treeNode.h
	Date:		10/18/2015
	Class:		CSC 402
	About:		Header file for treeNode. treeNodes are the components
			of the treeGraph/binary tree. A treeNode is comprised of
			data which is a template for any data type or data
			structure. A treeNode also has a pointer to its
			left and right child/leaf.
*/

#include <iostream>

template <class T>
struct treeNode {
	T data;
	treeNode<T> *left, *right;
	
	treeNode() {};
	treeNode(const T& info)
	{	data = info; }	
};
	
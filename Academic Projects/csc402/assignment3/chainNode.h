/*
	Author:	Christian Carreras
	File:	chainNode.h
	About:	Node class holds a element that is a template for any
		given class. Node also has a pointer to another node.
*/

#include <iostream>
using namespace std;

template<class T> struct chainNode {
	T element;
	chainNode<T> *next;
	
	chainNode() {};
	chainNode(const T& theElement) { this->element = theElement; }
	chainNode(const T& theElement, chainNode<T>* theNext)
	{	this->element = theElement;
		this->next = theNext;
	}
};
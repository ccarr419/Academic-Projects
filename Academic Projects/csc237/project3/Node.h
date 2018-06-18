/**
// Author:	Dr. Spiegel
// Updated By:	Christian Carreras
// Course:	CSC 237
// File: 	Node.h
// Purpose:	Doubly-linked list node definition/implementation
*/
#ifndef NODE_H
#define NODE_H
#include <cstddef>

// Need to prototype template classes if they are to be friends
template <class eltType> class node
{	private:
		node(eltType info, node* back=NULL, node* link = NULL ) : 
					data(info), prev(back), next(link) {};
		eltType data;
		node *prev, *next;
	//Let The DLinkedList and DListItr be friend classes
	template <class T> friend class DLinkedList;
	template <class T> friend class DListItr;
};

#endif

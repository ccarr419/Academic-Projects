/**
// Author:	Christian Carreras
//		(with thanks to Dr. Spiegel for
//		the original single linked list)
// Course:	CSC 237
// Filename:	DLinkedList.cpp
// Purpose:	This file implements the code for the data
//		members of the DLinkedList class. Pointers
//		to the nodes are used to make everything possible.
//		This is a templated class, and only uses the data types
//		specified within types.tpp	
*/
#include <assert.h>
#include <iostream>
#include "DLinkedList.h"
#include "Node.h"

using namespace std;

/**
//DLinkedList constructor, sets head eqaul to NULL
*/
template <typename eltType> DLinkedList<eltType>::DLinkedList() : head(NULL)
{}

/**
//DLinkedList copy constructor, calls copy private data member
*/
template <typename eltType> DLinkedList<eltType>::DLinkedList(const DLinkedList<eltType> &cl)
{head = copy( cl.head );}

/**
//DLinkedList destructor, calls destroy data member
*/
template <typename eltType> DLinkedList<eltType>::~DLinkedList()
{destroy(head);}

/**
//Inserts in order by checking all conditions for insertion:
//**Empty list
//**Beginning of list
//**Middle of list
//**End of list
*/
template <typename eltType> bool DLinkedList<eltType>::insert(eltType x)
{   	if (head == NULL || x < head->data) //Empty list or first in list
	{	if(head == NULL) //Empty list
			assert(head=new node<eltType>(x, NULL, head));
		else //First in the list
		{	node<eltType>* temp = head;
			assert(head=new node<eltType>(x, NULL, head));
			temp->prev = head;
		}
	}
	else //Further down the list
	{	node<eltType>* p = head->next;
		node<eltType>* trailp = head;
		while (p != NULL && x > p->data)
		{ 	trailp = p;
			p = p->next;
		}
		assert((trailp->next = new node<eltType>(x, trailp, p)) != NULL);
		if(p != NULL) //Middle of list
			p->prev = trailp->next;
	}
	return true;
}

/**
//Removes by checking all conditions for node removal:
//**Beginning of list
//**End of list
//**Middle of list
//**Not in list
*/
template <typename eltType> bool DLinkedList<eltType>::remove(eltType x) 
{       //assert(head != NULL);
	node<eltType>*  p = head;
	node<eltType>*  trailp = NULL;
	while ( p != NULL && p->data < x )
	{       trailp = p;
		p = p->next;
	}
	if(p == NULL) //Empty list
		return false;
	else if(p->data == x) //Node found
	{	if(p == head) //If node is first node
		{	if(p->next == NULL) //If node is only node in the list
				head = NULL;
			else
			{	head = head->next; //Not only node in list
				head->prev = NULL;
			}
		}
		else if(p->next == NULL) //Last in the list
			trailp->next = NULL;
		else
		{	trailp->next = p->next; //x is farther down in the LinkedList
			p->next->prev = trailp;
		}
		delete p;
		return true; //Removal successful
	}
  
	else //Not in the list
		return false;
}

/**
//Assignment operator copies the list to be assigned, destroys the old list
//and assigns the new list
*/
template <typename eltType> DLinkedList<eltType>
	&DLinkedList<eltType>::operator =(const DLinkedList<eltType>& cl)
{       if (this != &cl)
	{       destroy(head);
		head = copy(cl.head);
	}
	return *this;
}

/**
//Copies one list into a completely new list
*/
template <typename eltType>
node<eltType>* DLinkedList<eltType>::copy(node<eltType> *l)
{       node<eltType>* first = NULL;    // ptr to beginning of copied LinkedList
	node<eltType>* last = NULL;     // ptr to last item insert in the copy
	if (l != NULL)
	{       assert((first=last=new node<eltType>(l->data,NULL, NULL)) != NULL);
		for (node<eltType>* source=l->next;source!=NULL; source=source->next,last=last->next)
		{       last->next = new node<eltType>(source->data, last, NULL);
			assert(last->next);
		}
	}
	return first;
}

/**
//Destroys the whole DLinkedList node by node using recursion
*/
template <typename eltType> void DLinkedList<eltType>::destroy(node<eltType> *l)
{     	if(l == NULL) //If end of list or empty
		return;
	else
	{	destroy(l->next);
		node<eltType> *doomed = l;
		delete doomed; //destroy current node
	}
}

/**
//The constructor of the DListItr. The DLinkedList to be pointed at
//is taken as a parameter
*/
template <typename eltType>
DListItr<eltType>::DListItr(const DLinkedList<eltType> &l): itr(l),curr(l.head)
{}

/**
//Places the iterator at the begining of the list and returns that node's data
*/
template <typename eltType> eltType DListItr<eltType>::begin(void)
{	curr = itr.head;
	return curr->data;
}

/**
//Checks if the DLinkedList head is pointing to NULL (empty)
*/
template <typename eltType> bool DListItr<eltType>::isEmpty(void)
{	return (itr.head == NULL);}

/**
//Checks if the current iterator is pointing at the first node in the list
*/
template <typename eltType> bool DListItr<eltType>::isFirstNode(void)
{	assert(curr != NULL);
	return curr->prev == NULL;
}

/**
//Checks if the current iterator is pointing at the last node in the list
*/
template <typename eltType> bool DListItr<eltType>::isLastNode(void)
{	assert(curr != NULL);
	return curr->next == NULL;
}

/**
//Checks whether the current iterator is eqaul to NULL or not
*/
template <typename eltType> bool DListItr<eltType>::isNull(void)
{	return curr == NULL;}

/**
//The * operator returns a pointer the node's data which the current
//iterator is pointing at
*/
template <typename eltType> eltType DListItr<eltType>::operator*(void) const
{	return curr->data;}

/**
//The pre-increment operator moves the iterator
//forward one node
*/
template <typename eltType> DListItr<eltType>& 
DListItr<eltType>::operator++(void)
{	assert(curr != NULL);
	curr = curr->next;
	return *this; //Return the current iterator
}

/**
//The pre-decrement operator moves the iterator
//back one node
*/
template <typename eltType> DListItr<eltType>& 
DListItr<eltType>::operator--(void)
{	assert(curr != NULL);
	curr = curr->prev;
	return *this; //Return the current iterator
}
/**
// Author:	Christian Carreras
// Course:	CSC 237
// File:	types.tpp
// Purpose:	Necessary for explicit initialization
*/

//Explicit Initializers. Necessary to be able to be able to place 
//template class function implementations in a .cpp file
#include "Node.h"
#include "WordData.h"

template class node<int>;
template class node<WordData>;
template class DLinkedList<int>;
template class DLinkedList<WordData>;
template class DListItr<int>;
template class DListItr<WordData>;

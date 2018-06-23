/*
File: 		LinkedList.cpp
Author:		Dr. Spiegel
Updated by:	Christian Carreras
Course:		CSC136
Assignment:	Project 4
Description:	Code that implements the LinkedList class.
		makes it possible that the LinkedList, node
		and listItr work together to create one object.
*/
#include <assert.h>
#include <iostream>
#include "LinkedList.h"

// Construct empty LinkedList
template <typename eltType> LinkedList<eltType>::LinkedList() : head(NULL)
{}

// Copy constructor. copy() does the deep copy
template <typename eltType> LinkedList<eltType>::LinkedList(const LinkedList<eltType> &cl)
{head = copy( cl.head );}

// Free all nodes
template <typename eltType> LinkedList<eltType>::~LinkedList()
{destroy(head);}

// Assignment operator: copy() does the deep copy
template <typename eltType> LinkedList<eltType>
	&LinkedList<eltType>::operator =(const LinkedList<eltType>& cl)
{       if (this != &cl)
    {       destroy(head);
      head = copy(cl.head);
    }
  return *this;
}

// Place x into the list in order
template <typename eltType> bool LinkedList<eltType>::orderedInsert(eltType x)
{   if (empty() || x > head->data)
    assert(head=new node<eltType>(x,head));
  else   // start at 2nd node...already checked first node
    {	node<eltType>*  p       = head -> next; // head;
	node<eltType>*  trailp  = head;         // NULL;
	while (p != NULL && x < p->data)
	{       trailp = p;
		p = p->next;
	}
	
	//Check if there's a duplicate
	if(find(x))
	{	p->data += x; //Add coefficients together
		return false; 
	}

	else	//If there's no duplicate
	{ 	assert((trailp->next = new node<eltType>(x,p)) != NULL);
		return true; 
	}
    }
}

// Is this element in the linked list?
template <typename eltType> bool LinkedList<eltType>::find(eltType x)
{       node<eltType> *p = head;
  while (p != NULL && p->data > x)
    p = p->next;
  return (p != NULL && p->data == x);
}

// Inline: Look into this.
template <typename eltType> inline bool LinkedList<eltType>::empty()
{return (head == NULL);}

// Remove a node in an ordered list
// Pre: Node will be found
template <typename eltType> bool LinkedList<eltType>::remove(eltType x)
{       assert( !empty() );
  node<eltType>*  p = head;
  node<eltType>*  trailp = NULL;
  while ( p != NULL && p->data > x )
    {       trailp = p;
      p = p->next;
    }
  if(p->data == x)
  {	if (p == head)
		head = head->next;      // x is first in the LinkedList
	else
		trailp->next = p->next; // x is farther down in the LinkedList
	delete p;
	return true;
  }
  
  else
  return false;
}

// Remove all nodes in the linked list, starting at l
template <typename eltType> void LinkedList<eltType>::destroy(node<eltType> *l)
{       while (l != NULL)
    {       node<eltType> *doomed = l;
      l = l->next;
      delete doomed;
    }
}

// The deep copy. Copy the source list l, one node at a time
template <typename eltType>
node<eltType>* LinkedList<eltType>::copy(node<eltType> *l)
{       node<eltType>* first = NULL;    // ptr to beginning of copied LinkedList
  node<eltType>* last = NULL;     // ptr to last item insert in the copy
  if (l != NULL)
    {       assert((first=last=new node<eltType>(l->data,NULL)) != NULL);
      for (node<eltType>* source=l->next;source!=NULL;
	   source=source->next,last=last->next)
	{       last->next = new node<eltType>(source->data,NULL);
	  assert(last->next);
	}
    }
  return first;
}
// Output a linked list, using a list iterator
template <typename eltType> ostream& operator<<(ostream &os,const LinkedList<eltType> &l)
{
  listItr<eltType> lt(l);

  while ( lt.more() ) {
    os << lt.value();
    lt.next();
  }
  return os;
}

// Count nodes in a linked list, starting at l
template <typename eltType> int LinkedList<eltType>::countNodes(node<eltType> *p)
{return ((p) ?  1+countNodes(p->next) : 0);}

// Return number of nodes in *this' list
template <typename eltType> int LinkedList<eltType>::countNodesInList()
{return(countNodes(head));}

/* ****************************************************************
************** List Iterator Implementations *******************
****************************************************************/

// Construct a list iterator. It consists of:
//       a reference to a linked list object
//       a pointer to the actual list, initially pointing to its head
template <typename eltType>
listItr<eltType>::listItr(const LinkedList<eltType> &l): itr(l),curr(l.head)
{}

// Set curr to point at itr's head
template <typename eltType> eltType listItr<eltType>::start(void)
{return head->data;}

// Is curr at the end of the list?
template <typename eltType> bool listItr<eltType>::more(void)
{return curr != NULL;}

// Move curr to next node
template <typename eltType> void listItr<eltType>::next(void)
{assert( curr != NULL );
  curr = curr->next;
}

// Return data in curr's node. Regardless of assert(), this
//      function shouldn't be called until making sure more() returns true
template <typename eltType> eltType &listItr<eltType>::value(void) const
{assert( curr != NULL );
  return curr->data;
}

/*
File: 		LinkedList.h
Author:		Dr. Spiegel
Updated by:	Christian Carreras
Course:		CSC136
Assignment:	Project 4
Description:	LinkedList class with listItr class.
		A nearly infinite template object that is
		a container for whatever it is needed for.
		Creates the node object which are linked together. 
		The nodes are the containers.
*/
#ifndef _LinkedList_
#define _LinkedList_
#include <assert.h>
#include <iostream>

using namespace std;

// Need to prototype template classes if they are to be friends
template <typename eltType> class LinkedList;
template <typename eltType> class listItr;
/*
// and also the friend...note <> in header declaration of <<
template <typename eltType>
                ostream& operator<<(ostream&,LinkedList<eltType>);
*/

template <typename eltType> class node
{private:
  node(eltType info, node* link = NULL ) :  data(info), next(link) {};
  eltType data;
  node*   next;
  friend class LinkedList<eltType>;
  friend class listItr<eltType>;
};

template <typename eltType> class LinkedList
{
 public:
  // Construct empty LinkedList
  LinkedList();
  // Construct deep copy of another LinkedList
  LinkedList(const LinkedList&);

  // destroy LinkedList
  ~LinkedList();

  // Assign another LinkedList to this LinkedList; deep copy
  LinkedList& operator=(const LinkedList&);

  // Is the LinkedList empty?
  bool empty();

  bool find(eltType);

  // Ordered insert/remove
  bool orderedInsert(eltType);
  bool remove(eltType);

  // Quick example of recursion
  int  countNodesInList();

 private:
  // linked list pointer
  node<eltType>*  head;

  // Get a copy of a (deep) node
  node<eltType>*  copy(node<eltType> *);

  // Free nodes of a linked list
  void    destroy(node<eltType> *);

  // Need this to count nodes in LinkedList
  int     countNodes(node<eltType> *);
  /*
        // Linked list to ostream
        friend ostream& operator<< <>(ostream&, LinkedList<eltType>);
  */

  // Needed to use a list iterator
  friend class listItr<eltType>;
};

template <typename eltType> ostream& operator<<(ostream &os,const LinkedList<eltType> &l);

// Set up an iterator;
//      an object that provides a pointer to a linked list (in this case)
template <typename eltType> class listItr
{
 public:
  // Construct a List Iterator
  listItr(const LinkedList<eltType> &l);

  // Set curr to point at the first node of itr
  void start();
  // Is curr null?
  bool more();
  // Go to curr->next
  void next();
  // Get the value out of curr's node
  eltType &value() const;

 private:
  const LinkedList<eltType> &itr;
  node<eltType> *curr;
};

#endif

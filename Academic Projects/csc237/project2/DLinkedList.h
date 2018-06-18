/*
// Author:	Christian Carreras
//		(with thanks to Dr. Spiegel for
//		the original single linked list)
// Course:	CSC 237
// Filename:	DLinkedList.h
// Purpose:	The double linked list class uses nodes
//		with a forward and backward pointer to
//		make a list easy to iterate through.
//		Also included is the DLinkedList Iterator.
//		The iterator is named DListItr and is used
//		to access data within the list.		
*/
#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H
#include "Node.h"

template <typename eltType> class DLinkedList
{

public:
	/*
	// Function Name:	Constructor
	// Member Type:		Constructor
	// Parameters:		none
	// Returns:		N/A
	// Purpose:		Constructs a double linked list
	*/
	DLinkedList();
	
	/*
	// Function Name:	Copy Constructor
	// Member Type:		Copy Constructor
	// Parameters:		const DLinkedList& - import only
	// Returns:		N/A
	// Purpose:		Creates a copy of a DLinkedList
	*/
	DLinkedList(const DLinkedList&);
	
	/*
	// Function Name:	Destructor
	// Member Type:		Destructor
	// Parameters:		none
	// Returns:		N/A
	// Purpose:		Deletes an instantiation of a DLinkedList
	*/
	~DLinkedList();
	
	/*
	// Function Name:	= operator
	// Member Type:		Mutator
	// Parameters:		const DLinkedList& - import only
	// Returns:		DLinkedList& - the object itself
	// Purpose:		Sets a DLinkedList equal to another
	*/
	DLinkedList& operator=(const DLinkedList&);
	
	/*
	// Function Name:	insert
	// Member Type:		Mutator
	// Parameters:		eltType - import only
	// Returns:		true if inserted, false if not
	// Purpose:		Inserts data into the list in order
	*/
	bool insert(eltType);
	
	/*
	// Function Name:	remove
	// Member Type:		Mutator
	// Parameters:		eltType - import only
	// Returns:		true if removed, false if not
	// Purpose:		Removes data from the list and
	//			adjusts list appropriately
	*/
	bool remove(eltType);
	
private:
	node<eltType>* head;
	
	/*
	// Function Name:	copy
	// Member Type:		Mutator
	// Parameters:		node<eltType>* - import only
	// Returns:		node<eltType>* - first node of copied list
	// Purpose:		copies existing list into new list
	*/
	node<eltType>* copy(node<eltType>*);
	
	/*
	// Function Name:	destroy
	// Member Type:		Mutator
	// Parameters:		node<eltType>* - import only
	// Returns:		void
	// Purpose:		Destroys a DLinkedList object
	*/
	void destroy(node<eltType>*);
	
//Let the DListItr be a friend class	
template <class T> friend class DListItr;

};

template <typename eltType> class DListItr
{

public:
	/*
	// Function Name:	Constructor
	// Member Type:		Constructor
	// Parameters:		const DLinkedList<eltType>& - import only
	// Returns:		N/A
	// Purpose:		Constructs an iterator for the given list
	*/
	DListItr(const DLinkedList<eltType> &l);
	
	/*
	// Function Name:	begin
	// Member Type:		Mutator
	// Parameters:		none
	// Returns:		eltType - the data at the first node
	// Purpose:		Puts the iterator at the first node
	//			and returns the value at that node
	*/
	eltType begin();
	
	/*
	// Function Name:	isEmpty
	// Member Type:		Facilitator
	// Parameters:		none
	// Returns:		true if the list is empty
	//			false if not
	// Purpose:		Checks if head == NULL (empty)
	*/
	bool isEmpty();
	
	/*
	// Function Name:	isFirstNode
	// Member Type:		Facilitator
	// Parameters:		none
	// Returns:		true if first node
	//			false if not
	// Purpose:		Checks node if it is the first in the list
	//			by checking if prev is NULL
	*/
	bool isFirstNode();
	
	/*
	// Function Name:	isLastNode
	// Member Type:		Facilitator
	// Parameters:		none
	// Returns:		true if last node
	//			false if not
	// Purpose:		Checks node if it is the last node in the list
	//			by checking if next is NULL
	*/
	bool isLastNode();
	
	/*
	// Function Name:	isNull
	// Member Type:		Facilitator
	// Parameters:		none
	// Returns:		true if current node is NULL
	//			false if not
	// Purpose:		checks if iterator is out of the list
	*/
	bool isNull();
	
	/*
	// Function Name:	* operator
	// Member Type:		Inspector
	// Parameters:		none
	// Returns:		eltType - current node's data
	// Purpose:		returns the current node's data the
	//			iterator is pointing at
	*/
	eltType operator*() const;
	
	/*
	// Function Name:	++ operator (pre-increment)
	// Member Type:		Mutator
	// Parameters:		none
	// Returns:		DListItr<eltType>& - the iterator itself
	// Purpose:		Moves the iterator to the next node
	//			and returns the iterator to that node
	*/
	DListItr<eltType>& operator++();
	
	/*
	// Function Name:	-- operator (pre-decrement)
	// Member Type:		Mutator
	// Parameters:		none
	// Returns:		DListItr<eltType>& - the iterator itself
	// Purpose:		Moves the iterator to the previous node
	//			and returns the iterator to that node
	*/
	DListItr<eltType>& operator--();

private:
	const DLinkedList<eltType> &itr;
	node<eltType> *curr;

//Let the DLinkedList be a friend class
template <class T> friend class DLinkedList;

};

#endif

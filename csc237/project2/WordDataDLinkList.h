/*
// Author:	Christian Carreras
// Course:	CSC 237
// Filename:	WordDataDLinkList.h
// Purpose:	The WordDataDLinkList.h has a single data member
		DLinkedList. This class parses a file into the list,
		and prints the list iteratively and recursively
*/
#ifndef WORDDATADLINKLIST_H
#define WORDDATADLINKLIST_H
#include "WordList.h"
#include "WordData.h"
#include "Node.h"
#include "DLinkedList.h"

using namespace std;

class WordDataDLinkList : public WordList {
public:
	
	/*
	// Function Name:	Constructor
	// Member Type:		Constructor
	// Parameters:		none
	// Returns:		N/A
	// Purpose:		Constructs the WordDataDLinkList object
	*/
	WordDataDLinkList();
	
	/*
	// Function Name:	parseIntoList
	// Member Type:		Mutator
	// Parameters:		ifstream & - import/export
	// Returns:		void
	// Purpose:		Inserts data from file into DLinkedList
	*/
	void parseIntoList(ifstream &);
	
	/*
	// Function Name:	printIteratively
	// Member Type:		Facilitator
	// Parameters:		none
	// Returns:		void
	// Purpose:		Prints list with an iterator
	//			uses polymorphism to use correct function
	*/
	void printIteratively();

	/*
	// Function Name:	printRecursively
	// Member Type:		Facilitator
	// Parameters:		none
	// Returns:		void
	// Purpose:		Prints list with recursive function calls
	//			uses polymorphism
	*/
	void printRecursively();
	
private:

	DLinkedList<WordData> DList;
	
	/*
	// Function Name:	printRecursivelyWorker
	// Member Type:		Facilitator
	// Parameters:		DListItr<WordData> - import only
	// Returns:		void
	// Purpose:		Uses recursive calls to print list
	//			Used by the printRecursively function
	*/
	void printRecursivelyWorker(DListItr<WordData>);
	
	/*
	// Function Name:	incMatch
	// Member Type:		Mutator
	// Parameters:		string - import only
	// Returns:		true if match found
	//			false if not
	// Purpose:		Tries to find a match in the list
	//			and increments the count of the word
	//			if a match is found
	*/
	bool incMatch(string temp);
	
};

#endif


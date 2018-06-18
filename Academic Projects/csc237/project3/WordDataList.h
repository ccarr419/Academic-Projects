/**
// Author:		Dr. Spiegel
// Documented By:	Christian Carreras
// Course:		CSC 237
// Filename:		WordDataList.h
// Purpose:
*/
#ifndef WORDDATALIST_H
#define WORDDATALIST_H

#include <string>
#include "WordList.h"
#include "WordData.h"

using namespace std;

class WordDataList : public WordList {
public:

	/**
	// Function Name:	Constructor
	// Member Type:		Constructor
	// Parameters:		none
	// Returns:		N/A
	// Purpose:		Constructs the WordDataList object
	*/
	WordDataList();

	/**
	// Function Name:	parseIntoList
	// Member Type:		Mutator
	// Parameters:		ifstream& - import/export
	// Returns:		void
	// Purpose:		Parses file into WordDataList's data member
	*/
	void parseIntoList(ifstream &inf);

	/**
	// Function Name:	printIteratively
	// Member Type:		Facilitator
	// Parameters:		none
	// Returns:		void
	// Purpose:		Prints the object array iteratively with
	//			a for loop
	*/
	void printIteratively();
  
	/**
	// Function Name:	printRecursively
	// Member Type:		Facilitator
	// Parameters:		none
	// Returns:		void
	// Purpose:		Prints the object array with recursive calls
	//			uses the printRecursivelyWorker function
	*/
	void printRecursively();
  
	/**
	// Function Name:	printPtrRecursively
	// Member Type:		Facilitator
	// Parameters:		none
	// Returns:		void
	// Purpose:		Prints the object array with recursive calls
	//			and pointers
	*/
	void printPtrRecursively();

private:
	WordData TheWords[10];
	int numWords;

	/**
	// Function Name:	incMatch
	// Member Type:		Mutator
	// Parameters:		string - import only
	// Returns:		true if match found
	//			false if not
	// Purpose:		Find if there is already an occurrence
	//			of the word in the object array
	*/
	bool incMatch(string temp);
  
	/**
	// Function Name:	printRecursivelyWorker
	// Member Type:		Facilitator
	// Parameters:		int - import only
	// Returns:		void
	// Purpose:		Used by the printRecursively function
	//			to do the recursive calls
	*/
	void printRecursivelyWorker(int numWords);

	/**
	// Function Name:	printPtrRecursivelyWorker
	// Member Type:		Facilitator
	// Parameters:		int - import only
	// Returns:		void
	// Purpose:		Used by the pritnPtrRecursively function
	//			to do the recursive calls
	*/
	void printPtrRecursivelyWorker(int numWords);

};
  
#endif

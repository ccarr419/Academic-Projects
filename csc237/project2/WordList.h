/*
// Author:		Dr. Spiegel
// Documented By:	Christian Carreras
// Course:		CSC 237
// Filename:		WordList.h
// Purpose:		Abstract base class for containers of word data
//			Known subclasses: WordDataList, WordDataDLinkList
*/
#ifndef WORDLIST_H
#define WORDLIST_H

#include <fstream>
#include <string>

using namespace std;

class WordList {
public:

	/*
	// Function Name:	parseIntoList
	// Parameters:		ifstream& - import/export
	// Returns:		void
	// Purpose:		Pure virtual funtion to be used by subclasses
	*/
	virtual void parseIntoList(ifstream &inf)=0;

	/*
	// Function Name:	printIteratively
	// Parameters:		none
	// Returns:		void
	// Purpose:		Pure virtual funtion to be used by subclasses
	*/
	virtual void printIteratively()=0;
  
	/*
	// Function Name:	printRecursively
	// Parameters:		none
	// Returns:		void
	// Purpose:		Pure virtual funtion to be used by subclasses
	*/
	virtual void printRecursively()=0;
  
	/*
	// Function Name:	printPtrRecursively
	// Parameters:		none
	// Returns:		void
	// Purpose:		Not pure virtual because only used by WordDataList
	*/
	virtual void printPtrRecursively() {}
    
};
  
#endif

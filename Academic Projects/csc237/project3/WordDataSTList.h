/**
* Author:	Christian Carreras
* File:		WordDataSTList.h
* Date Created:	3/30/14
* Class:	CSC 237 Spring 2014
* Purpose:	This is the header file for the WordDataSTList class.
*		The WordDataSTList is a subclass of the WordList class.
*		Using pure virtual functions in the WordList class the
*		subclasses inherits those functions and implements them
*		through polymorphism. Meaning the function is linked up
*		to the correct use of that function at run time for there
*		are multiple uses of that function due to inheritance.
*		This class uses the Standard Library List (STL) list to
*		hold data (WordData objects) and uses the inherited functions
*		to add to the list and print the list iteratively and
*		recursively with the help of helper functions.
**/
#ifndef WORDDATASTLIST_H
#define WORDDATASTLIST_H

#include "WordList.h"
#include "WordData.h"
#include <list>

using namespace std;

class WordDataSTList : public WordList {
public:

	/**
	* This is the WordSTList constructor. The constructor creates the 
	* WordDataSTList. This is a default constructor meaning that this 
	* is the default C++ constructor for all objects.
	**/
	WordDataSTList();
	
	/**
	* This function uses polymorphism to link up the pure virtual function
	* from the superclass to the code for the subclasses' use of that
	* function. This function reads the parameter file and parses the
	* strings into the list into using the WordData object data type.
	* IncMatch is also called to check for duplicates.
	**/
	void parseIntoList(ifstream &);
	
	/**
	* This function also uses polymorphism to link up the pure virtual 
	* function from the superclass. The purpose of this function is to 
	* iterate through the list one by one and print the data to the
	* screen until the end of the screen is reached.
	**/
	void printIteratively();
	
	/**
	* This is another function that uses polymorphism from the superclass.
	* The purpose of this function is iterate through the list with
	* recursive calls (with the help of the printRecursivelyWorker functon)
	**/
	void printRecursively();
	
private:
	
	list<WordData> STList;
	
	/**
	* This function is a helper function to printRecursively. This function
	* actually makes the recursive calls by iterating through the list one
	* by one and printing the data until the end of the list is reached.
	**/
	void printRecursivelyWorker(list<WordData>::iterator);
	
	/**
	* This function is a helper function to parseIntoList. This function
	* checks for a duplicate occurrence within the list. If a duplicate
	* is found then the number of occurrences for that word is increased
	* by one and true is returned. If no duplicate is found then false
	* is returned and the list is unchanged.
	**/
	bool incMatch(string);
	
};

#endif

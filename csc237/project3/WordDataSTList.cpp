/**
* Author:	Christian Carreras
* File Name:	WordDataSTList.cpp
* Date Created:	3/30/14
* Class:	CSC 237 Spring 2014
* Purpose:	This cpp file implements the functions of the header file
*		WordDataSTList.h. Some functions use polymorphism due to
*		WordDataSTList being a sub class. WordDataSTList has three
*		functions that use polymorphism and two helper functions.
*		Helper functions are used for recursive printing and finding
*		duplicates within the list.
**/
#include <iostream>
#include <list>
#include "WordDataSTList.h"
#include "WordData.h"

using namespace std;

/**
* Function Name:	Constructor
* Member Type:		Constructor
* Parameters:		None
* Return Value:		N/A
* Purpose:		Constructs the WordDataSTList object
*			Default constructor
**/
WordDataSTList::WordDataSTList()
{}

/**
* Function Name:	parseIntoList
* Member Type:		Mutator
* Parameters:		ifstream - import/export (reads from file)
* Return Value:		void
* Purpose:		Implemented through polymorphism by being a subclass
*			of the WordList class. Reads from the parameter file
*			into the STL list and calls incMatch to check for 
*			duplicates.
**/
void WordDataSTList::parseIntoList(ifstream &inf)
{	string temp; //Temporary storage
	WordData theWord;
	while (inf >> temp) 
	{	if (!incMatch(temp)) //Check if match first
		{	//Insert into list
			theWord.setWord(temp);
			theWord.setCount(1);
			STList.push_back(theWord);
		}
	}
}

/**
* Function Name:	printIteratively
* Member Type:		Inspector
* Parameters:		None
* Return Value:		void
* Purpose:		Also implemented through polymorphism, this function
*			with the help of a for loop and list iterator goes
*			through the list element by element and prints
*			the WordData info to the screen.
**/
void WordDataSTList::printIteratively()
{	cout<<"--------------------------"<<endl;
	cout<<"|STL List       Iterative|"<<endl;
	cout<<"|Word         Occurences |"<<endl;  
	cout<<"--------------------------"<<endl;
	for(list<WordData>::iterator it = STList.begin(); 
	it != STList.end(); ++it)
		cout << " " << *it << endl;
}

/**
* Function Name:	printRecursively
* Member Type:		Inspector
* Parameters:		None
* Return Value:		void
* Purpose:		Another function implemented through polymorphism.
*			This function calls printRecursivelyWorker to go
*			through the the list and print the WordData info
*			recursively until the end of the list is reached.
**/
void WordDataSTList::printRecursively()
{	list<WordData>::iterator it = STList.begin();
	cout<<"--------------------------"<<endl;
	cout<<"|STL List       Recursive|"<<endl;
	cout<<"|Word         Occurences |"<<endl;  
	cout<<"--------------------------"<<endl;
	printRecursivelyWorker(it);
}

/**
* Function Name:	printRecursivelyWorker
* Member Type:		Inspector
* Parameters:		list<WordData>::iterator - import only
* Return Value:		void
* Purpose:		Called by the printRecursively function to make
*			the recursive calls, iterate through the list
*			and print the WordList info until the end of the
*			list is reached.
**/
void WordDataSTList::printRecursivelyWorker(list<WordData>::iterator it)
{	if(it == STList.end()) //Check if iterator is at the end of the list
		return; //Stop recursion, go back
	cout << " " << *it << endl;
	printRecursivelyWorker(++it);
}

/**
* Function Name:	incMatch
* Member Type:		Mutator
* Parameters:		string - import only (test for match)
* Return Value:		True if match is found
*			False if no match found
* Purpose:		Called by the parseIntoList function.
*			Iterates through list until a match is found
*			or the end of the list is reached. If a match is
*			found then the current data is erased and new data
*			with the new count is inserted.
**/
bool WordDataSTList::incMatch(string temp)
{	for(list<WordData>::iterator it = STList.begin(); 
	it != STList.end(); ++it)
	{	WordData checkWord = *it;
		if (temp == checkWord.getWord()) //If match
		{	it = STList.erase(it); 
			checkWord.incCount();	
			STList.insert(it, checkWord);
			return true;
		}
	}
	return false; //No match found
}

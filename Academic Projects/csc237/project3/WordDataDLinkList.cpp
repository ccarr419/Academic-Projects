/**
// Author:	Christian Carreras
// Course:	CSC 237
// Filename:	WordDataDLinkList.cpp
// Purpose:	Implements the code for the WordDataDLinkList class
//		The DLinkedList data member is specifically of the
//		WordData type and adjusts accordingly. When a duplicate
//		word is found, only the counter is incremented
//		no word will be inserted
*/
#include <iostream>
#include "WordDataDLinkList.h"
#include "DLinkedList.h"
#include "WordData.h"

using namespace std;

/**
//Constructor
*/
WordDataDLinkList::WordDataDLinkList()
{}

/**
//Checks for matching data within the list
*/
bool WordDataDLinkList::incMatch(string temp)
{	for(DListItr<WordData> it(DList); !(it.isNull()); ++it)
	{	WordData checkWord = *it;
		if (temp == checkWord.getWord()) //If match
		{	DList.remove(checkWord); 
			checkWord.incCount();	
			DList.insert(checkWord);
			return true;
		}
	}
    return false; //No match found
}

/**
//Parse from file into DLinkedList
*/
void WordDataDLinkList::parseIntoList(ifstream &inf)
{ 	string temp; //Temporary storage
	WordData theWord;
	while (inf >> temp) 
	{	if (!incMatch(temp)) //Check if match first
		{	//Insert into list
			theWord.setWord(temp);
			theWord.setCount(1);
			DList.insert(theWord);
		}
	}
}

/**
//Print the list with an iterator and for loop
*/
void WordDataDLinkList::printIteratively()
{	cout<<"--------------------------"<<endl;
	cout<<"|D Linked List  Iterative|"<<endl;
	cout<<"|Word         Occurences |"<<endl;  
	cout<<"--------------------------"<<endl;
	for(DListItr<WordData> it(DList); !(it.isNull()); ++it)
		cout << " " << *it << endl;	
}

/**
//Print the list with recursive calls
//Calls printRecursivelyWorker
*/
void WordDataDLinkList::printRecursively()
{	DListItr<WordData> it(DList);
	cout<<"--------------------------"<<endl;
	cout<<"|D Linked List  Recursive|"<<endl;
	cout<<"|Word         Occurences |"<<endl;  
	cout<<"--------------------------"<<endl;
	printRecursivelyWorker(it);
}

/**
//Helps printRecursively with the recursive calls
*/
void WordDataDLinkList::printRecursivelyWorker(DListItr<WordData> it)
{	if(it.isLastNode()) //Check if iterator is on last node
	{	cout<<" " << *it << endl;
		return; //Stop recursion, go back
	}
	cout << " " << *it << endl;
	printRecursivelyWorker(++it);
	
}

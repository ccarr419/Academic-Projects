/*
// Author:	Christian Carreras
// Course:	CSC 237
// File:	testll.cpp
// Purpose:	Fully tests the DLinkedList class by letting the user
//		freely insert/remove integers and use the data members
//		to print the list, check if the list is empty, and find
//		the first/node in the list
*/
#include<iostream>
#include "DLinkedList.h"
#include "Node.h"
using namespace std;

/*
// Function Name:	menu	
// Parameters:		none
// Returns:		void
// Purpose:		displays the menu for the user to see
*/
void menu();

/*
// Function Name:	options
// Parameters:		DLinkedList<int>& - import only
// Returns:		int - user's choice (exit or not)
// Purpose:		Creates the interface for the user
*/
int options(DLinkedList<int>&);

/*
// Function Name:	insertIntoList
// Parameters:		DLinkedList<int>& - import only
// Returns:		void
// Purpose:		Asks user for an integer and inserts it into the list
*/
void insertIntoList(DLinkedList<int>&);

/*
// Function Name:	removeFromList
// Parameters:		DLinkedList<int>& - import only
// Returns:		void
// Purpose:		Asks user for an integer and removes that integer if
//			it is found in the list. Tells user if successful
*/
void removeFromList(DLinkedList<int>&);

/*
// Function Name:	checkEmpty
// Parameters:		DLinkedList<int>& - import only
// Returns:		void
// Purpose:		Checks if the current is empty
*/
void checkEmpty(DLinkedList<int>&);

/*
// Function Name:	findFirst
// Parameters:		DLinkedList<int>& - import only
// Returns:		void
// Purpose:		Finds the first node in the list
*/
void findFirst(DLinkedList<int>&);

/*
// Function Name:	findLast
// Parameters:		DLinkedList<int>& - import only
// Returns:		void
// Purpose:		Finds the last node in the list
*/
void findLast(DLinkedList<int>&);

/*
// Function Name:	printListForward
// Parameters:		DLinkedList<int>& - import only
// Returns:		void
// Purpose:		Prints list first-last
*/
void printListForward(DLinkedList<int>&);

/*
// Function Name:	printListBackward
// Parameters:		DLinkedList<int>& - import only
// Returns:		void
// Purpose:		Prints list last-first
*/
void printListBackward(DLinkedList<int>&);

int main()
{	DLinkedList<int> theList;
	char num = '0';
	while(num != '8') //Exit selected or not
	{	menu();
		num = options(theList);
	}
	cout << "\nProgram Session Terminated\n\n";
	return 0;
}

/*
//Displays the menu for the user to see
*/
void menu()
{	cout << "\nDOUBLE LINKED LIST TEST PROGRAM\n";
	cout << "1. Insert Into List\n";
	cout << "2. Remove From List\n";
	cout << "3. Check If List Is Empty\n";
	cout << "4. Find First Node\n";
	cout << "5. Find Last Node\n";
	cout << "6. Display List Forwards\n";
	cout << "7. Display List Backwards\n";
	cout << "8. Exit\n";
}

/*
//Creates the interface for the user to:
//*Insert into list
//*Remove from list
//*Check if list is empty
//*Find the first node
//*Find the last node
//*Print list forwards
//*Print list backwards
*/
int options(DLinkedList<int>&l)
{	char choice;
	cout << "\nPlease enter your choice: ";
	cin >> choice;
	switch(choice)
	{	case '1': //Insert
			insertIntoList(l);
			break;
		case '2': //Remove
			removeFromList(l);
			break;
		case '3': //Check if list is empty
			checkEmpty(l);
			break;
		case '4': //Find first node
			findFirst(l);
			break;
		case '5': //Find last node
			findLast(l);
			break;
		case '6': //Print first-last
			printListForward(l);
			break;
		case '7': //Print last-first
			printListBackward(l);
			break;
		case '8': //Exit
			cout << "Goodbye\n";
			break;
		default: //Error-catch
			cout << "\nNot a valid choice\n";
			break;
	}
	return choice;
}

/*
//Asks user for an integer to insert into list
*/
void insertIntoList(DLinkedList<int>&l)
{	int num;
	cout << "\nPlease enter an integer to insert: ";
	cin >> num;
	if(l.insert(num)) //Display current list
		printListForward(l);
	else
		cout << "Error inserting into list\n";
}

/*
//Asks user for an integer to remove from the list
//Tells user if the number wasn't in the list
*/
void removeFromList(DLinkedList<int>&l)
{	int num;
	cout << "\nPlease enter an integer to remove: ";
	cin >> num;
	if(l.remove(num)) //Display current list
		printListForward(l);
	else
		cout << "Number was not found\n";
}

/*
//Checks if head == NULL (list is empty)
*/
void checkEmpty(DLinkedList<int>&l)
{	DListItr<int> it(l);
	if(it.isEmpty())
		cout << "\nThe list is empty\n";
	else
		cout << "\nThe list is not empty\n";
}

/*
//Find what head is pointing to (first node) and print to screen
*/
void findFirst(DLinkedList<int>&l)
{	DListItr<int> it(l);
	while(!(it.isFirstNode()))
		++it;
	cout << "\nThe first in the list is " << *it << endl;
}

/*
//Find last node in the list and print to screen
*/
void findLast(DLinkedList<int>&l)
{	DListItr<int> it(l);
	while(!(it.isLastNode()))
		++it;
	cout << "\nThe last in the list is " << *it << endl;
}

/*
//Print the current list first node to last node
*/
void printListForward(DLinkedList<int>&l)
{	cout << "\nCurrent List: ";
	for(DListItr<int> it(l); !(it.isNull()); ++it)
		cout << *it << " ";
	cout << endl;
}

/*
//Print current list last node to first node
*/
void printListBackward(DLinkedList<int>&l)
{	DListItr<int> it(l);
	cout << "\nCurrent List: ";
	for( ; !(it.isNull()); ++it) //Go to last node
		if(it.isLastNode()) break;
	for( ; !(it.isNull()); --it) //Then print backwards
		cout << *it << " ";
	cout << endl;
}

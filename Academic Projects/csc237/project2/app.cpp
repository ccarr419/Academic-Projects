/*
// Author:	Christian Carreras 	        
//		(with thanks to Dr. Spiegel & Adam Tal)
// Course:	CSC 237
// Filename:	app.cpp
// Purpose:	This Example inputs a string and demon-
//		strates how to store it using a subclass
//		of an abstract base class that incorporates
//		virtual functions to enable polymorphism
//		If a file name is input through the command
//		line all of the options will be done  
//		automatically
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include "WordList.h"
#include "WordDataList.h"
#include "WordDataDLinkList.h"
#include "DLinkedList.h"

using namespace std;

/*
// Function Name: 	displayMenu
// Parameters:		none
// Returns:		void
// Purpose: 		Displays the menu on the screen
*/
void displayMenu();

/*
// Function Name: 	printEverything
// Parameters:  	ifstream& - import/export - handle for data file
// 			WordDataList* - export only
// Returns:		void
// Purpose: 		Takes in a file and sends it through every
//              	parsing and printing function
*/
void printEverything(ifstream &inf, WordList *TheList, string);

/*
// Function Name:	getFile
// Parameters:		ifstream& - import/export
//			string - import only
// Returns:		true if the file was found and opened
//			false if the file was not found
//			or failed to open
// Purpose:		Tries to open a file and returns whether
//			it was opened or not
*/
bool getFile(ifstream &, string);

/*
// Function Name:	chooseOption
// Parameters:		ifstream& - import/export
//			WordList* - import only
//			string - import only
// Returns:		void
// Purpose:		Creates an interface for the user to
//			choose what he/she wants to do
*/
void chooseOption(ifstream &inf, WordList *TheList, string);

int main(int argc,char *argv[])
{ 	ifstream inf;
	WordList *TheList;
	if(argc>1) //if there was an input on the command line
	{
		inf.open(argv[1]); //try and open the file
		if (inf.fail())       //if the file does not open
		{                    //terminate
			cout<<"Sorry, the file failed to open."<<endl;
			return 0;
		}
		string file = argv[1];
		printEverything(inf ,TheList,file);
		return 0;
	}

	string fileName;
	cout<<"Please enter a file name: ";
	getline(cin,fileName);
	if(getFile(inf, fileName)) //If the file was found	
		chooseOption(inf, TheList, fileName); //Go to the interface
	else //If the file was not found
		cout << "File not found.\n";

	return 0;
}

/*
// Displays menu to screen
*/
void displayMenu()
{
	cout<<endl;
	cout<<"How do you want to print your sentence elements?"<<endl;
	cout<<"------------------------------------------------"<<endl;
	cout<<"1. Object Array Iterative"<<endl;
	cout<<"2. Object Array Recursive"<<endl;
	cout<<"3. Object Array Pointer Recursive"<<endl;
	cout<<"4. Double Linked List Iterative"<<endl;
	cout<<"5. Double Linked List Recursive"<<endl;
	cout<<"6. Quit"<<endl;
}

/*
// Prints every option if command line is used
*/
void printEverything(ifstream &inf, WordList *TheList, string file)
{ 	TheList = new WordDataList; //Point TheList to a WordDataList
	TheList->parseIntoList(inf);
	TheList->printIteratively();
	TheList->printRecursively();
	TheList->printPtrRecursively();
	free(TheList); //Reclaim memory
	
	inf.close(); //Reload the file
	inf.open(file.c_str());
	
	TheList = new WordDataDLinkList;//Point TheList to a WordDataDlinkList
	TheList->parseIntoList(inf);
	TheList->printIteratively();
	TheList->printRecursively();
	free(TheList); //Reclaim memory
}

/*
//Attempt to open file and return a truth value on whether
//the file was able to be opened or not 
*/
bool getFile(ifstream &inf, string file)
{	inf.open(file.c_str()); //Attempt to open the file
	if(inf.fail()) //If the file doesn't exist
		return false;
	else //If the file exists
		return true;
}

/*
//The interface for the user:
//Uses a switch statment to let
//the user choose what he/she wants
*/
void chooseOption(ifstream &inf, WordList *TheList, string file)
{	char selection;
	int keepAlive = 1; //Keep interface open
	while (keepAlive)
	{	displayMenu(); //Open menu
		cout << "Please enter your choice: ";
		cin>>selection;
		switch(selection)
		{ 	case '1': //Print WordDataList Iteratively
				TheList = new WordDataList;
				TheList->parseIntoList(inf);
				TheList->printIteratively();
				break;
			case '2': //Print WordDataList Recursively
				TheList = new WordDataList;
				TheList->parseIntoList(inf);
				TheList->printRecursively();
				break;
			case '3': //Print WordDataList Ptr Recursively
				TheList = new WordDataList;
				TheList->parseIntoList(inf);
				TheList->printPtrRecursively();
				break;
			case '4': //Print WordDataDLinkList Iteratively
				TheList = new WordDataDLinkList;
				TheList->parseIntoList(inf);
				TheList->printIteratively();
				break;
			case '5': //Print WordDataDLinkList Recursively
				TheList = new WordDataDLinkList;
				TheList->parseIntoList(inf);
				TheList->printRecursively();
				break;
			case '6': //Exit
				cout << "Goodbye" << endl;
				keepAlive = 0;
				break;
			default: //Error-catch
				cout << "I cannot understand " << selection;
				cout << ".  Try again." << endl;
				break;
		}
		free(TheList); //Reclaim memory
		inf.close(); //Reload file
		getFile(inf, file);
	}
}

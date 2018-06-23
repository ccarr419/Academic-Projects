/**
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
//		This application also times each data structure's
//		method of printing to test for efficiency
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include "WordList.h"
#include "WordDataList.h"
#include "WordDataDLinkList.h"
#include "DLinkedList.h"
#include "WordDataSTList.h"

using namespace std::chrono;

/**
// Function Name: 	displayMenu
// Parameters:		none
// Returns:		void
// Purpose: 		Displays the menu on the screen
*/
void displayMenu();

/**
// Function Name: 	printEverything
// Parameters:  	ifstream& - import/export - handle for data file
// 			WordDataList* - export only
// Returns:		void
// Purpose: 		Takes in a file and sends it through every
//              	parsing and printing function
*/
void printEverything(ifstream &inf, WordList *TheList, string);

/**
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

/**
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
			std::cout<<"Sorry, the file failed to open."<<endl;
			return 0;
		}
		string file = argv[1];
		printEverything(inf ,TheList,file);
		return 0;
	}

	string fileName;
	std::cout << "Please enter a file name: ";
	getline(cin,fileName);
	if(getFile(inf, fileName)) //If the file was found	
		chooseOption(inf, TheList, fileName); //Go to the interface
	else //If the file was not found
		std::cout << "File not found.\n";

	return 0;
}

/**
// Displays menu to screen
*/
void displayMenu()
{
	std::cout << endl;
	std::cout << "How do you want to print your sentence elements?" << endl;
	std::cout << "------------------------------------------------" << endl;
	std::cout << "1. Object Array Iterative" << endl;
	std::cout << "2. Object Array Recursive" << endl;
	std::cout << "3. Object Array Pointer Recursive" << endl;
	std::cout << "4. STL List Iterative" << endl;
	std::cout << "5. STL List Recursive" << endl;
	std::cout << "6. Double Linked List Iterative" << endl;
	std::cout << "7. Double Linked List Recursive" << endl;
	std::cout << "8. Quit" << endl;
}

/**
// Prints every option if command line is used
*/
void printEverything(ifstream &inf, WordList *TheList, string file)
{ 	TheList = new WordDataList; //Point TheList to a WordDataList
	TheList->parseIntoList(inf);
	
	//Find fucntion time for Array list iterative print
	auto begin = high_resolution_clock::now(); //Start time
	TheList->printIteratively();
	auto end = high_resolution_clock::now(); //End time
	auto ticks = duration_cast<microseconds>(end-begin); //Difference
	//Display the time it took to complete function
	std::cout << "That took " << ticks.count() << " microseconds\n\n";
	
	//Find function time of Array list recursive print
	begin = high_resolution_clock::now();
	TheList->printRecursively();
	end = high_resolution_clock::now();
	ticks = duration_cast<microseconds>(end-begin);
	std::cout << "That took " << ticks.count() << " microseconds\n\n";
	
	//Find function time of Array list recursive pointer print
	begin = high_resolution_clock::now();
	TheList->printPtrRecursively();
	end = high_resolution_clock::now();
	ticks = duration_cast<microseconds>(end-begin);
	std::cout << "That took " << ticks.count() << " microseconds\n\n";
	
	free(TheList); //Reclaim memory	
	inf.close(); //Reload the file
	inf.open(file.c_str());
	
	TheList = new WordDataSTList;//Point TheList to a WordDataSTList
	TheList->parseIntoList(inf);
	
	//Find function time for STL list iterative print
	begin = high_resolution_clock::now();
	TheList->printIteratively();
	end = high_resolution_clock::now();
	ticks = duration_cast<microseconds>(end-begin);
	std::cout << "That took " << ticks.count() << " microseconds\n\n";
	
	//Find function time for STL list recursive print
	begin = high_resolution_clock::now();
	TheList->printRecursively();
	end = high_resolution_clock::now();
	ticks = duration_cast<microseconds>(end-begin);
	std::cout << "That took " << ticks.count() << " microseconds\n\n";
	
	free(TheList); //Reclaim memory	
	inf.close(); //Reload the file
	inf.open(file.c_str());
	
	TheList = new WordDataDLinkList;//Point TheList to a WordDataDlinkList
	TheList->parseIntoList(inf);
	
	//Find function time for DLinkedList iterative print
	begin = high_resolution_clock::now();
	TheList->printIteratively();
	end = high_resolution_clock::now();
	ticks = duration_cast<microseconds>(end-begin);
	std::cout << "That took " << ticks.count() << " microseconds\n\n";
	
	//Find function time for DLinkedList recursive print
	begin = high_resolution_clock::now();
	TheList->printRecursively();
	end = high_resolution_clock::now();
	ticks = duration_cast<microseconds>(end-begin);
	std::cout << "That took " << ticks.count() << " microseconds\n\n";
	
	free(TheList); //Reclaim memory
}

/**
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

/**
//The interface for the user:
//Uses a switch statment to let
//the user choose what he/she wants
*/
void chooseOption(ifstream &inf, WordList *TheList, string file)
{	char selection;
	auto begin = high_resolution_clock::now(); //Start time
	auto end = high_resolution_clock::now(); //End time
	auto ticks = duration_cast<microseconds>(end-begin);
	int keepAlive = 1; //Keep interface open
	while (keepAlive)
	{	displayMenu(); //Open menu
		std::cout << "Please enter your choice: ";
		cin>>selection;
		switch(selection)
		{ 	case '1': //Print WordDataList Iteratively
				TheList = new WordDataList;
				TheList->parseIntoList(inf);	
				begin = high_resolution_clock::now(); //Start time
				TheList->printIteratively();		
				break;
			case '2': //Print WordDataList Recursively
				TheList = new WordDataList;
				begin = high_resolution_clock::now(); //Start time
				TheList->parseIntoList(inf);
				TheList->printRecursively();
				break;
			case '3': //Print WordDataList Ptr Recursively
				TheList = new WordDataList;
				TheList->parseIntoList(inf);
				begin = high_resolution_clock::now(); //Start time
				TheList->printPtrRecursively();
				break;
			case '4': //Print WordDataSTList Iteratively
				TheList = new WordDataSTList;
				TheList->parseIntoList(inf);
				begin = high_resolution_clock::now(); //Start time
				TheList->printIteratively();
				break;
			case '5': //Print WordDataSTList Recursively
				TheList = new WordDataSTList;
				TheList->parseIntoList(inf);
				begin = high_resolution_clock::now(); //Start time
				TheList->printRecursively();
				break;
			case '6': //Print WordDataDLinkList Iteratively
				TheList = new WordDataDLinkList;
				TheList->parseIntoList(inf);
				begin = high_resolution_clock::now(); //Start time
				TheList->printIteratively();
				break;
			case '7': //Print WordDataDLinkList Recursively
				TheList = new WordDataDLinkList;
				TheList->parseIntoList(inf);
				begin = high_resolution_clock::now(); //Start time
				TheList->printRecursively();
				break;
			case '8': //Exit
				std::cout << "Goodbye" << endl;
				keepAlive = 0;
				break;
			default: //Error-catch
				std::cout << "I cannot understand " << selection;
				std::cout << ".  Try again." << endl;
				break;
		}
		if(keepAlive) //If the user quits program
		{	end = high_resolution_clock::now(); //End time
			ticks = duration_cast<microseconds>(end-begin);
			std::cout << "That took " << ticks.count() << " microseconds\n";
		}
		free(TheList); //Reclaim memory
		inf.close(); //Reload file
		getFile(inf, file);
	}
}

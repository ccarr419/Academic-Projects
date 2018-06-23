/***************************************************************
Author:         Dr. Spiegel
Course:         CSC 136 020 
Assignment:     #3a
Due Date:       October 8, 2013
Filename:       Array_tst.cpp 
Purpose:        This program reads a file of Terms into an Array and then performs
		various operations on it, testing the Array and Term classes. You can 
		evaluate, multiply, add, and print the Terms contained in objects of this type 
***************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include "Array.h"
#include "term.h"

using namespace std;

bool openFile(ifstream &file, string &filename);//opens a file
void mainMenu(Array &TermList); 		//holds the main menu loop
// void getData(ifstream &file, Array &TermList); 	// loads Terms from the file 
ifstream &operator>>(ifstream &file, Array &TermList);	// Use operator instead
void evaluateTerm(Array &TermList); 		//evaluates a term for a supplied value
void multiplyTerm(Array &TermList); 		//multiplies a term by a supplied value
void addTerm(Array &TermList); 			//adds a term to the term list
bool checkQuit(); 				//checks if the user wants to quit or not

int main()
{
	//Declare variables
	ifstream file; //input file to ingest
	string filename; //name of the input file
	char userChoice; //holds the char the user enters to navigate menus
	Array TermList;
	
	//Get file to open from user
	cout << "\n\nWelcome to the Array of Term testing program!\n\n";
	cout << "Enter the file you would like to open:\n";
	cin >> filename; //store the filename for the file the user wants to use
	
	//Open the file and
	if (openFile(file,filename) == false) //If false, close the program
	{
		cout << "There was an error opening your file!\nQuiting now\n";
		return(0); //exit program
	}
	
	//Start to ingest the terms located in the file
	// getData(file, TermList);
	file >> TermList;
	
	//Enter main menu loop
	mainMenu(TermList);
	
	//Say goodbye and quit
	cout << "Goodbye!\n";
	
	return(0); //exit program
}

bool openFile(ifstream &file, string &filename)
{ /*********************************************************************
	*   Function name:  openFile
	*   Description:    Opens a file
	*   Parameters:    ifstream file - the file stream
	*                         string filename - the file name to open
	*                                                                   
	*   Return Value:  true if file opened correctly
							false if file opened incorrectly
	*********************************************************************/
	//Attempt to open file
	file.open(filename.c_str());
	return(file); //Check if opened correctly
}

//void getData(ifstream &file, Array &TermList)
ifstream &operator>>(ifstream &file, Array &TermList)
{	/*********************************************************************
	*   Function name:  getData
	*   Description:    Takes data from the file into a Term and appends it to TermList
	*   Parameters:     ifstream file - holds the file stream
	*		    Array TermList - is an Array of Term.
	*                                                                   
	*   Return Value: n/a
	*********************************************************************/
	Term aTerm;
	while (file >> aTerm)
		TermList.addTerm(aTerm);
	file.close();
	return(file);
}

void mainMenu(Array &TermList)
{	/*********************************************************************
	*   Function name:  mainMenu
	*   Description:    Prints the main menu and executes functions
	*   Parameters:   char userChoice - hold the input character for the menu
	*						 Term term - holds the Term object and the term data
	*                                                                   
	*   Return Value: n/a
	*********************************************************************/
	char userChoice;
	//enter menu loop
	while (userChoice != 'X')
	{
		//print menu choices
		cout << "The list of Terms is Presently: " << TermList << endl;
		cout << "\nChoose from the following:\n\n";
		cout << "E - Evaluate a term\nM - Multiply a term\nA - Add a term\n"
						<< "P - Print the List\nQ - Quit the program\n";
		cout << "*********************************\n";
		
		cin >> userChoice; 		//take in users choice
		userChoice=toupper(userChoice); // and upper case it
		
		//give the user what they want
		switch (userChoice)
		{
			case 'E':
				evaluateTerm(TermList); //evaluates the term
				break;
			case 'M':
				multiplyTerm(TermList); //multiplys the term by a number
				break;
			case 'A':
				addTerm(TermList); //adds a term to the existing TermList
				break;
			case 'P':
				cout << TermList << endl; //prints the TermList
				break;
			case 'Q':
				if (checkQuit()) //sees whether or not the user wants to quit
				  return;
				break;
			default:
				cout << "Invalid menu choice!!\n";
		}
	}
}

void evaluateTerm(Array &TermList)
{	/*********************************************************************
	*   Function name:  evaluateTerm
	*   Description:    Asks for x and and index and evaluates the requested Term
	*   Parameters:     Array &TermList - is the list of Terms
	*                                                                   
	*   Return Value: n/a
	*********************************************************************/
	// Input x and which Term, and print the result of evaluating that one Term
	double x; //x= value to evaluate the term with.
	double termNum = 0;
	cout << "\nPlease enter a value for x: ";
	cin >> x;
	for(int i = 0; i < TermList.getElements(); i++)
		termNum += TermList[i](x);
	cout << termNum << endl << endl;
}

void multiplyTerm(Array &TermList) 
{	/*********************************************************************
	*   Function name:  multiplyTerm
	*   Description:    Asks for a scalar and index and multiplies the term 
				at the given index by the scalar
	*   Parameters:     Array &TermList - is the list of Terms
	*                                                                   
	*   Return Value: n/a
	*********************************************************************/
	// Input the factor and which Term, and print the result of multiplying that one Term
	double factor; //holds the amount the user wants to multiply by
	double termNum = 0;
	cout << "\nPlease enter a factor to multiply by: ";
	cin >> factor;
	for(int i = 0; i < TermList.getElements(); i++)
		TermList[i]*=factor;
	cout << endl;
}

void addTerm(Array &TermList)
{	/*********************************************************************
	*   Function name:  addTerm
	*   Description:   Adds a term to the term
	*   Parameters:   Term term - is the poly object being evaluated
	*                                                                   
	*   Return Value: n/a
	*********************************************************************/
	//Declare local variables
	//Term newTerm;
	double coeff; //holds the desired coefficient to add
	int expn; //holds the desired exponent to add
	
	cout << "\nEnter the coefficient of the term you wish to add:\n";
	cin >> coeff; //store the value in coeff
	cout << "Enter the exponent of the term you wish to add:\n";
	cin >> expn; //stores the value in expn
	cout << endl;
	TermList.addTerm(coeff, expn);
}

bool checkQuit()
{	/*********************************************************************
	*   Function name:  checkQuit
	*   Description:   Checks if the user wants to actually quit or not
	*   Parameters:   char userChoice - holds what the user wants to do in the menu
	*                                                                   
	*   Return Value: n/a
	*********************************************************************/
	char userChoice;
	cout << "Do you really want to quit?  (y/n)\n"; //askes if the user really wants to quit
	cin >> userChoice; //store value in userChoice
	return (toupper(userChoice)=='Y');
}


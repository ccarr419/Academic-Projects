/**
// Author:	Christian Carreras
// File:	WordInfo.h
// Purpose:	Header file for the WordInfo class.
//		This file creates the WordInfo class.
//		The WordInfo class consists of private members
//		word, which is string and count which is an int but
//		also counts the # of times the word appears.
//		The class also has public member functions such
//		as sets, gets and an overloaded operator.
//		The class also contains associative operators.
*/

#ifndef WORDINFO_H
#define WORDINFO_H
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class WordInfo {

public:

	//Constructor
	WordInfo(string wrd = "", int cnt = 0);

	///////
	//Sets
	///////
	
	/**
	// Function: 	setWord
	// Parameters:	string - import only
	// Returns:	void
	// Member Type:	Mutator
	// Purpose:	Sets the value for the private member word
	*/
	void setWord(string);
	
	/**
	// Function:	setCount
	// Parameters:	int - import only
	// Returns:	void
	// Member Type:	Mutator
	// Purpose:	Sets the value for the private member count
	*/
	void setCount(int);
	
	///////
	//Gets
	///////
	
	/**
	// Function:	getWord
	// Parameters:	none
	// Returns:	string
	// Member Type:	Inspector
	// Purpose:	Returns the value of the private member word
	*/
	string getWord() const;
	
	/**
	// Function:	getCount
	// Parameters: 	none
	// Returns:	int
	// Purpose:	Returns the value of the private member count
	*/
	int getCount() const;
	
	/**
	// Function:	++ operator
	// Parameters:	int (post-increment)
	// Returns:	void
	// Purpose:	increments count
	*/
	void operator++(int);
	
private:
	string word;
	int count;
};

//Associate operators

/**
// Function:	>> operator
// Parameters:	ifstream& - import/export
//		WordInfo& - import/export
// Returns:	ifstream
// Purpose:	Extract data from file directly
//		into class
*/
ifstream &operator>>(ifstream &, WordInfo &);

/**
// Function:	<< operator
// Parameters:	ostream& - import/export
//		WordInfo - import only
// Returns:	ostream
// Purpose:	prints the class to screen
*/
ostream &operator<<(ostream &, const WordInfo &);

#endif

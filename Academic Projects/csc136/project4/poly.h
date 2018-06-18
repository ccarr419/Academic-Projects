/* 
Filename:	poly.h
Author: 	Dr. Spiegel
Updated By:	Christian Carreras
Course:		CSC136
Assignment:	Project 4
Description:	Definition of the Polynomial Class
		This class provides the user the functionality of a polynomial, including
		the ability to add terms, evaluate, and multiply the coefficients.
		It also provides basic get and set functionalities.
		A function is provided to read terms from a file, and two associated 
		non-member, non-friend stream operators are present for reading a Term 
		and outputting the Polynomial in its entirety.
*/
#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <string>
#include "LinkedList.h"
#include "term.h"

using namespace std;

class Polynomial
{
public:
  
//////
// Constructor
//////

Polynomial();

/*
Function:	setTermList
Member Type:	Mutator
Description:	Makes TermList equal to another LinkedList
Parameters:	const LinkedList<Term>	- input - list to be set equal to
Returns:	bool
*/
bool setTermList(const LinkedList<Term>&);

/*
Function:	getTermList
Member Type:	Inspector
Description:	Returns the LinkedList private member
Parameters:	none
Returns:	TermList - LinkedList object
*/
const LinkedList<Term> getTermList() const;

/*
Function: 	operator ()
Member Type:	Facilitator
Description: 	Evaluate the polynomial for variable x
Parameters: 	x  - input - variable that is standing for value of x
Returns:      	The polynomial evaluated for x
*/
double operator()(double x) const;
  
/*
Function: 	multiply
Member Type:	Mutator
Description: 	Multiply each coefficient by the scalar arg factor
Parameters: 	fact  - input - variable that is multiplying against all the coefficents
Returns:      	void
*/
void operator *=(float factor);
  
/*
Function: 	add
Member Type:	Mutator
Description: 	Add a term to the polynomial
Parameters: 	coefficent  - input - the coefficent of the term being added
		exponent    - input - the exponent of the term being added
Returns:      	true if the term is added, false otherwise
*/
bool add(float coefficient, int exponent);

/*
Function: 	add
Member Type:	Mutator
Description: 	Add a term to the polynomial
Parameters: 	T  - input - the Term being added
Returns:      	true if the term is added, false otherwise
*/
bool add(Term &T);  
  
/*
Function: 	readFile
Member Type:	Mutator
Description: 	Loads up the terms from a user declared filename
Parameters: 	file - input/output - stream variable 
Returns:      	void
*/
void readFile(ifstream &file);

/*
Function:	removeTerm
Member Type:	Mutator
Description:	Checks if term is located within the LinkedList and if
		so removes the term from the LinkedList.
Parameters:	int	- input - term exponent to be removed
Returns:	bool	- true if term is found & removed
			- false if term is not found
*/
bool removeTerm(int);
 
private:

LinkedList<Term> TermList;

};


/*
Function: 	operator >>
Description: 	Reads in a Term from a file
Parameters: 	ifstream file	- input/output - the input stream
		Polynomial	- output only  - the Polynomial that will hold the data read in
Returns:      	ifstream 
*/
ifstream &operator >>(ifstream &file, const Polynomial&);

/*
Function: 	operator <<
Description: 	Print a Polynomial to the screen
Parameters: 	out - input/output - output stream
		P   - input        - The Polynomial to print
Returns:        void
*/
ostream &operator <<(ostream &out, const Polynomial &P);

#endif

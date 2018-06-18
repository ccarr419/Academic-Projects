
// Author: 		Dr. Spiegel
// Updated By:		Christian Carreras
// Course:		CSC136
// Assignment:		Project 2
// Filename:		poly.h
// Purpose:		Definition of the Polynomial Class
//			This class provides the user the functionality of a polynomial, including
//			the ability to add terms, evaluate, and multiply the coefficients.
//			It also provides basic set and get functionality.
//			A function is provided to read terms from a file, and two associated 
//			non-member, non-friend stream operators are present for reading a Term 
//			and outputting the Polynomial in its entirety.

#ifndef POLY_H
#define POLY_H

#include <iostream>
#include <string>
#include "Array.h"
#include "term.h"

using namespace std;

class Polynomial
{
 public:
  
  //////
  // Constructor
  //////

  
Polynomial();

  //////
  // Gets and Sets
  //////
  
  // Sets 

/*
Function: 	setTerm
Member Type:	Mutator
Description: 	Sets the term in the variable at a specific index
Parameters: 	int index	- input 	- the index at which the values are stored
		float co 	- input 	- the coefficient
		int ex 		- input 	- the exponent 
Returns:      	true if the value is set, false if not
*/ 
  bool setTerm(int index, float co, int ex);

/*
Function: 	setCoeff
Member Type:	Mutator
Description: 	Sets the coefficient for a term in the variable at a specific index
Parameters: 	int index	- input 	- the index at which the values are stored
		float co 	- input 	- the coefficient for the user
Returns:      	true if the value is set, false if not
*/ 
  bool setCoeff(int index, float co);

/*
Function: 	setExponent
Member Type:	Mutator
Description: 	Sets the exponent for the term in the variable at a specific index
Parameters: 	int index	- input 	- the index at which the values are stored
		int ex 		- input 	- the exponent for the user
Returns:      	true if the value is set, false if not
*/
  bool setExponent(int index, int ex);

  // Gets

/*
Function: 	getArray
Member Type:	Inspector
Description: 	Gives the user the Array object
Parameters: 	none
Returns:      	the Array object
*/
  Array& getArray();

/*
Function: 	getTerm
Member Type:	Inspector
Description: 	Gives the user the values associated with the terms at the index
Parameters: 	int index	- input - the index at which the values are stored
Returns:        The requested Term
Precondition:	index is an in use (active) index
*/
  Term getTerm(int index) const;

/*
Function: 	getCoeff
Member Type:	Inspector
Description: 	Gets the user the coefficient at a certain index
Parameters: 	int index	- input - the index at which the values are stored
Returns:        The requested coefficient
Precondition:	index is an in use (active) index
*/
  float getCoeff(int index) const;

/*
Function: 	getExponent
Member Type:	Inspector
Description:  	Gets the user the exponent for a certain index
Parameters: 	int index	- input - the index at which the values are stored
Returns:      	The requested exponent
Precondition:	index is an in use (active) index
*/
  int getExponent(int index) const;

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
 
 private:

Array A;

};


/*
Function: 	operator >>
Description: 	Reads in a Term from a file
Parameters: 	ifstream file	- input/output - the input stream
		Polynomial	- output only  - the Polynomial that will hold the data read in
Returns:      	ifstream 
*/
  ifstream &operator >>(ifstream &file, Polynomial&);

/*
Function: 	operator <<
Description: 	Print a Polynomial to the screen
Parameters: 	out - input/output - output stream
		P   - input        - The Polynomial to print
Returns:        void
*/
  ostream &operator <<(ostream &out, Polynomial &P);

#endif

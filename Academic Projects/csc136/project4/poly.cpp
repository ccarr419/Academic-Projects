/* 
Filename:	poly.cpp
Author: 	Christian Carreras
Course:		CSC136
Assignment:	Project 4
Description:	Creates the polynomial object with the constructor and
		with the help of member functions the user is allowed to
		update the poly by using Term functions as well as
		LinkedList functions.
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include "poly.h"
#include "LinkedList.h"
#include "term.h"
using namespace std;

//Constructor
Polynomial::Polynomial()
{
}

/*
Function:	setTermList
Member Type:	Mutator
Description:	Makes TermList equal to another LinkedList
Parameters:	const LinkedList<Term>	- input - list to be set equal to
Returns:	bool
*/
bool Polynomial::setTermList(const LinkedList<Term> &list)
{	TermList = list;
	return true;
}

/*
Function:	getTermList
Member Type:	Inspector
Description:	Returns the LinkedList private member
Parameters:	none
Returns:	TermList - LinkedList object
*/
const LinkedList<Term> Polynomial::getTermList() const
{	return TermList;
}

/*
Function: 	operator ()
Member Type:	Facilitator
Description: 	Evaluate the polynomial for variable x
Parameters: 	x  - input - variable that is standing for value of x
Returns:      	The polynomial evaluated for x
*/
double Polynomial::operator()(double x) const
{	double answer = 0;
	LinkedList<Term> newList = getTermList();
	listItr<Term> lt(newList);
	while ( lt.more() ) {
		Term newTerm = lt.value();
		//Multiply the coefficient by x^expn and add to total
		if(newTerm.getExponent() > 1)
			answer += (pow(x, newTerm.getExponent())*newTerm.getCoefficient());
		//Multiply the coefficient by x and add to total
		else if(newTerm.getExponent() == 1)
			answer += (x*newTerm.getCoefficient());
		//Add the coefficient to total
		else if(newTerm.getExponent() == 0)
			answer += newTerm.getCoefficient();
		lt.next();
	}
	return answer;
}

/*
Function: 	multiply
Member Type:	Facilitator
Description: 	Multiply each coefficient by the scalar arg factor
Parameters: 	fact  - input - variable that is multiplying against all the coefficients
Returns:      	void
*/
void Polynomial::operator*=(float factor)
{	LinkedList<Term> newList = getTermList();
	listItr<Term> lt(newList);
	while ( lt.more() ) {
		Term newTerm = lt.value();
		float coeff = newTerm.getCoefficient();
		coeff *= factor;
		newTerm.setCoefficient(coeff);
		lt.value() = newTerm;
		lt.next();
	}
	setTermList(newList);
}

/*
Function: 	add
Member Type:	Mutator
Description: 	Add a term to the polynomial
Parameters: 	coefficient  - input - the coefficient of the term being added
		exponent     - input - the exponent of the term being added
Returns:      	true if the term is added, false otherwise
*/
bool Polynomial::add(float co, int ex)
{	Term newTerm;
	newTerm.setCoefficient(co);
	newTerm.setExponent(ex);
	return(add(newTerm));
}

/*
Function:       add
Member Type:	Inspector
Description:    Add a term to the polynomial
Parameters:     T  - input - the Term being added
Returns:        true if the term is added, false otherwise
*/
bool Polynomial::add(Term &T)
{	TermList.orderedInsert(T);
	return true;
}

/*
Function:       readFile
Member Type:	Mutator
Description:    Loads up the terms from a user declared filename
Parameters:     file& - input/output - stream variable
Returns:        void
*/
void  Polynomial::readFile(ifstream &file)
{	Term T;
	while(file >> T)
		add(T);
	file.close();
}

/*
Function:	removeTerm
Member Type:	Mutator
Description:	Checks if term is located within the LinkedList and if
		so removes the term from the LinkedList.
Parameters:	int	- input - term exponent to be removed
Returns:	bool	- true if term is found & removed
			- false if term is not found
*/
bool Polynomial::removeTerm(int expn)
{	Term newTerm;
	newTerm.setExponent(expn);
	if(TermList.remove(newTerm))
		return true;
	else
		return false;
}

/*
Function:       operator >>
Description:    Reads in a Term from a file
Parameters:     ifstream file   - input/output - the input stream
                Polynomial      - output only  - Poly to data input
Returns:        ifstream
*/
ifstream &operator >>(ifstream &file, const Polynomial&P)
{	Term newTerm;
	file >> newTerm;
	LinkedList<Term> newList = P.getTermList();
	newList.orderedInsert(newTerm);
	return file;
}

/*
Function: 	operator <<
Description: 	Print a Polynomial to the screen
Parameters: 	out - input/output - output stream
		P   - input        - The Polynomial to print
Returns:        void
*/
ostream &operator <<(ostream &out, const Polynomial &P)
{	LinkedList<Term> newList = P.getTermList();
	listItr<Term> lt(newList);
	while ( lt.more() ) {
		out << lt.value();
		lt.next();
		if(lt.more())
			out << " + ";
	}
	return out;
}

/*
File: 		term.cpp
Author: 	Christian Carreras
Course:		CSC136
Assignment:	Project 4
Description:	Creates term objects that can be used
		to store inside a polynomial object.
		The term is self-contained and self-reliant
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "term.h"

using namespace std;

//////////////
//Constructor
//////////////
/*
Function:	setCoefficient
Member Type:	Mutator
Description:	Sets the coefficient in the term
Parameters:	float	- input - coefficient to put in the term
Returns:	true if value is set, false if not
*/
Term::Term(float coeff, int expn) 
{	setTerm(coeff, expn); }

///////////
//Sets
///////////
/*
Function:	setExponent
Member Type:	Mutator
Description:	Sets the exponent in the term
Parameters:	int	- input - exponent to put in the term
Returns:	true if value is set, false if not
*/
bool Term::setTerm(float co, int ex)
{	coefficient = co;
	exponent = ex;
	return true;
}

/*
Function:	setCoefficient
Member Type:	Mutator
Description:	Sets the coefficient in the term
Parameters:	float	- input - coefficient to put in the term
Returns:	true if value is set, false if not
*/
bool Term::setCoefficient(float co)
{	return(coefficient = co); }

/*
Function:	setExponent
Member Type:	Mutator
Description:	Sets the exponent in the term
Parameters:	int	- input - exponent to put in the term
Returns:	true if value is set, false if not
*/
bool Term::setExponent(int ex)
{	return(exponent = ex); }

///////////
//Gets
///////////
/*
Function:	getCoefficient
Member Type:	Inspector
Description:	Returns the coefficient value of the term
Parameters:	none
Returns:	float	- coefficient
*/
float Term::getCoefficient() const
{	return coefficient; }

/*
Function:	getExponent
Member Type:	Inspector
Description:	Returns the exponent value of the term
Parameters:	none
Returns:	int	- exponent
*/
int Term::getExponent() const
{	return exponent; }

////////////////////////
//Member Operators
////////////////////////
/*
Function:	*= operator
Member Type:	Mutator
Description:	Multiplies term coefficient by a factor
Parameters:	double	- factor to multiply by
Returns:	void
*/
void Term::operator*=(double factor)
{	setCoefficient(getCoefficient()*factor); }

/*
Function:	() operator
Member Type:	Facilitator
Description:	Evaluates the term for the given factor
Parameters:	double	- input - factor to evaluate the term by
Returns:	double	- the term evaluated
*/
double Term::operator()(double x) const
{ 	double answer;	
	answer = pow(x, getExponent())*getCoefficient();
	return answer;
}

/*
Function:	== operator
Member Type:	Facilitator
Description:	Checks if the exponent of a term is equal
		to the given integer
Parameters:	Term	- input - number to check if equal to
Returns:	true if the exponent is equal, false if not
*/
bool Term::operator==(Term x) const
{	if(getExponent() == x.getExponent())
		return true;
	else
		return false;
}

/*
Function:	!= operator
Member Type:	Facilitator
Description:	Checks if the the exponent of term is not
		equal to the given integer
Parameters:	Term	- input - number to check not equal to
Returns:	true if not equal, false if equal
*/
bool Term::operator!=(Term x) const
{	if(getExponent() != x.getExponent())
		return true;
	else
		return false;
}

/*
Function:	> operator
Member Type:	Facilitator
Description:	Checks if the Term is greater than a given Term
Parameters:	Term&	- input - Term to check if greater than Term
Returns:	true if the term is greater than the other term, false if not
*/
bool Term::operator>(const Term &T) const
{	if(getExponent() > T.getExponent())
		return true;
	else
		return false;
}

/*
Function:	< operator
Member Type:	Facilitator
Description:	Checks if the Term is less than a given Term
Parameters:	Term&	- input - Term to check if greater than Term
Returns:	true if the term is less than the other term, false if not
*/
bool Term::operator<(const Term &T) const
{	if(getExponent() < T.getExponent())
		return true;
	else
		return false;
}

/*
Function:	+= operator
Member Type:	Mutator
Description:	Combines common terms
Parameters:	Term&	- input - Term to add to another term
Returns:	bool
*/
bool Term::operator+=(const Term &T)
{	setCoefficient(getCoefficient()+T.getCoefficient());
	return true;
}

///////////////////////////
//Associated Operators
///////////////////////////
/*
Function:	>> operator
Description:	Takes input and places it inside the term's
		coefficient and exponent.
		Enables cin << Term
Parameters:	ifstream&	- input stream
		Term&		- The Term from user-input
Returns:	ifstream
*/
ifstream &operator>>(ifstream &input, Term &T)
{	float coeff;
	int expn;
	input >> coeff >> expn;
	T.setCoefficient(coeff);
	T.setExponent(expn);
	return input;
}

/*
Function:	<< operator
Description:	Outputs the Term in correct polynomial form
		Enables cout << Term
Parameters:	ostream&	- the output stream
		const Term&	- the Term to ouput
Returns:	ostream
*/
ostream &operator<<(ostream &out, const Term &T)
{	//When the coefficient and exponent are greater than 1
	if(T.getCoefficient() > 1 && T.getExponent() > 1)
		out << T.getCoefficient() << "x^" << T.getExponent();
		
	//When the coefficient is equal to 1 but the exponent is greater than 1
	else if(T.getCoefficient() == 1 && T.getExponent() > 1)
		out << "x^" << T.getExponent();

	//When the coefficient > 1 and the exponent = 1
	else if(T.getCoefficient() > 1 && T.getExponent() == 1)
		out << T.getCoefficient() << "x";

	//When both the coefficient and the exponent are equal to one
	else if(T.getCoefficient() == 1 && T.getExponent() == 1)
		out << "x";

	//When the the exponent is zero
	else if(T.getExponent() == 0)
		out << T.getCoefficient();
		
	//When the coefficient is 0
	else if(T.getCoefficient() == 0)
		out << "";
			
	return out;
}

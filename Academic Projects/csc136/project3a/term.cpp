//File: 	term.cpp
//Author: 	Christian Carreras
//Description:	Term class code and implication
//		which is to be used by the Array class
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "term.h"

using namespace std;

//Constructor
Term::Term(float coeff, int expn) 
{	setTerm(coeff, expn); }

///////////
//Sets
///////////
bool Term::setTerm(float co, int ex)
{	coefficient = co;
	exponent = ex;
	return true;
}

bool Term::setCoefficient(float co)
{	return(coefficient = co); }

bool Term::setExponent(int ex)
{	return(exponent = ex); }

///////////
//Gets
///////////
float Term::getCoefficient() const
{	return coefficient; }

int Term::getExponent() const
{	return exponent; }

////////////////////////
//Member Operators
////////////////////////

//Multiply Term by factor
void Term::operator*=(double factor)
{	setCoefficient(getCoefficient()*factor); }

//Evaluate Term for x
double Term::operator()(double x) const
{ 	double answer;	
	answer = pow(x, getExponent())*getCoefficient();
	return answer;
}

//Checks if Terms matches an int
bool Term::operator==(int x) const
{	if(getExponent() == x)
		return true;
	else
		return false;
}

//Checks if a Term is less than another Term
bool Term::operator<(const Term &T) const
{	if(getExponent() < T.getExponent())
		return true;
	else
		return false;
}

///////////////////////////
//Associated Operators
///////////////////////////

//Read input into Term
ifstream &operator>>(ifstream &input, Term &T)
{	float coeff;
	int expn;
	input >> coeff >> expn;
	T.setCoefficient(coeff);
	T.setExponent(expn);
	return input;
}

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

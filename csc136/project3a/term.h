//File:		term.h
//Author:	Christian Carreras
//Description:	Term class that contains a coefficient
//		and exponent which is used by the Array class
#ifndef TERM_H
#define TERM_H

#include <iostream>

using namespace std;

class Term {

public:

Term(float coeff = 0, int expn = 0);	//Default constructor

//Sets
bool setTerm(float coeff, int expn);	//Set the Term
bool setCoefficient(float coeff);	//Set the Term's coefficient
bool setExponent(int expn);		//Set the Term's exponent

//Gets
float getCoefficient() const;		//Return coefficient
int getExponent() const;		//Return exponent

//Operators
void operator *=(double);		//Multiplies coefficient by factor
double operator ()(double) const;	//Evaluates Term for x
bool operator ==(int) const;		//Compares Terms
bool operator <(const Term &) const;

private:

float coefficient;
int exponent;

};

ifstream &operator>>( ifstream &, Term & );
ostream &operator<<( ostream &, const Term & );

#endif

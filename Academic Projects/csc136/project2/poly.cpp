#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include "poly.h"
using namespace std;

//Constructor
Polynomial::Polynomial(int s)
{	setSize(s); }

//////////
//SETS
/////////

/*
Function: 		setTerm
Member Type:	Mutator
Description: 	Sets the term in the variable at a specific index
Parameters: 	int index	- input 	- the index at which the values are stored
				float co 	- input 	- the coefficient
				int ex 		- input 	- the exponent 
Returns:      	true if the value is set, false if not
*/ 
bool Polynomial::setTerm(int index, float co, int ex)
{	termList[index].coeff = co;
	termList[index].expn = ex;
	return true;
}

/*
Function: 		setCoeff
Member Type:	Mutator
Description: 	Sets the coefficient for a term in the variable at a specific index
Parameters: 	int index	- input 	- the index at which the values are stored
				float co 	- input 	- the coefficient for the user
Returns:      	true if the value is set, false if not
*/ 
bool Polynomial::setCoeff(int index, float co)
{	return(termList[index].coeff = co);
}

/*
Function: 		setExponent
Member Type:	Mutator
Description: 	Sets the exponent for the term in the variable at a specific index
Parameters: 	int index	- input 	- the index at which the values are stored
				int ex 		- input 	- the exponent for the user
Returns:      	true if the value is set, false if not
*/
bool Polynomial::setExponent(int index, int ex)
{	return(termList[index].expn = ex);
}

//////////
//GETS
/////////

/*
Function: 		getTerm
Member Type:	Inspector
Description: 	Gives the user the values associated with the terms at the index
Parameters: 	int index	- input - the index at which the values are stored
Returns:        The requested Term
Precondition:	index is an in use (active) index
*/
Term Polynomial::getTerm(int index) const
{	return termList[index];
}

/*
Function: 		getSize
Member Type:	Inspector
Description: 	Furnishes the number of Terms in the Polynomial
Parameters: 	none
Returns:        the number of Terms in the Polynomial
*/
int Polynomial::getSize() const
{	return size;
}

/*
Function: 		getCoeff
Member Type:	Inspector
Description: 	Gets the user the coefficient at a certain index
Parameters: 	int index	- input - the index at which the values are stored
Returns:        The requested coefficient
Precondition:	index is an in use (active) index
*/
float Polynomial::getCoeff(int index) const
{	return termList[index].coeff;
}

/*
Function: 		getExponent
Member Type:	Inspector
Description:  	Gets the user the exponent for a certain index
Parameters: 	int index	- input - the index at which the values are stored
Returns:      	The requested exponent
Precondition:	index is an in use (active) index
*/
int Polynomial::getExponent(int index) const
{	return termList[index].expn;
}

/*
Function: 		operator ()
Member Type:	Facilitator
Description: 	Evaluate the polynomial for variable x
Parameters: 	x  - input - variable that is standing for value of x
Returns:      	The polynomial evaluated for x
*/
double Polynomial::operator()(double x) const
{	double answer;
	for(int i = 0; i < getSize(); i++)
		{	//Multiply the coefficient by x^expn and add to total
			if(getExponent(i) > 1)
				answer = answer+(pow(x, getExponent(i))*getCoeff(i));
			//Multiply the coefficient by x and add to total
			else if(getExponent(i) == 1)
				answer = answer+(x*getCoeff(i));
			//Add the coefficient to total
			else if(getExponent(i) == 0)
				answer += getCoeff(i);
		}
	return answer;
}

/*
Function: 		multiply
Member Type:	Facilitator
Description: 	Multiply each coefficient by the scalar arg factor
Parameters: 	fact  - input - variable that is multiplying against all the coefficients
Returns:      	void
*/
void Polynomial::operator*=(float factor)
{	for(int i = 0; i < getSize(); i++)
		setCoeff(i, termList[i].coeff*factor);	
}

/*
Function: 		add
Member Type:	Mutator
Description: 	Add a term to the polynomial
Parameters: 	coefficient  - input - the coefficient of the term being added
				exponent     - input - the exponent of the term being added
Returns:      	true if the term is added, false otherwise
*/
bool Polynomial::add(float coefficient, int exponent)
{	//If size > 0, check for duplicate exponents
	if(getSize() > 0)
	{	for(int i = 0; i < getSize(); i++)
		{	//Add the coefficients together if exponents match
			if(exponent == getExponent(i))
			{	setCoeff(i, getCoeff(i)+coefficient);
				coefficient = 0;
			}
		}
	}
	//When the coefficient does not equal zero or the polynomial is full
	if(coefficient != 0 && getSize() < 10)
	{	setCoeff(getSize(), coefficient);
		setExponent(getSize(), exponent);
		sort(); // Sort the array every time a new term is added
		setSize(getSize()+1);} //Increment size
	return true;
}

/*
Function:       add
Member Type:	Inspector
Description:    Add a term to the polynomial
Parameters:     T  - input - the Term being added
Returns:        true if the term is added, false otherwise
*/
bool Polynomial::add(const Term &T)
{	return(add(T.coeff,T.expn));
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
Function: 		setSize
Member Type:	Mutator
Description: 	Sets the term in the variable at a specific index. Private because the application 
				programmer shouldn't be messing with this;  # terms is a function of adding terms.
Parameters: 	int s	- input	- the index of the last value in the term array
Returns:      	N/A
*/ 
void Polynomial::setSize(int s)
{	//Number of terms should be between 0 and 10, if not set size to 10
	size = (s >= 0 && s < 11) ? s : 10;
}

/*
Function:		sort
Member Type:	Facilitator
Description:	Organizes the polynomial from highest exponent to lowest.
Parameters:		none
Returns:		N/A
*/
void Polynomial::sort()
{	for(int spot = getSize(); spot > 0; spot--)
	{	int idxMax = spot;
		for(int idx = 0; idx < spot; idx++)
			if(termList[idxMax].expn > termList[idx].expn)
				idxMax = idx;
		if(idxMax != spot)
			swap(termList[idxMax], termList[spot]);
	}
}

/*
Function:		swap
Member Type:	Mutator
Description:	Works with sort() to organize the polynomial from highest exponent to lowest.
Parameters:		Term &x	- input - swap with Term y
				Term &y	- input - swap with Term x
Returns:		N/A
*/
void Polynomial::swap(Term &x, Term &y)
{	Term temp = x;
	x = y;
	y = temp;
}

/*
Function:       operator >>
Description:    Reads in a Term from a file
Parameters:     ifstream file   - input/output - the input stream
                Term T          - output only  - Term to data input 
Returns:        ifstream
*/
ifstream &operator >>(ifstream &file, Term &T)
{	file >> T.coeff >> T.expn;
	return file;
}

/*
Function: 		operator <<
Description: 	Print a Polynomial to the screen
Parameters: 	out - input/output - output stream
				P   - input        - The Polynomial to print
Returns:        void
*/
ostream &operator <<(ostream &out, const Polynomial &P)
{	for(int i = 0; i < P.getSize(); i++)
	{	//When the coefficient and exponent are greater than 1
		if(P.getCoeff(i) > 1 && P.getExponent(i) > 1)
		{	//If this is the last element in the polynomial
			if(i == P.getSize()-1)
				out << P.getCoeff(i) << "x^" << P.getExponent(i);
			else
				out << P.getCoeff(i) << "x^" << P.getExponent(i) << "+";
		}
		//When the coefficient is equal to 1 but the exponent is greater than 1
		else if(P.getCoeff(i) == 1 && P.getExponent(i) > 1)
		{	if(i == P.getSize()-1)
				out << "x^" << P.getExponent(i);
			else
				out << "x^" << P.getExponent(i) << "+";
		}
		//When the coefficient > 1 and the exponent = 1
		else if(P.getCoeff(i) > 1 && P.getExponent(i) == 1)
		{	if(i == P.getSize()-1)
				out << P.getCoeff(i) << "x";
			else
				out << P.getCoeff(i) << "x+";
		}
		//When both the coefficient and the exponent are equal to one
		else if(P.getCoeff(i) == 1 && P.getExponent(i) == 1)
		{	if(i == P.getSize()-1)
				out << "x";
			else
				out << "x+";
		}
		//When the the exponent is zero
		else if(P.getExponent(i) == 0)
			out << P.getCoeff(i);
		//When the coefficient is 0
		else if(P.getCoeff(i) == 0)
			out << "";		
	}
	return out;
}

/*
Function: 		operator <<
Description: 	Write the Polynomial to a File
Parameters: 	ofstream &out  - 	input/output - The output file stream
				const Polynomial &P	input	     - Polynomial to save
Returns:        ofstream - the output file stream
*/
ofstream &operator <<(ofstream &out, const Polynomial &P)
{	for(int i = 0; i < P.getSize(); i++)
		out << P.getCoeff(i) << " " << P.getExponent(i) << endl;
	return out;
}

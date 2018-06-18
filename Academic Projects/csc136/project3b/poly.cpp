#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include "poly.h"
#include "Array.h"
#include "term.h"
using namespace std;

//Constructor
Polynomial::Polynomial()
{
}

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
{	A[index].setCoefficient(co);
	A[index].setExponent(ex);
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
{	return(A[index].setCoefficient(co));
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
{	return(A[index].setExponent(ex));
}

//////////
//GETS
/////////

/*
Function: 	getArray
Member Type:	Inspector
Description: 	Gives the user the Array object
Parameters: 	none
Returns:      	the Array object
*/
Array& Polynomial::getArray()
{	return A;
}

/*
Function: 		getTerm
Member Type:	Inspector
Description: 	Gives the user the values associated with the terms at the index
Parameters: 	int index	- input - the index at which the values are stored
Returns:        The requested Term
Precondition:	index is an in use (active) index
*/
Term Polynomial::getTerm(int index) const
{	return A[index];
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
{	return A[index].getCoefficient();
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
{	return A[index].getExponent();
}

/*
Function: 		operator ()
Member Type:	Facilitator
Description: 	Evaluate the polynomial for variable x
Parameters: 	x  - input - variable that is standing for value of x
Returns:      	The polynomial evaluated for x
*/
double Polynomial::operator()(double x) const
{	double answer = 0;
	for(int i = 0; i < A.getElements(); i++)
		{	//Multiply the coefficient by x^expn and add to total
			if(getExponent(i) > 1)
				answer += (pow(x, getExponent(i))*getCoeff(i));
			//Multiply the coefficient by x and add to total
			else if(getExponent(i) == 1)
				answer += (x*getCoeff(i));
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
{	for(int i = 0; i < A.getElements(); i++)
		setCoeff(i, getCoeff(i)*factor);	
}

/*
Function: 		add
Member Type:	Mutator
Description: 	Add a term to the polynomial
Parameters: 	coefficient  - input - the coefficient of the term being added
				exponent     - input - the exponent of the term being added
Returns:      	true if the term is added, false otherwise
*/
bool Polynomial::add(float co, int ex)
{	return(A.addTerm(co, ex));
}

/*
Function:       add
Member Type:	Inspector
Description:    Add a term to the polynomial
Parameters:     T  - input - the Term being added
Returns:        true if the term is added, false otherwise
*/
bool Polynomial::add(Term &T)
{	return(A.addTerm(T));
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
Function:       operator >>
Description:    Reads in a Term from a file
Parameters:     ifstream file   - input/output - the input stream
                Polynomial      - output only  - Poly to data input
Returns:        ifstream
*/
ifstream &operator >>(ifstream &file, Polynomial&P)
{	Term newTerm;
	file >> newTerm;
	P.add(newTerm);
	return file;
}

/*
Function: 		operator <<
Description: 	Print a Polynomial to the screen
Parameters: 	out - input/output - output stream
				P   - input        - The Polynomial to print
Returns:        void
*/
ostream &operator <<(ostream &out, Polynomial &P)
{	out << P.getArray();
	return out;
}


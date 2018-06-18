/**
* Author:		Christian Carreras
* File Name:	fraction.cpp
* Purpose:
**/
#include "fraction.h"
#include <iostream>
#include <assert.h>
#include "primes.h"
#include <string>
#include <cmath>

/**
* Function Name:	Constructor
* Member Type:		Constructor
* Parameter(s):	int - import only (numerator)
*				int - import only (denominator)
* Return Value:	N/A
* Purpose:		Constructs fraction object from user given numerator
*				and denominator, default values for the numerator and
*				denominator are both one. Checks if fraction can be reduced
*				after numerator and denominator are set.
**/
fraction::fraction(int num, int den)
{	
	setFraction(num, den);
	checkReduce();
}

/**
* Function Name:	setNumerator
* Member Type:		Mutator
* Parameter(s):	int - import only
* Return Value:	void
* Purpose:		Sets the fraction's numerator value to the given int value
**/
void fraction::setNumerator(int num)
{	numerator = num; }

/**
* Function Name:	setDenominator	
* Member Type:		Mutator
* Parameter(s):	int - import only
* Return Value:	void
* Purpose:		Sets the fraction's denominator value to the given int value
*				If denominator value is zero, assert will end the program
*				(This will avoid any divide by zero situation)
**/
void fraction::setDenominator(int den)
{	
	assert(den != 0); //Avoid dividing by zero
	if(den < 0) //If the denominator is less than zero
	{	denominator = abs(den); //Will now equal its absolute value
		setNumerator(-1*getNumerator());
		//Numerator will turn negative if positive
		//and positive if negative
	}
	else //If denominator is greater than zero
		denominator = den;
}

/**
* Function Name:	setFraction
* Member Type:		Mutator
* Parameter(s):	int - import only (numerator)
*				int - import only (denominator)
* Return Value:	void
* Purpose:		Calls setNumerator and setDenominator to set
*				the whole fraction at once
**/
void fraction::setFraction(int num, int den)
{	
	setNumerator(num);
	setDenominator(den);
}

/**
* Function Name:	getNumerator
* Member Type:		Inspector
* Parameter(s):	N/A
* Return Value:	int (numerator)
* Purpose:		Returns the numerator value of the fraction
**/
int fraction::getNumerator() const
{	return numerator; }

/**
* Function Name:	getDenominator
* Member Type:		Inspector
* Parameter(s):	N/A
* Return Value:	int (denominator)
* Purpose:		Returns the denomiantor value of the fraction
**/
int fraction::getDenominator() const
{	return denominator; }

/**
* Function Name:	< operator
* Member Type:		Facilitator
* Parameter(s):	fraction& - import only
* Return Value:	true if less than
*				false if not
* Purpose:		Checks if current fraction is less than another
**/
bool fraction::operator<(fraction &F) const
{	
	double dec1 = convertToDecimal();
	double dec2 = F.convertToDecimal();
	if(dec1 < dec2)
		return true;
	return false;
}

/**
* Function Name:	< operator
* Member Type:		Facilitator
* Parameter(s):	double - import only
* Return Value:	true if less than
*				false if not
* Purpose:		Checks if current fraction is less than the given
*				double value
**/
bool fraction::operator<(double D) const
{	
	double dec = convertToDecimal();
	if(dec < D)
		return true;
	return false;
}

/**
* Function Name:	> operator
* Member Type:		Facilitator
* Parameter(s):	fraction& - import only
* Return Value:	true if greater than
*				false if not
* Purpose:		Checks if current fraction is greater than another
**/
bool fraction::operator>(fraction &F) const
{	
	double dec1 = convertToDecimal();
	double dec2 = F.convertToDecimal();
	if(dec1 > dec2)
		return true;
	return false;
}

/**
* Function Name:	operator >
* Member Type:		Facilitator
* Parameter(s):	double - import only
* Return Value:	true if greater than
*				false if not
* Purpose:		Checks if current fraction is greater than the given
*				double value
**/
bool fraction::operator>(double D) const
{	
	double dec = convertToDecimal();
	if(dec > D)
		return true;
	return false;
}

/**
* Function Name:	<= operator
* Member Type:		Facilitator
* Parameter(s):	fraction& - import only
* Return Value:	true if less than or equal to
*				false if not
* Purpose:		Checks if current fraction is less than or equal to another
**/
bool fraction::operator<=(fraction &F) const
{	
	double dec1 = convertToDecimal();
	double dec2 = F.convertToDecimal();
	if(dec1 <= dec2)
		return true;
	return false;
}

/**
* Function Name:	<= operator
* Member Type:		Facilitator
* Parameter(s):	double - import only
* Return Value:	true if less than or equal to
*				false if not
* Purpose:		Checks if current fraction is less than or equal to the
*				given double value
**/
bool fraction::operator<=(double D) const
{	
	double dec = convertToDecimal();
	if(dec <= D)
		return true;
	return false;
}

/**
* Function Name:	>= operator
* Member Type:		Facilitator
* Parameter(s):	fraction& - import only
* Return Value:	true if greater than or equal to
*				false if not
* Purpose:		Checks if current fraction is greater than or equal to another
**/
bool fraction::operator>=(fraction &F) const
{	
	double dec1 = convertToDecimal();
	double dec2 = F.convertToDecimal();
	if(dec1 >= dec2)
		return true;
	return false;
}

/**
* Function Name:	>= operator
* Member Type:		Facilitator
* Parameter(s):	double - import only
* Return Value:	true if greater than or equal to
*				false if not
* Purpose:		Checks if current fraction is greater than or equal to the
*				given double value
**/
bool fraction::operator>=(double D) const
{	
	double dec = convertToDecimal();
	if(dec >= D)
		return true;
	return false;
}

/**
* Function Name:	== operator
* Member Type:		Facilitator
* Parameter(s):	fraction& - import only
* Return Value:	true if equal to
*				false if not
* Purpose:		Checks if current fraction is equal to another
**/
bool fraction::operator==(fraction &F) const
{	
	double dec1 = convertToDecimal();
	double dec2 = F.convertToDecimal();
	if(dec1 == dec2)
		return true;
	return false;
}

/**
* Function Name:	== operator
* Member Type:		Facilitator
* Parameter(s):	double - import only
* Return Value:	true if equal to
*				false if not
* Purpose:		Checks if current fraction is equal to the given double value
**/
bool fraction::operator==(double D) const
{	
	double dec = convertToDecimal();
	if(dec == D)
		return true;
	return false;
}

/**
* Function Name:	!= operator
* Member Type:		Facilitator
* Parameter(s):	fraction& - import only
* Return Value:	true if not equal to
*				false if equal to
* Purpose:		Checks if current fraction is not equal to another
**/
bool fraction::operator!=(fraction &F) const
{	
	double dec1 = convertToDecimal();
	double dec2 = F.convertToDecimal();
	if(dec1 != dec2)
		return true;
	return false;
}

/**
* Function Name:	!= operator
* Member Type:		Facilitator
* Parameter(s):	double - import only
* Return Value:	true if not equal to
*				false if equal to
* Purpose:		Checks if current fraction is not equal to the given double value
**/
bool fraction::operator!=(double D) const
{	
	double dec = convertToDecimal();
	if(dec != D)
		return true;
	return false;
}

/**
* Function Name:	= operator
* Member Type:		Mutator
* Parameter(s):	fraction& - import only
* Return Value:	void
* Purpose:		Sets current fraction equal to another
**/
void fraction::operator=(fraction &F)
{	
	setNumerator(F.getNumerator());
	setDenominator(F.getDenominator());
}

/**
* Function Name:	*= operator
* Member Type:		Mutator
* Parameter(s):	fraction& - import only
* Return Value:	void
* Purpose:		Multiplies current fraction by another fraction
**/
void fraction::operator*=(fraction &F)
{	
	//Multiply numerator by numerator
	setNumerator(getNumerator()*F.getNumerator());
	
	//Multiply denominator by denominator
	setDenominator(getDenominator()*F.getDenominator());
	checkReduce();
}

/**
* Function Name:	/= operator
* Member Type:		Mutator
* Parameter(s):	fraction& - import only
* Return Value:	void
* Purpose:		Divides current fraction by another fraction
**/
void fraction::operator/=(fraction &F)
{	
	//Multiply numerator by denominator
	setNumerator(getNumerator()*F.getDenominator());
	
	//Multiply denominator by numerator
	setDenominator(getDenominator()*F.getNumerator());
	checkReduce();
}

/**
* Function Name:	+= operator
* Member Type:		Mutator
* Parameter(s):	fraction& - import only
* Return Value:	void
* Purpose:		Adds the current fraction and the given fraction together
**/
void fraction::operator+=(fraction &F)
{	
	//If the denominators are equal, just add the numerators
	if(getDenominator() == F.getDenominator())
		setNumerator(getNumerator()+F.getNumerator());
		
	//If not, multiply the current fraction's numerator and denominator by the
	//given fraction's denominator and multiply the given fraction's numerator
	//and denominator by the current fraction's denominator
	else
	{	fraction f1, f2; //Temporary storage
		f1.setNumerator(getNumerator() * F.getDenominator());
		f1.setDenominator(getDenominator() * F.getDenominator());
		f2.setNumerator(F.getNumerator() * getDenominator());
		f2.setDenominator(F.getDenominator() * getDenominator());
		
		//Now add the numerators together
		setNumerator(f1.getNumerator() + f2.getNumerator());
		setDenominator(f1.getDenominator());
	} //Check if fraction can be reduced
	checkReduce();
}

/**
* Function Name:	-= operator
* Member Type:		Mutator
* Parameter(s):	fraction& - import only
* Return Value:	void
* Purpose:		Subtracts the given fraction from the current fraction
**/
void fraction::operator-=(fraction &F)
{	
	//If the denominators are equal, just subtract the numerators
	if(getDenominator() == F.getDenominator())
		setNumerator(getNumerator()-F.getNumerator());
		
	//If not, multiply the current fraction's numerator and denominator by the
	//given fraction's denominator and multiply the given fraction's numerator
	//and denominator by the current fraction's denominator
	else
	{	fraction f1, f2; //Temporary storage
		f1.setNumerator(getNumerator() * F.getDenominator());
		f1.setDenominator(getDenominator() * F.getDenominator());
		f2.setNumerator(F.getNumerator() * getDenominator());
		f2.setDenominator(F.getDenominator() * getDenominator());
		
		//Now subtract the numerators
		setNumerator(f1.getNumerator() - f2.getNumerator());
		setDenominator(f1.getDenominator());
	} //Check if fraction can be reduced
	checkReduce();
}

/**
* Function Name:	convertToDecimal
* Member Type:		Facilitator
* Parameter(s):	N/A
* Return Value:	double - converted fraction
* Purpose:		Divides numerator by denominator to find and return
*				the fraction's equivalent double value
**/
double fraction::convertToDecimal() const
{	
	double num = getNumerator();
	double den = getDenominator();
	double dec = num/den;
	return dec;
}

/**
* Function Name:	checkReduce
* Member Type:		Mutator
* Parameter(s):	N/A
* Return Value:	void
* Purpose:		Checks if the fraction can be reduced to a smaller fraction
*				by finding the greatest common multiple (gcm) If the numerator
*				and denominator are equal the value will be 1/1 or -1/1
**/
void fraction::checkReduce()
{	
	if(abs(getNumerator()) == getDenominator())
	{	setNumerator(getNumerator()/getDenominator());
		setDenominator(1);
		return;
	}
	int min = fmin(abs(getNumerator()), getDenominator());
	int max = fmax(abs(getNumerator()), getDenominator());
	for(int i = min; i > 1; i--)
	{	if(min % i == 0 && max % i == 0)
		{	setNumerator(getNumerator()/i);
			setDenominator(getDenominator()/i);
			return;
		}
	}
}

/**
* Function Name:	printImproper
* Member Type:		Facilitator
* Parameter(s):	N/A
* Return Value:	void
* Purpose:		Prints the current fraction improperly (if the numerator
*				is greater than the denominator) if the numerator is not
*				greater than the denominator, just the fraction will print
**/
void fraction::printImproper() const
{	
	if(abs(getNumerator()) > getDenominator())
	{	int wholenum = floor(getNumerator()/getDenominator());
		int num = getNumerator()-(wholenum*getDenominator());
		cout << wholenum << "u" << num << "/" << getDenominator();
	}
	else
		cout << *this;
}

/**
* Function Name:	<< operator
* Member Type:		N/A
* Parameter(s):	ostream& - import/export
*				fraction* - import only
* Return Value:	ostream& - the fraction printed properly
* Purpose:		Prints the fraction to screen, if a proper fraction
*				the value will appear as a fraction ("num/den")
**/
ostream &operator<<(ostream &out, const fraction &F)
{	
	//If numerator is zero, print zero
	//If denominator is 1, print numerator
	if(F.getNumerator() == 0 || F.getDenominator() == 1)
		out << F.getNumerator();
	else
	{	//If numerator and denominator equal, print numerator (1 or -1)
		if(abs(F.getNumerator()) == F.getDenominator())
			out << F.getNumerator();
		else //Fraction cannot be reduced to whole number, print fraction
			out << F.getNumerator() << "/" << F.getDenominator();
	}
	return out;
}

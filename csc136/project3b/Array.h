/*
Author:		Dr. Spiegel
Updated By:	Christian Carreras
File: 		Array.h
Description:	Simple class Array (for Term class)
*/
#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

 using namespace std;

class Term;
class Array {

public:

//////////////
//Constructor
//////////////
/*
Function:	Constructor
Description:	Constructs an array of Terms
Parameters:	none
Returns:	N/A
*/
Array( int = 10 );

///////////////////
//Copy Constructor
///////////////////
/*
Function:	Copy Constructor
Description:	Creates copy of the Array object
Parameters:	const Array&	- Array object
Returns:	N/A
*/
Array( const Array & );

//////////////
//Destructor
//////////////
/*
Function:	Destructor
Description:	Removes an Array object from memory
Parameters:	none
Returns:	N/A
*/
~Array();

/////////
//Sets
/////////
/*
Function:	setCapacity
Member Type:	Mutator
Description:	Sets the capacity of the Array object
Parameters:	int	- capacity
Returns:	void
*/
void setCapacity(int);

/////////
//Gets
/////////
/*
Function:	getCapacity
Member Type:	Inspector
Description:	Returns the Array object's capacity
Parameters:	none
Returns:	int	- capacity
*/
int getCapacity() const;

/*
Function:	getElements
Member Type:	Inspector
Description:	Returns the elementsInUse
Parameters:	none
Returns:	int	- elementsInUse
*/
int getElements() const;

/*
Function:	getArrayCount
Member Type:	Inspector
Description:	Returns number of Arrays in use
Parameters:	none
Returns:	int	- arrayCount
*/
static int getArrayCount();

///////////////////
//Member Functions
///////////////////
/*
Function:	addTerm
Member Type:	Mutator
Description:	Calls other addTerm function with smaller data
Parameters:	Term&	- Term object to be added to array
Returns:	true if Term is added, false if not
*/
bool addTerm(Term&);

/*
Function:	addTerm
Member Type:	Mutator
Description:	Checks if array if full and if the coeff is zero
		Then calls cDupLoc and +=
Parameters:	float	- coefficient
		int	- exponent
Returns:	true if Term is added, false if not
*/
bool addTerm(float, int);

/*
Function:	cDupLoc
Member Type:	Mutator
Description:	Checks if one element's exponent matches another in the
		array and if so adds that element's coefficient to the
		other matching element's coefficient
Parameters:	float	- coefficient
		int	- exponent
Returns:	true if there is a duplicate location, false if not
*/
bool cDupLoc(float, int);

/*
Function:	sort
Member Type:	Mutator
Description:	Class selSort
Parameters:	none
Returns:	void
*/
void sort();

//////////////
//Operators
//////////////
/*
Function:	= operator
Member Type:	Mutator
Description:	Sets one array object equal to another
Parameters:	const Array&	- array object to be set equal to
Returns:	const Array	- the array object itself
*/
const Array &operator=( const Array & );

/*
Function:	== operator
Member Type:	Facilitator
Description:	Checks if two array objects are equal
Parameters:	const Array&	- array object to be compared to
Returns:	true if arrays are equal, false if not
*/
bool operator==( const Array & ) const;  // compare equal

// Determine if two arrays are not equal and
// return true, otherwise return false (uses operator==).
bool operator!=( const Array &right ) const  
{ return ! ( *this == right ); }

/*
Function:	[] operator
Member Type:	Mutator
Description:	Allows user to potentially change an array element
Parameters:	int	- array index
Returns:	returns the Term at that Array index
*/
Term &operator[]( int );              // subscript operator

/*
Function:	[] operator
Member Type:	Inspector
Description:	Enables individual array elements to be displayed
Parameters:	int	- array index
Returns:	returns the Term at that Array index
*/
const Term &operator[]( int ) const;  // subscript operator

/*
Function:	+= operator
Member Type:	Mutator
Description:	Appends a Term to the end of an Array object
Parameters:	Term&	- the Term to be added
Returns:	Array&	- the Array object itself
*/
Array& operator+=(Term &);
					
private:

int capacity; // size of the array
int elementsInUse; // elements of the array used
Term *ptr; // pointer to first element of array
static int arrayCount;  // # of Arrays instantiated

/*
Function:	setElements
Member Type:	Mutator
Description:	Sets elementsInUse, private so
		user can't mess with it
Parameters:	int	- elementsInUse
Returns:	void
*/
void setElements(int);

};

/*
Function:	<< operator
Description:	Diplsys the array term by term
Parameters:	ostream&	- output stream
		const Array&	- Array to be place into string
Returns:	ostream
*/
ostream &operator<<( ostream &, const Array & );

#endif


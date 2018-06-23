// File: array.cpp
// Member function definitions for class Array
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <assert.h>
#include "Array.h"
#include "term.h"
#include "SortSearch.h"

 using namespace std;

// Initialize static data member at file scope
int Array::arrayCount = 0;   // no objects yet

// Default constructor for class Array (default size 10)
Array::Array( int arraySize )
{
   setCapacity(( arraySize > 0 ? arraySize : 10 )); 
   ptr = new Term[getCapacity()]; // create space for array
   assert( ptr != 0 );    // terminate if memory not allocated
   ++arrayCount;          // count one more object
   setElements(0);

   for ( int i = 0; i < getCapacity(); i++ )
      ptr[ i ] = 0;          // initialize array
}

// Copy constructor for class Array
// must receive a reference to prevent infinite recursion
Array::Array( const Array &init )
{  setCapacity(init.getCapacity());
   ptr = new Term[getCapacity()]; // create space for array
   assert( ptr != 0 );    // terminate if memory not allocated
   ++arrayCount;          // count one more object
   setElements(getElements());

   for ( int i = 0; i < getElements(); i++ )
      ptr[ i ] = init.ptr[ i ];  // copy init into object
}

// Destructor for class Array
Array::~Array()
{
   delete [] ptr;            // reclaim space for array
   --arrayCount;             // one fewer objects
}

// Set the Array's size
void Array::setCapacity(int elts)
{ capacity=elts;
}

// Get the size of the array
int Array::getCapacity() const 
{ return capacity; }

int Array::getElements() const
{	return elementsInUse; }

// Overloaded assignment operator
// const return avoids: ( a1 = a2 ) = a3
const Array &Array::operator=( const Array &right )
{
   if ( &right != this ) {  // check for self-assignment
      
      // for arrays of different sizes, deallocate original
      // left side array, then allocate new left side array.
      if ( getCapacity() != right.getCapacity() ) {
         delete [] ptr;         // reclaim space
         setCapacity(right.getCapacity());     // resize this object
         ptr = new Term[getCapacity()]; // create space for array copy
         assert( ptr != 0 );    // terminate if not allocated
      }

      for ( int i = 0; i < getElements(); i++ )
         ptr[ i ] = right[ i ];  // copy array into object
   }
   setElements(right.getElements());
   return *this;   // enables x = y = z;
}

// Determine if two arrays are equal and
// return true, otherwise return false.
bool Array::operator==( const Array &right ) const
{
   if ( getElements() != right.getElements() )
      return false;    // arrays of different sizes

   for ( int i = 0; i < getElements(); i++ )
      if ((ptr[i].getCoefficient() && ptr[i].getExponent()) != 
      (right[i].getCoefficient() && right[i].getExponent()))
         return false; // arrays are not equal

   return true;        // arrays are equal
}

// Overloaded subscript operator for non-const Arrays
// reference return creates an lvalue
Term &Array::operator[]( int subscript )
{
   // check for subscript out of range error
   assert( 0 <= subscript && subscript < getElements() );

   return ptr[ subscript ]; // reference return
}

// Overloaded subscript operator for const Arrays
// const reference return creates an rvalue
const Term &Array::operator[]( int subscript ) const
{
   // check for subscript out of range error
   assert( 0 <= subscript && subscript < getElements() );

   return ptr[ subscript ]; // const reference return
}

// Return the number of Array objects instantiated
// static functions cannot be const 
int Array::getArrayCount() { return arrayCount; }

bool Array::addTerm(Term &T)
{	return(addTerm(T.getCoefficient(), T.getExponent())); }

bool Array::addTerm(float coeff, int expn)
{	Term T;
	if(getElements() < getCapacity())	//Check if Array is full
	{	if(coeff != 0)
		{	if(!cDupLoc(coeff, expn))//Check for duplicate location
			{	T.setCoefficient(coeff);
				T.setExponent(expn);
				*this+=T;
				return true;
			}
			else
			{	setElements(getElements()+1);
				return true;
			}
		}
		else
			return false;
	}
	else
		return false;
}

void Array::sort()
{	selSort(ptr, getElements());
}

//Check to find if exponents match
bool Array::cDupLoc(float coeff, int expn)
{	int idx = getElements();
	for(int i = 0; i < getElements(); i++)
	{	if(expn == ptr[i].getExponent())
		{	ptr[i].setCoefficient(ptr[i].getCoefficient()+coeff);
			setElements(getElements()-1);
		}
	}
	if(idx != getElements())
		return true;
	else
		return false;
}
//Adds Term to the Array
Array& Array::operator+=(Term &T)
{	ptr[elementsInUse].setCoefficient(T.getCoefficient());
	ptr[elementsInUse].setExponent(T.getExponent());
	setElements(getElements()+1);
	sort(); //Sort Array
}

void Array::setElements(int x)
{	elementsInUse = x; }

// Overloaded output operator for class Array 
ostream &operator<<( ostream &output, const Array &a )
{
   for(int i = 0; i < a.getElements(); i++)
	{	if(i < a.getElements()-1)
			output << a[i] << " + "; 
		else
			output << a[i];
	}

   return output;   // enables cout << x << y;
}

// File: array.h
// Simple class Array (for Term class)
#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>

 using namespace std;

class Term;
class Array {

public:
   Array( int = 10 );                   // default constructor
   Array( const Array & );              // copy constructor
   ~Array();                            // destructor
   void setCapacity(int);			// set the capacity
   int getCapacity() const;                 // return capacity
   int getElements() const;
   const Array &operator=( const Array & ); // assign arrays
   bool operator==( const Array & ) const;  // compare equal

   // Determine if two arrays are not equal and
   // return true, otherwise return false (uses operator==).
   bool operator!=( const Array &right ) const  
      { return ! ( *this == right ); }
   
   Term &operator[]( int );              // subscript operator
   const Term &operator[]( int ) const;  // subscript operator
   static int getArrayCount();          // Return count of 
                                        // arrays instantiated.
   bool addTerm(Term&);
   bool addTerm(float, int);
   bool cDupLoc(float, int);
   void sort();
   Array& operator+=(Term &);
					
private:
   int capacity; // size of the array
   int elementsInUse;
   Term *ptr; // pointer to first element of array
   static int arrayCount;  // # of Arrays instantiated
   void setElements(int);

};

   ostream &operator<<( ostream &, const Array & );

#endif


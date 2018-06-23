/*
File:		types.tpp
Author:		Dr. Spiegel
Updated By:	Christian Carreras
Course:		CSC136
Assignment:	Project 4
Description:	Necessary to make the LinkedList object
		compatible with Term objects.
*/

// Explicit Initializers. Necessary to be able to be able to place 
//      template class function implementations in a .cpp file
#include "term.h"

template class node<Term>;
template class LinkedList<Term>;
template class listItr<Term>;
template ostream& operator<<(ostream &os,const LinkedList<Term> &l);

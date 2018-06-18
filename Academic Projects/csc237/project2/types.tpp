/*
// Author:	Christian Carreras
// Course:	CSC 237
// File:	types.tpp
// Purpose:	Necessary for explicit initialization
*/

//Explicit Initializers. Necessary to be able to be able to place 
//template class function implementations in a .cpp file
#include "Node.h"
#include "WordData.h"

template class node<int>;
template class node<WordData>;
template class DLinkedList<int>;
template class DLinkedList<WordData>;
template class DListItr<int>;
template class DListItr<WordData>;

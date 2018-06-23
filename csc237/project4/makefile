# Author:			Dr. Spiegel
# Documented By:	Chris Carreras
# File:			makefile
# Date:			25/04/2014
# Purpose:		Links the BinarySearch tree .cpp file to its .h file
#				Then links those files to TreeTest.cpp
#				Creates the executable named tree

debugFlag=-g

tree: BinarySearchTree.o Treetest.o 
	g++ -o tree Treetest.o BinarySearchTree.o $(debugFlag)

Treetest.o: Treetest.cpp  BinarySearchTree.h
	g++ -c Treetest.cpp $(debugFlag)

BinarySearchTree.o: BinarySearchTree.cpp BinarySearchTree.h 
	g++ -c BinarySearchTree.cpp $(debugFlag)


clean: 
	\rm -f *.o testdate

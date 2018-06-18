#	Author:		Christian Carreras
#	File:		makefile
#	Date:		10/18/2015
#	Class:		CSC 402
#	About:		Makefile for compiling instructions of the treeGraph
#			class and its tester file.


arrayBsDemo: arrayBsDemo.o arrayBsTree.o
	g++  -o arrayBsDemo arrayBsDemo.o arrayBsTree.o
	
arrayBsTree.o: arrayBsTree.cpp arrayBsTree.h bsTree.h
	g++ -c arrayBsTree.cpp
	
arrayBsDemo.o: arrayBsDemo.cpp arrayBsTree.cpp arrayBsTree.h
	g++ -c arrayBsDemo.cpp
	
clean: 
	\rm -f *.o arrayBsDemo
# Author:		Christian Carreras
# File:			makefile
# Date Made:	02/13/2017	
# Due Date:		02/17/2017
# School:		Kutztown University
# Class Num:	CSC 552
# Class Name:	Advanced Unix Programming
# Semester:		SPRING 2017
# Professor:	Dr. Spiegel
# Purpose:		This makefile makes executables for every file in program 1.

CC=/usr/bin/g++
DebugFlag=-g

p1: p1.cpp countWords.cpp printWords.cpp
	$(CC) $(DebugFlag) -o p1 p1.cpp
	$(CC) $(DebugFlag) -o countWords countWords.cpp
	$(CC) $(DebugFlag) -o printWords printWords.cpp
	
countWords: countWords.cpp
	$(CC) $(DebugFlag) -o countWords countWords.cpp
	
printWords: printWords.cpp
	$(CC) $(DebugFlag) -o printWords printWords.cpp

clean:
	\rm -rf *.o p1

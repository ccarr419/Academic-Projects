#Author: 	Christian Carreras
#File: 		makefile
#Purpose: 	Makes it possible to link the WordInfo class
#		to its code and from there to WordTest.cpp
CC = /opt/csw/gcc3/bin/g++
CFLAGS = -Wall

p1: WordTest.o WordInfo.o
	$(CC) $(CFLAGS) -o p1 WordTest.o WordInfo.o

WordTest.o: WordTest.cpp WordInfo.h
	$(CC) $(CFLAGS) -c WordTest.cpp	

WordInfo.o: WordInfo.cpp WordInfo.h
	$(CC) $(CFLAGS) -c WordInfo.cpp

clean:
	rm -rf *.o

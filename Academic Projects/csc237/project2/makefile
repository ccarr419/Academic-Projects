#Author:	Christian Carreras
#Course:	CSC 237
#File:		makefile
#Purpose:	Makes possible to link multiple files together
CC=/opt/csw/gcc3/bin/g++
DebugFlag=-g

app: app.o WordData.o WordDataList.o WordDataDLinkList.o DLinkedList.o
	$(CC) $(DebugFlag) -o app app.o WordData.o WordDataList.o WordDataDLinkList.o DLinkedList.o

testll: testll.o DLinkedList.o WordData.o
	$(CC) $(DebugFlag) -o testll testll.o DLinkedList.o WordData.o
	
WordData.o:  WordData.cpp WordData.h 
	$(CC) $(DebugFlag) -c WordData.cpp
	
WordDataList.o:  WordData.h WordDataList.cpp WordDataList.h WordList.h 
	$(CC) $(DebugFlag) -c WordDataList.cpp
	
WordDataDLinkList.o: WordDataDLinkList.cpp WordDataDLinkList.h DLinkedList.h
	$(CC) $(DebugFlag) -c WordDataDLinkList.cpp

DLinkedList.o: DLinkedList.cpp DLinkedList.h types.tpp
	cp DLinkedList.cpp temp.cpp
	cat types.tpp >> temp.cpp
#	Compile temporary file created with instantiations at the end; save as DLinkedList.o
	$(CC) -c temp.cpp -g -o DLinkedList.o

app.o:  WordDataList.h WordList.h WordDataDLinkList.h Node.h app.cpp 
	$(CC) $(DebugFlag) -c app.cpp

testll.o: testll.cpp DLinkedList.h WordData.h Node.h
	$(CC) $(DebugFlag) -c testll.cpp

clean:
	\rm -rf *.o testLL



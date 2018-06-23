#Author:	Christian Carreras
#Course:	CSC 237
#File:		makefile
#Purpose:	Links the WordList superclass to it's correct subclasses
#		and links the subclasses to their correct data member
#		objects (aka WordData, DLinkedList, Node, etc.)
#		Creates the executable app to test polymorphism
cc=/opt/csw/gcc4/bin/g++ -std=gnu++0x

app: app.o WordData.o WordDataList.o WordDataDLinkList.o DLinkedList.o WordDataSTList.o
	$(cc) -o app app.o WordData.o WordDataList.o WordDataDLinkList.o DLinkedList.o WordDataSTList.o
	
WordData.o:  WordData.cpp WordData.h 
	$(cc) -c WordData.cpp
	
WordDataSTList.o: WordData.h WordDataSTList.cpp WordDataSTList.h WordList.h
	$(cc) -c WordDataSTList.cpp
	
WordDataList.o:  WordData.h WordDataList.cpp WordDataList.h WordList.h 
	$(cc) -c WordDataList.cpp
	
WordDataDLinkList.o: WordDataDLinkList.cpp WordDataDLinkList.h DLinkedList.h
	$(cc) -c WordDataDLinkList.cpp

DLinkedList.o: DLinkedList.cpp DLinkedList.h types.tpp
	cp DLinkedList.cpp temp.cpp
	cat types.tpp >> temp.cpp
#	Compile temporary file created with instantiations at the end; save as DLinkedList.o
	$(cc) -c temp.cpp -g -o DLinkedList.o

app.o:  WordDataList.h WordList.h WordDataDLinkList.h Node.h app.cpp 
	$(cc) -c app.cpp

clean:
	\rm -rf *.o app



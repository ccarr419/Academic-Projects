debugFlag=-g

chainDemo: chainDemo.o chain.o
	g++ -o chainDemo chainDemo.o chain.o $(debugFlag)

chain.o: chain.cpp chain.h chainNode.h
	g++ -c chain.cpp $(debugFlag)

chainDemo.o: chainDemo.cpp chain.cpp chain.h
	g++ -c chainDemo.cpp
	
clean: 
	\rm -f *.o chainDemo

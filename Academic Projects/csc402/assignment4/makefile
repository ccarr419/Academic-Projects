debugFlag=-g

graphDemo: graphDemo.o adjacencyMatrixGraph.o adjacencyListGraph.o
	g++ -o graphDemo graphDemo.o adjacencyMatrixGraph.o adjacencyListGraph.o $(debugFlag)
	
adjacencyMatrixGraph.o: adjacencyMatrixGraph.cpp adjacencyMatrixGraph.h
	g++ -c adjacencyMatrixGraph.cpp $(debugFlag)

adjacencyListGraph.o: adjacencyListGraph.cpp adjacencyListGraph.h
	g++ -c adjacencyListGraph.cpp $(debugFlag)
	
graphDemo.o: graphDemo.cpp adjacencyMatrixGraph.h adjacencyMatrixGraph.cpp adjacencyListGraph.h adjacencyListGraph.cpp
	g++ -c graphDemo.cpp
	
clean: 
	\rm -f *.o graphDemo

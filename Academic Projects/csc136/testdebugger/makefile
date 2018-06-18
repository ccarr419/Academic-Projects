CC=/opt/csw/gcc3/bin/g++  

DebugFlag=-g

debug: debug.o demo.o
	$(CC) -o debug demo.o debug.o $(DebugFlag)

debug.o: debug.cpp demo.h
	$(CC) -c debug.cpp $(DebugFlag)

demo.o: demo.cpp demo.h
	$(CC) -c demo.cpp $(DebugFlag)

clean:
	\rm -f *.o debug

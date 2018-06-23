DebugFlag=-g
CC=/opt/csw/gcc3/bin/g++

p3: poly_tst.o poly.o Array.o term.o
	$(CC) $(DebugFlag) -o p3 poly_tst.o poly.o Array.o term.o

Array.o: Array.h Array.cpp term.h
	$(CC) $(DebugFlag) -c Array.cpp

poly_tst.o: poly_tst.cpp poly.h term.h
	$(CC) $(DebugFlag) -c poly_tst.cpp

poly.o: poly.cpp poly.h Array.h term.h
	$(CC) $(DebugFlag) -c poly.cpp

term.o: term.h term.cpp
	$(CC) $(DebugFlag) -c term.cpp

clean:
	rm -rf *.o p3

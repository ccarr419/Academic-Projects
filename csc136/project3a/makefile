DebugFlag=-g

p3a: Array_tst.o Array.o term.o
	g++ $(DebugFlag) -o p3a Array_tst.o Array.o term.o

Array.o: Array.h Array.cpp term.h
	g++ $(DebugFlag) -c Array.cpp

Array_tst.o: Array_tst.cpp Array.h term.h
	g++ $(DebugFlag) -c Array_tst.cpp

term.o: term.h term.cpp
	g++ $(DebugFlag) -c term.cpp

clean:
	rm -rf *.o p3a

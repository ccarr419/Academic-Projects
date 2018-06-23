CC = /opt/csw/gcc4/bin/g++
CFLAGS = -Wall

p2: poly_tst.o poly.o 
	$(CC) $(CFLAGS) -o p2 poly_tst.o poly.o

poly_tst.o: poly_tst.cpp poly.h
	$(CC) $(CFLAGS) -c poly_tst.cpp

poly.o: poly.cpp poly.h
	$(CC) $(CFLAGS) -c poly.cpp

clean:
	rm -rf *.o

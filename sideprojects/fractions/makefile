#Author: Christian Carreras
cc = /opt/csw/gcc3/bin/g++

test: test.o fraction.o primes.o
	$(cc) -o test test.o fraction.o primes.o
	
fraction.o: fraction.cpp fraction.h
	$(cc) -c fraction.cpp
	
test.o:	test.cpp fraction.h
	$(cc) -c test.cpp
	
clean: 
	\rm -rf *.o test

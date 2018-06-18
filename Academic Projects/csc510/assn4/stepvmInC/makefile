#       makefile for stepvmInC project
#       Dr. Dale Parson. Fall 2017

all:		test

TARGET = stepvmInC

include ./makelib

testall:	clean test testspeed testdebug testprof1 testprof2 testprof3

clean:		subclean
		/bin/rm -f *.out *.o $(TARGET) stepvmDirectInC stepvmInC stepvmTokenInC
		/bin/rm -f debug.txt *.dif *.tmp core* gmon.out gprof[123].txt
		/bin/rm -f stepvmSubroutineInC

build:	

test:
		$(GCC) -Wno-unused-result -O2  stepvmTokenInC.c -o stepvmTokenInC
		/bin/bash -c "time ./stepvmTokenInC 1 BASIC 1 > testbasic.out 2>testbasicerr.out"
		- diff testbasic.out testbasic.ref > testbasic.dif
		# diff testbasicerr.out testbasicerr.ref > testbasicerr.dif
		$(GCC) -Wno-unused-result -O2  stepvmSubroutineInC.c -o stepvmSubroutineInC
		/bin/bash -c "time  ./stepvmSubroutineInC 1 BASIC 1 > testsubroutine.out 2>testsubroutineerr.out"
		- diff testsubroutine.out testbasic.ref > testsubroutine.dif
		# diff testsubroutineerr.out testbasicerr.ref > testsubroutineerr.dif
		$(GCC) -Wno-unused-result -O2  stepvmDirectInC.c -o stepvmDirectInC
		/bin/bash -c "time  ./stepvmDirectInC 1 BASIC 1 > testdirect.out 2>testdirecterr.out"
		- diff testdirect.out testbasic.ref > testdirect.dif
		# diff testdirecterr.out testbasicerr.ref > testdirecterr.dif

testspeed:
		$(GCC) -Wno-unused-result -O2  stepvmTokenInC.c -o stepvmTokenInC
		/bin/bash -c "time  ./stepvmTokenInC 0 BASIC 5000000 > /dev/null "
		$(GCC) -Wno-unused-result -O2  stepvmSubroutineInC.c -o stepvmSubroutineInC
		/bin/bash -c "time  ./stepvmSubroutineInC 0 BASIC 5000000 > /dev/null "
		$(GCC) -Wno-unused-result -O2  stepvmDirectInC.c -o stepvmDirectInC
		/bin/bash -c "time  ./stepvmDirectInC 0 BASIC 5000000 > /dev/null "

testdebug:
		$(GCC) -Wno-unused-result -g -DDEBUGVM  stepvmTokenInC.c -o stepvmTokenInC
		./stepvmTokenInC 1 BASIC 1 > testdebug.out 2>testdebugerr.out
		- diff testdebug.out testdebug.ref > testdebug.dif
		$(GCC) -Wno-unused-result -g -DDEBUGVM  stepvmSubroutineInC.c -o stepvmSubroutineInC
		./stepvmSubroutineInC 1 BASIC 1 > testdebug.out 2>testdebugerr.out
		- diff testdebug.out testdebug.ref > testdebug.dif
		$(GCC) -Wno-unused-result -g -DDEBUGVM  stepvmDirectInC.c -o stepvmDirectInC
		./stepvmDirectInC 1 BASIC 1 > testdirectdebug.out 2>testdirectdbgerr.out
		- diff testdirectdebug.out testdebug.ref  > testdirectdebug.dif

# testprof1 & 2 & 3 are for profiling with gprof
# # see http://www.thegeekstuff.com/2012/08/gprof-tutorial/
testprof1:
		/bin/rm -f gmon.out
		$(GCC) -Wno-unused-result -pg stepvmTokenInC.c -o stepvmTokenInC
		./stepvmTokenInC 0 BASIC 5000000 > testdebug.out 2>testdebugerr.out
		gprof ./stepvmTokenInC gmon.out > gprof1.txt

testprof2:
		/bin/rm -f gmon.out
		$(GCC) -Wno-unused-result -pg  stepvmSubroutineInC.c -o stepvmSubroutineInC
		./stepvmSubroutineInC 0 BASIC 5000000 > testdirectdebug.out 2>testdirectdbgerr.out
		gprof ./stepvmSubroutineInC gmon.out > gprof2.txt

testprof3:
		/bin/rm -f gmon.out
		$(GCC) -Wno-unused-result -pg  stepvmDirectInC.c -o stepvmDirectInC
		./stepvmDirectInC 0 BASIC 5000000 > testdirectdebug.out 2>testdirectdbgerr.out
		gprof ./stepvmDirectInC gmon.out > gprof3.txt

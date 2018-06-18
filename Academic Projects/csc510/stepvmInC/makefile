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
		$(GCC) -O2  stepvmTokenInC.c -o stepvmTokenInC
		time ./stepvmTokenInC 1 BASIC 1 > testbasic.out 2>testbasicerr.out
		diff testbasic.out testbasic.ref > testbasic.dif
		diff testbasicerr.out testbasicerr.ref > testbasicerr.dif
		$(GCC) -O2  stepvmSubroutineInC.c -o stepvmSubroutineInC
		time ./stepvmSubroutineInC 1 BASIC 1 > testsubroutine.out 2>testsubroutineerr.out
		diff testsubroutine.out testbasic.ref > testsubroutine.dif
		diff testsubroutineerr.out testbasicerr.ref > testsubroutineerr.dif
		$(GCC) -O2  stepvmDirectInC.c -o stepvmDirectInC
		time ./stepvmDirectInC 1 BASIC 1 > testdirect.out 2>testdirecterr.out
		diff testdirect.out testbasic.ref > testdirect.dif
		diff testdirecterr.out testbasicerr.ref > testdirecterr.dif

testspeed:
		$(GCC) -O2  stepvmTokenInC.c -o stepvmTokenInC
		time ./stepvmTokenInC 0 BASIC 5000000 > /dev/null 2>/dev/null
		$(GCC) -O2  stepvmSubroutineInC.c -o stepvmSubroutineInC
		time ./stepvmSubroutineInC 0 BASIC 5000000 > /dev/null 2>/dev/null
		$(GCC) -O2  stepvmDirectInC.c -o stepvmDirectInC
		time ./stepvmDirectInC 0 BASIC 5000000 > /dev/null 2>/dev/null

testdebug:
		$(GCC) -g -DDEBUGVM  stepvmTokenInC.c -o stepvmTokenInC
		./stepvmTokenInC 1 BASIC 1 > testdebug.out 2>testdebugerr.out
		diff testdebug.out testdebug.ref > testdebug.dif
		$(GCC) -g -DDEBUGVM  stepvmSubroutineInC.c -o stepvmSubroutineInC
		./stepvmSubroutineInC 1 BASIC 1 > testdebug.out 2>testdebugerr.out
		diff testdebug.out testdebug.ref > testdebug.dif
		$(GCC) -g -DDEBUGVM  stepvmDirectInC.c -o stepvmDirectInC
		./stepvmDirectInC 1 BASIC 1 > testdirectdebug.out 2>testdirectdbgerr.out
		diff testdirectdebug.out testdebug.ref  > testdirectdebug.dif

# testprof1 & 2 & 3 are for profiling with gprof
# # see http://www.thegeekstuff.com/2012/08/gprof-tutorial/
testprof1:
		/bin/rm -f gmon.out
		$(GCC) -pg stepvmTokenInC.c -o stepvmTokenInC
		./stepvmTokenInC 0 BASIC 5000000 > testdebug.out 2>testdebugerr.out
		gprof ./stepvmTokenInC gmon.out > gprof1.txt

testprof2:
		/bin/rm -f gmon.out
		$(GCC) -pg  stepvmSubroutineInC.c -o stepvmSubroutineInC
		./stepvmSubroutineInC 0 BASIC 5000000 > testdirectdebug.out 2>testdirectdbgerr.out
		gprof ./stepvmSubroutineInC gmon.out > gprof2.txt

testprof3:
		/bin/rm -f gmon.out
		$(GCC) -pg  stepvmDirectInC.c -o stepvmDirectInC
		./stepvmDirectInC 0 BASIC 5000000 > testdirectdebug.out 2>testdirectdbgerr.out
		gprof ./stepvmDirectInC gmon.out > gprof3.txt

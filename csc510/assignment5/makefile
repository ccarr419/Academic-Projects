#       makefile for assn5, problem 5, CSC 510 Advanced Operating Systems
#       Dr. Dale Parson. Fall 2017
#       Modified by Christian Carreras
#       do a 'make clean' before every simulation

all:		needtarget

TARGET = csc510fall2017assn5
DEBUG = 1
DPOS := /home/KUTZTOWN/parson/OpSys
DPPY := $(DPOS)/state2codeV15

CF = -std=gnu++0x -pthread

include ./makelib

clean:		subclean
		/bin/rm -f *.o *.log testFair testWRP testSRP testWWP testSWP testFCFS

test:		needtarget

needtarget:
		@echo "do 'make testAll', 'make testFair', 'make testWRP', 'make testWWP', or 'make testFCFS'"
		bash -c "exit 1"
        
testAll: testFair testWRP testWWP testFCFS
		@echo "ALL SIMULATIONS COMPLETE"
      
testFair: fair.o readWriteSTM.o
		@echo 'COMPILING testFair'
		/bin/bash -c "g++ $(CF) -o testFair fair.o readWriteSTM.o"
		@echo "COMPILING COMPLETED"
		@echo "SIMULATING (TESTING) testFair"
		/bin/bash -c "./testFair"
		@echo "COMPLETED (OK) SIMULATING (TESTING) testFair"
        
testWRP: wrp.o readWriteSTM.o
		@echo 'COMPILING testWRP'
		/bin/bash -c "g++ $(CF) -o testWRP wrp.o readWriteSTM.o"
		@echo "COMPILING COMPLETED"
		@echo "SIMULATING (TESTING) testWRP"
		/bin/bash -c "./testWRP"
		@echo "COMPLETED (OK) SIMULATING (TESTING) testWRP"
        
#testSRP: srp.o readWriteSTM.o
#		@echo 'COMPILING testSRP'
#		/bin/bash -c "g++ $(CF) -o testSRP srp.o readWriteSTM.o"
#		@echo "COMPILING COMPLETED"
#		@echo "SIMULATING (TESTING) testSRP"
#		/bin/bash -c "./testSRP"
#		@echo "COMPLETED (OK) SIMULATING (TESTING) testSRP"
        
testWWP: wwp.o readWriteSTM.o
		@echo 'COMPILING testWWP'
		/bin/bash -c "g++ $(CF) -o testWWP wwp.o readWriteSTM.o"
		@echo "COMPILING COMPLETED"
		@echo "SIMULATING (TESTING) testWWP"
		/bin/bash -c "./testWWP"
		@echo "COMPLETED (OK) SIMULATING (TESTING) testWWP"
        
#testSWP: swp.o readWriteSTM.o
#		@echo 'COMPILING testSWP'
#		/bin/bash -c "g++ $(CF) -o testSWP swp.o readWriteSTM.o"
#		@echo "COMPILING COMPLETED"
#		@echo "SIMULATING (TESTING) testSWP"
#		/bin/bash -c "./testSWP"
#		@echo "COMPLETED (OK) SIMULATING (TESTING) testSWP"
        
testFCFS: fcfs.o readWriteSTM.o
		@echo 'COMPILING testFCFS'
		/bin/bash -c "g++ $(CF) -o testFCFS fcfs.o readWriteSTM.o"
		@echo "COMPILING COMPLETED"
		@echo "SIMULATING (TESTING) testFCFS"
		/bin/bash -c "./testFCFS"
		@echo "COMPLETED (OK) SIMULATING (TESTING) testFCFS"
        
fair.o:
		@echo 'COMPILING fair'
		/bin/bash -c "g++ $(CF) -c fair.cpp"
        
wrp.o:
		@echo 'COMPILING wrp'
		/bin/bash -c "g++ $(CF) -c wrp.cpp"
        
#srp.o:
#		@echo 'COMPILING srp'
#		/bin/bash -c "g++ $(CF) -c srp.cpp"
        
wwp.o:
		@echo 'COMPILING wwp'
		/bin/bash -c "g++ $(CF) -c wwp.cpp"

#swp.o:
#		@echo 'COMPILING swp'
#		/bin/bash -c "g++ $(CF) -c swp.cpp"
        
fcfs.o:
		@echo 'COMPILING fcfs'
		/bin/bash -c "g++ $(CF) -c fcfs.cpp"

readWriteSTM.o:
		@echo 'COMPILING readWriteSTM'
		/bin/bash -c "g++ $(CF) -c readWriteSTM.cpp"

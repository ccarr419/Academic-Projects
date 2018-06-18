#       makefile for jitstm2017, problem 3, CSC 510 Advanced Operating Systems
#       Dr. Dale Parson. Fall 2017

all:		build

TARGET = jitstm2017
DEBUG = 1
DPOS := /home/KUTZTOWN/parson/OpSys
DPPY := $(DPOS)/state2codeV15

include ./makelib

clean:		subclean
		/bin/rm -f *.out *.dif *.pyc junk parsetab.py *.vmlf *.png
		/bin/rm -f *.dot *.gif *.jpg testmachine.ck junk.* *.tmp *.log *.
		/bin/rm -f *.crunch /tmp/$(STUDENT)_STM_*.log $(STUDENT)_STM_*.log
		/bin/rm -f jit*.py

test:		testserver testXint
			T1=`grep COST jitserver.log | cut -d! -f2` && T2=`grep COST jitXint.log | cut -d! -f2` && $(PYTHON) -c print\(\"SPEEDUP:\",$$T2/$$T1\)

build:		buildserver buildXint

buildserver:
		@echo 'COMPILING jitserver'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py jitserver.stm jitserver.dot jitserver.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

testserver:		buildserver
		@echo "SIMULATING (TESTING) jitserver"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. STMLOGDIR=/tmp time $(PYTHON) jitserver.py 2 4 1000000 12345 2"
		grep COST jit*.log
		@echo "COMPLETED (OK) SIMULATING (TESTING) jitserver"

buildXint:
		@echo 'COMPILING jitXint'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py jitXint.stm jitXint.dot jitXint.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

testXint:		buildXint
		@echo "SIMULATING (TESTING) jitXint"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. STMLOGDIR=/tmp time $(PYTHON) jitXint.py 2 4 1000000 12345 2"
		grep COST jit*.log
		@echo "COMPLETED (OK) SIMULATING (TESTING) jitXint"

buildXcomp:
		@echo 'COMPILING jitXcomp'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py jitXcomp.stm jitXcomp.dot jitXcomp.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

testXcomp:		buildXcomp
		@echo "SIMULATING (TESTING) jitXcomp"
		/bin/rm -f ./$(STUDENT)_STM_*.log $(STUDENT)_STM_*.log jitXcomp.log
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. STMLOGDIR=/tmp time $(PYTHON) jitXcomp.py 2 4 1000000 12345 2"
		grep COST jit*.log
		@echo "COMPLETED (OK) SIMULATING (TESTING) jitXcomp"

graphs:		$(JPEGFILES)

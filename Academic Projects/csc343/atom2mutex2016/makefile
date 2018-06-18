#       makefile for atom2mutex2016, problem 2, CSC 343 Operating Systems
#       Dr. Dale Parson. Fall 2016

all:		build

TARGET = atom2mutex2016
DEBUG = 1
DPOS := /home/KUTZTOWN/parson/OpSys
DPPY := $(DPOS)/state2codeV12

include ./makelib

clean:		subclean
		-/bin/bash -c 'chmod 666 ~parson/tmp/$(STUDENT)_STM*'
		/bin/bash -c '/bin/rm -f *.out *.dif *.pyc junk parsetab.py *.vmlf'
		/bin/bash -c '/bin/rm -f *.dot *.gif *.jpg testmachine.ck junk.* *.tmp *.log atom2mutex2016.py'
		/bin/bash -c '/bin/rm -f *.crunch ~parson/tmp/$(STUDENT)_STM_*.log $(STUDENT)_STM_*.log Unsafe*.log'
		/bin/bash -c '/bin/rm -f rr*.py sjf*.py fcfs*.py plotcrunch.csv *.crunch *_crunch.py *.crunch *.csv *.png *.jpg'
		/bin/bash -c '/bin/rm -f countUnsafe.py countAtomic20.py countAtomic2.py countMutex20.py countMutex2.py'

build:		build_unsafe build_atomic20 build_atomic2 build_mutex20 build_mutex2

test:		test_unsafe test_atomic20 test_mutex20 test_atomic2 test_mutex2

csv:
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) plotcrunch.py diffset countUnsafe_crunch.py countAtomic20_crunch.py countMutex20_crunch.py countAtomic2_crunch.py countMutex2_crunch.py

build_unsafe:
		@echo 'COMPILING countUnsafe'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py countUnsafe.stm countUnsafe.dot countUnsafe.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

test_unsafe:	build_unsafe
		@echo "SIMULATING (TESTING) countUnsafe"
		/bin/rm -f ~parson/tmp/$(STUDENT)_STM_*.log $(STUDENT)_STM_*.log countUnsafe.log
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. STMLOGDIR=~parson/tmp time $(PYTHON) countUnsafe.py 2 4 10000 12345 2"
		/bin/bash -c 'chmod 666 ~parson/tmp/$(STUDENT)_STM*'
		# Ignore any errors on the unsafe version
		-/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlog.py countUnsafe.log"
		egrep 'MSG.*ENDTHREAD' countUnsafe.log
		egrep 'MSG.*ENDTHREAD' countUnsafe.log | tail -1 | cut -d, -f6-9 > countUnsafe.out
		# Ignore diffs in countUnsafe
		-diff countUnsafe.out countUnsafe.ref > countUnsafe.dif
		@echo "COMPLETED (OK) SIMULATING (TESTING) countUnsafe"

build_atomic20:
		@echo 'COMPILING countAtomic20'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py countAtomic20.stm countAtomic20.dot countAtomic20.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

test_atomic20:	build_atomic20
		@echo "SIMULATING (TESTING) countAtomic20"
		/bin/rm -f ~parson/tmp/$(STUDENT)_STM_*.log $(STUDENT)_STM_*.log countAtomic20.log
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. STMLOGDIR=~parson/tmp time $(PYTHON) countAtomic20.py 2 4 10000 12345 2"
		/bin/bash -c 'chmod 666 ~parson/tmp/$(STUDENT)_STM*'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlog.py countAtomic20.log"
		egrep 'MSG.*ENDTHREAD' countAtomic20.log
		egrep 'MSG.*ENDTHREAD' countAtomic20.log | tail -1 | cut -d, -f6-9 > countAtomic20.out
		diff countAtomic20.out countAtomic20.ref > countAtomic20.dif
		@echo "COMPLETED (OK) SIMULATING (TESTING) countAtomic20"

build_atomic2:
		@echo 'COMPILING countAtomic2'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py countAtomic2.stm countAtomic2.dot countAtomic2.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

test_atomic2:	build_atomic2
		@echo "SIMULATING (TESTING) countAtomic2"
		/bin/rm -f ~parson/tmp/$(STUDENT)_STM_*.log $(STUDENT)_STM_*.log countAtomic2.log
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. STMLOGDIR=~parson/tmp time $(PYTHON) countAtomic2.py 2 4 10000 12345 2"
		/bin/bash -c 'chmod 666 ~parson/tmp/$(STUDENT)_STM*'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlog.py countAtomic2.log"
		egrep 'MSG.*ENDTHREAD' countAtomic2.log
		egrep 'MSG.*ENDTHREAD' countAtomic2.log | tail -1 | cut -d, -f6-9 > countAtomic2.out
		diff countAtomic2.out countAtomic2.ref > countAtomic2.dif
		@echo "COMPLETED (OK) SIMULATING (TESTING) countAtomic2"

build_mutex20:
		@echo 'COMPILING countMutex20'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py countMutex20.stm countMutex20.dot countMutex20.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

test_mutex20:	build_mutex20
		@echo "SIMULATING (TESTING) countMutex20"
		/bin/rm -f ~parson/tmp/$(STUDENT)_STM_*.log $(STUDENT)_STM_*.log countMutex20.log
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. STMLOGDIR=~parson/tmp time $(PYTHON) countMutex20.py 2 4 10000 12345 2"
		/bin/bash -c 'chmod 666 ~parson/tmp/$(STUDENT)_STM*'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlog.py countMutex20.log"
		egrep 'MSG.*ENDTHREAD' countMutex20.log
		egrep 'MSG.*ENDTHREAD' countMutex20.log | tail -1 | cut -d, -f6-9 > countMutex20.out
		diff countMutex20.out countMutex20.ref > countMutex20.dif
		@echo "COMPLETED (OK) SIMULATING (TESTING) countMutex20"

build_mutex2:
		@echo 'COMPILING countMutex2'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py countMutex2.stm countMutex2.dot countMutex2.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

test_mutex2:	build_mutex2
		@echo "SIMULATING (TESTING) countMutex2"
		/bin/rm -f ~parson/tmp/$(STUDENT)_STM_*.log $(STUDENT)_STM_*.log countMutex2.log
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. STMLOGDIR=~parson/tmp time $(PYTHON) countMutex2.py 2 4 10000 12345 2"
		/bin/bash -c 'chmod 666 ~parson/tmp/$(STUDENT)_STM*'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlog.py countMutex2.log"
		egrep 'MSG.*ENDTHREAD' countMutex2.log
		egrep 'MSG.*ENDTHREAD' countMutex2.log | tail -1 | cut -d, -f6-9 > countMutex2.out
		diff countMutex2.out countMutex2.ref > countMutex2.dif
		@echo "COMPLETED (OK) SIMULATING (TESTING) countMutex2"


graphs:		$(JPEGFILES)
		-/bin/bash -c "python graphcrunch.py m1 MEAN_lockSum countUnsafe_crunch countAtomic20_crunch countMutex20_crunch countAtomic2_crunch countMutex2_crunch"
		-/bin/bash -c "python graphcrunch.py m1 MEAN_lockDifference countUnsafe_crunch countAtomic20_crunch countMutex20_crunch countAtomic2_crunch countMutex2_crunch"
		-/bin/bash -c "python graphcrunch.py m1 MEAN_TURNAROUNDTIME countUnsafe_crunch countAtomic20_crunch countMutex20_crunch countAtomic2_crunch countMutex2_crunch"
		-mkdir $(ACCTWWW)
		/bin/bash -c "cp -p *.jpg $(ACCTWWW)"
		-/bin/bash -c "cp -p *.png $(ACCTWWW)"
		-/bin/bash -c 'chmod -R o+r+X $(ACCTWWW)'
		@echo "You can browse JPEGS and PNGS in http://acad.kutztown.edu/~$(STUDENT)"

#       makefile for swap3prj2016, problem 3, CSC 343 Operating Systems
#       Dr. Dale Parson. Fall 2016

all:		build

TARGET = swap3prj2016
DEBUG = 1
DPOS := /home/KUTZTOWN/parson/OpSys
DPPY := $(DPOS)/state2codeV12

include ./makelib

clean:		subclean
		-/bin/bash -c 'chmod 666 ~parson/tmp/$(STUDENT)_STM*'
		/bin/bash -c '/bin/rm -f *.out *.dif *.pyc junk parsetab.py *.vmlf *.png *.csv'
		/bin/bash -c '/bin/rm -f *.dot *.gif *.jpg testmachine.ck junk.* *.tmp *.log *.'
		/bin/bash -c '/bin/rm -f *.crunch ~parson/tmp/$(STUDENT)_STM_*.log $(STUDENT)_STM_*.log Unsafe*.log'
		/bin/bash -c '/bin/rm -f rr*.py sjf*.py fcfs*.py plotcrunch.csv *.crunch *_crunch.py *.crunch *_crunch.csv allrr*.py'

testmin:		testrr_ff_min testrr_bf_min testallrr_ff_min testallrr_bf_min testfifo

testmax:		testrr_ff_max testrr_bf_max testallrr_ff_max testallrr_bf_max testfifo

testfifo:	testrr_ff_swap testrr_bf_swap testallrr_ff_swap testallrr_bf_swap

test:		testmin testfifo

csv:
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) plotcrunch.py diffset rr_ff_swap_crunch.py rr_bf_swap_crunch.py allrr_ff_swap_crunch.py allrr_bf_swap_crunch.py"

buildrr_bf_swap:
		@echo 'COMPILING rr_bf_swap'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py rr_bf_swap.stm rr_bf_swap.dot rr_bf_swap.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

testrr_bf_swap:	buildrr_bf_swap
		@echo "SIMULATING (TESTING) rr_bf_swap"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. STMLOGDIR=~parson/tmp time $(PYTHON) rr_bf_swap.py 2 5 1000000 12345 2"
		/bin/bash -c 'chmod 666 ~parson/tmp/$(STUDENT)_STM*'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlog.py rr_bf_swap.log"
		@echo "COMPLETED (OK) SIMULATING (TESTING) rr_bf_swap"

buildrr_ff_swap:
		@echo 'COMPILING rr_ff_swap'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py rr_ff_swap.stm rr_ff_swap.dot rr_ff_swap.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

testrr_ff_swap:	buildrr_ff_swap
		@echo "SIMULATING (TESTING) rr_ff_swap"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. STMLOGDIR=~parson/tmp time $(PYTHON) rr_ff_swap.py 2 5 1000000 12345 2"
		/bin/bash -c 'chmod 666 ~parson/tmp/$(STUDENT)_STM*'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlog.py rr_ff_swap.log"
		@echo "COMPLETED (OK) SIMULATING (TESTING) rr_ff_swap"

buildallrr_bf_swap:
		@echo 'COMPILING allrr_bf_swap'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py allrr_bf_swap.stm allrr_bf_swap.dot allrr_bf_swap.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

testallrr_bf_swap:	buildallrr_bf_swap
		@echo "SIMULATING (TESTING) allrr_bf_swap"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. STMLOGDIR=~parson/tmp time $(PYTHON) allrr_bf_swap.py 2 5 1000000 12345 2"
		/bin/bash -c 'chmod 666 ~parson/tmp/$(STUDENT)_STM*'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlog.py allrr_bf_swap.log"
		@echo "COMPLETED (OK) SIMULATING (TESTING) allrr_bf_swap"

buildallrr_ff_swap:
		@echo 'COMPILING allrr_ff_swap'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py allrr_ff_swap.stm allrr_ff_swap.dot allrr_ff_swap.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

testallrr_ff_swap:	buildallrr_ff_swap
		@echo "SIMULATING (TESTING) allrr_ff_swap"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. STMLOGDIR=~parson/tmp time $(PYTHON) allrr_ff_swap.py 2 5 1000000 12345 2"
		/bin/bash -c 'chmod 666 ~parson/tmp/$(STUDENT)_STM*'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlog.py allrr_ff_swap.log"
		@echo "COMPLETED (OK) SIMULATING (TESTING) allrr_ff_swap"

buildrr_bf_min:
		@echo 'COMPILING rr_bf_min'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py rr_bf_min.stm rr_bf_min.dot rr_bf_min.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

testrr_bf_min:	buildrr_bf_min
		@echo "SIMULATING (TESTING) rr_bf_min"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. STMLOGDIR=~parson/tmp time $(PYTHON) rr_bf_min.py 2 5 1000000 12345 2"
		/bin/bash -c 'chmod 666 ~parson/tmp/$(STUDENT)_STM*'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlog.py rr_bf_min.log"
		@echo "COMPLETED (OK) SIMULATING (TESTING) rr_bf_min"

buildrr_ff_min:
		@echo 'COMPILING rr_ff_min'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py rr_ff_min.stm rr_ff_min.dot rr_ff_min.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

testrr_ff_min:	buildrr_ff_min
		@echo "SIMULATING (TESTING) rr_ff_min"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. STMLOGDIR=~parson/tmp time $(PYTHON) rr_ff_min.py 2 5 1000000 12345 2"
		/bin/bash -c 'chmod 666 ~parson/tmp/$(STUDENT)_STM*'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlog.py rr_ff_min.log"
		@echo "COMPLETED (OK) SIMULATING (TESTING) rr_ff_min"

buildallrr_bf_min:
		@echo 'COMPILING allrr_bf_min'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py allrr_bf_min.stm allrr_bf_min.dot allrr_bf_min.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

testallrr_bf_min:	buildallrr_bf_min
		@echo "SIMULATING (TESTING) allrr_bf_min"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. STMLOGDIR=~parson/tmp time $(PYTHON) allrr_bf_min.py 2 5 1000000 12345 2"
		/bin/bash -c 'chmod 666 ~parson/tmp/$(STUDENT)_STM*'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlog.py allrr_bf_min.log"
		@echo "COMPLETED (OK) SIMULATING (TESTING) allrr_bf_min"

buildallrr_ff_min:
		@echo 'COMPILING allrr_ff_min'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py allrr_ff_min.stm allrr_ff_min.dot allrr_ff_min.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

testallrr_ff_min:	buildallrr_ff_min
		@echo "SIMULATING (TESTING) allrr_ff_min"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. STMLOGDIR=~parson/tmp time $(PYTHON) allrr_ff_min.py 2 5 1000000 12345 2"
		/bin/bash -c 'chmod 666 ~parson/tmp/$(STUDENT)_STM*'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlog.py allrr_ff_min.log"
		@echo "COMPLETED (OK) SIMULATING (TESTING) allrr_ff_min"

buildrr_bf_max:
		@echo 'COMPILING rr_bf_max'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py rr_bf_max.stm rr_bf_max.dot rr_bf_max.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

testrr_bf_max:	buildrr_bf_max
		@echo "SIMULATING (TESTING) rr_bf_max"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. STMLOGDIR=~parson/tmp time $(PYTHON) rr_bf_max.py 2 5 1000000 12345 2"
		/bin/bash -c 'chmod 666 ~parson/tmp/$(STUDENT)_STM*'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlog.py rr_bf_max.log"
		@echo "COMPLETED (OK) SIMULATING (TESTING) rr_bf_max"

buildrr_ff_max:
		@echo 'COMPILING rr_ff_max'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py rr_ff_max.stm rr_ff_max.dot rr_ff_max.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

testrr_ff_max:	buildrr_ff_max
		@echo "SIMULATING (TESTING) rr_ff_max"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. STMLOGDIR=~parson/tmp time $(PYTHON) rr_ff_max.py 2 5 1000000 12345 2"
		/bin/bash -c 'chmod 666 ~parson/tmp/$(STUDENT)_STM*'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlog.py rr_ff_max.log"
		@echo "COMPLETED (OK) SIMULATING (TESTING) rr_ff_max"

buildallrr_bf_max:
		@echo 'COMPILING allrr_bf_max'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py allrr_bf_max.stm allrr_bf_max.dot allrr_bf_max.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

testallrr_bf_max:	buildallrr_bf_max
		@echo "SIMULATING (TESTING) allrr_bf_max"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. STMLOGDIR=~parson/tmp time $(PYTHON) allrr_bf_max.py 2 5 1000000 12345 2"
		/bin/bash -c 'chmod 666 ~parson/tmp/$(STUDENT)_STM*'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlog.py allrr_bf_max.log"
		@echo "COMPLETED (OK) SIMULATING (TESTING) allrr_bf_max"

buildallrr_ff_max:
		@echo 'COMPILING allrr_ff_max'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py allrr_ff_max.stm allrr_ff_max.dot allrr_ff_max.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

testallrr_ff_max:	buildallrr_ff_max
		@echo "SIMULATING (TESTING) allrr_ff_max"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. STMLOGDIR=~parson/tmp time $(PYTHON) allrr_ff_max.py 2 5 1000000 12345 2"
		/bin/bash -c 'chmod 666 ~parson/tmp/$(STUDENT)_STM*'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlog.py allrr_ff_max.log"
		@echo "COMPLETED (OK) SIMULATING (TESTING) allrr_ff_max"

graphs:		$(JPEGFILES)
		/bin/bash -c "python graphcrunch.py m1 MEAN_running rr_ff_swap_crunch rr_bf_swap_crunch allrr_ff_swap_crunch allrr_bf_swap_crunch rr_ff_min_crunch rr_bf_min_crunch allrr_ff_min_crunch allrr_bf_min_crunch rr_ff_max_crunch rr_bf_max_crunch allrr_ff_max_crunch allrr_bf_max_crunch"
		/bin/bash -c "python graphcrunch.py m1 MEAN_waitForMemory rr_ff_swap_crunch rr_bf_swap_crunch allrr_ff_swap_crunch allrr_bf_swap_crunch rr_ff_min_crunch rr_bf_min_crunch allrr_ff_min_crunch allrr_bf_min_crunch rr_ff_max_crunch rr_bf_max_crunch allrr_ff_max_crunch allrr_bf_max_crunch"
		/bin/bash -c "python graphcrunch.py m1 MEAN_checkIfMemory rr_ff_swap_crunch rr_bf_swap_crunch allrr_ff_swap_crunch allrr_bf_swap_crunch rr_ff_min_crunch rr_bf_min_crunch allrr_ff_min_crunch allrr_bf_min_crunch rr_ff_max_crunch rr_bf_max_crunch allrr_ff_max_crunch allrr_bf_max_crunch"
		/bin/bash -c "python graphcrunch.py m1 SUM_waitForMemory rr_ff_swap_crunch rr_bf_swap_crunch allrr_ff_swap_crunch allrr_bf_swap_crunch rr_ff_min_crunch rr_bf_min_crunch allrr_ff_min_crunch allrr_bf_min_crunch rr_ff_max_crunch rr_bf_max_crunch allrr_ff_max_crunch allrr_bf_max_crunch"
		/bin/bash -c "python graphcrunch.py m1 SUM_checkIfMemory rr_ff_swap_crunch rr_bf_swap_crunch allrr_ff_swap_crunch allrr_bf_swap_crunch rr_ff_min_crunch rr_bf_min_crunch allrr_ff_min_crunch allrr_bf_min_crunch rr_ff_max_crunch rr_bf_max_crunch allrr_ff_max_crunch allrr_bf_max_crunch"
		/bin/bash -c "python graphcrunch.py m1 SUM_GETMEMORY rr_ff_swap_crunch rr_bf_swap_crunch allrr_ff_swap_crunch allrr_bf_swap_crunch rr_ff_min_crunch rr_bf_min_crunch allrr_ff_min_crunch allrr_bf_min_crunch rr_ff_max_crunch rr_bf_max_crunch allrr_ff_max_crunch allrr_bf_max_crunch"
		-mkdir $(ACCTWWW)
		ls $(JPEGFILES) *png
		cp -p $(JPEGFILES) *png $(ACCTWWW)
		-chmod -R o+r+X $(ACCTWWW)
		grep SUM_GETMEMORY *_crunch*.py | sort --field-separator== -k 2
		@echo "You can browse JPEGS in http://acad.kutztown.edu/~$(STUDENT)"

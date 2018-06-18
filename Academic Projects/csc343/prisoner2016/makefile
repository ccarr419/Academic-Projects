#       makefile for swapping2016, problem 3, CSC 343 Operating Systems
#       Dr. Dale Parson. Fall 2015

all:		build

TARGET = prisonerd2016
DEBUG = 1
DPOS := /home/KUTZTOWN/parson/OpSys
DPPY := $(DPOS)/state2codeV12

include ./makelib

clean:		subclean
		-/bin/bash -c 'chmod 666 ~parson/tmp/$(STUDENT)_STM*'
		/bin/bash -c '/bin/rm -f *.out *.dif *.pyc junk parsetab.py *.vmlf prisonerd2016_crunch.png'
		/bin/bash -c '/bin/rm -f *.dot *.gif *.jpg testmachine.ck junk.* *.tmp *.log prisonerd2016.py'
		/bin/bash -c '/bin/rm -f *.crunch ~parson/tmp/$(STUDENT)_STM_*.log $(STUDENT)_STM_*.log Unsafe*.log'
		/bin/bash -c '/bin/rm -f rr*.py sjf*.py fcfs*.py plotcrunch.csv *.crunch *_crunch.py *.crunch *_crunch.csv'

test:		test_prisonerd2016

csv:
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) plotcrunch.py diffset prisonerd2016_crunch.py 

build:
		@echo 'COMPILING prisonerd2016'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py prisonerd2016.stm prisonerd2016.dot prisonerd2016.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

test_prisonerd2016:	build
		@echo "SIMULATING (TESTING) prisonerd2016"
		/bin/rm -f ~parson/tmp/$(STUDENT)_STM_*.log $(STUDENT)_STM_*.log prisonerd2016.log
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. STMLOGDIR=~parson/tmp time $(PYTHON) prisonerd2016.py 2 4 500 12345 2"
		/bin/bash -c 'chmod 666 ~parson/tmp/$(STUDENT)_STM*'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlog.py prisonerd2016.log"
		# STUDENT, COMMENT OUT NEXT LINE TO SEE THE LOG FILE.
		# bash -c '/bin/rm -f ~parson/tmp/$(STUDENT)_STM_*.log $(STUDENT)_STM_*.log prisonerd2016*.log'
		@echo "COMPLETED (OK) SIMULATING (TESTING) prisonerd2016"

graphs:		$(JPEGFILES)
		-/bin/bash -c "python graphcrunch.py f1 prisonerd2016_crunch SUM_timeInJail_thread_0_process_0 SUM_timeInJail_thread_1_process_0 SUM_timeInJail_thread_0_process_1 SUM_timeInJail_thread_1_process_1 SUM_timeInJail_thread_0_process_2 SUM_timeInJail_thread_1_process_2 SUM_timeInJail_thread_0_process_3 SUM_timeInJail_thread_1_process_3 SUM_timeInJail_thread_0_process_4 SUM_timeInJail_thread_1_process_4 SUM_timeInJail_thread_0_process_5 SUM_timeInJail_thread_1_process_5 SUM_timeInJail_thread_0_process_6 SUM_timeInJail_thread_1_process_6 SUM_timeInJail_thread_0_process_7 SUM_timeInJail_thread_1_process_7 SUM_timeInJail_thread_0_process_8 SUM_timeInJail_thread_1_process_8 SUM_timeInJail_thread_0_process_9 SUM_timeInJail_thread_1_process_9"
		-mkdir $(ACCTWWW)
		cp -p prisonerd2016.jpg $(ACCTWWW)
		-cp -p prisonerd2016_crunch.png $(ACCTWWW)
		-/bin/bash -c 'chmod -R o+r+X $(ACCTWWW)'
		@echo "You can browse JPEGS and PNGS in http://acad.kutztown.edu/~$(STUDENT)"

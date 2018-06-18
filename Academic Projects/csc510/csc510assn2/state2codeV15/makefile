#       makefile for state2codeV15 project
#       Dr. Dale Parson. Fall 2013, Fall 2014

all:		build

TARGET = state2codeV15
DEBUG = 1
# DPOS := ~parson/OpSys
DPOS := ..
DPPY := $(DPOS)/state2codeV15
# STUDENT - CHANGE SIMLOGLEVEL FROM 2 TO 3 if your program crashes and is
# losing diagnostic msg()s at the time of crash. Level 3 will flush every
# msg() to disk when it is called, but flush makes it run VERY SLOWLY.
# Update 7/12/2017, level 3 is OK now, acad & snape were mounting with 'sync',
# without that it runs fine at level 3.
SIMLOGLEVEL = 3

include ./makelib

build:		buildCPUsched buildPaging

clean:		subclean
		/bin/rm -f *.out *.dif *.pyc junk parsetab.py *.vmlf *.csv
		/bin/rm -f *.dot *.gif *.jpg testmachine.ck junk.* *.tmp *.log *.png
		/bin/rm -f rr.py rr_fifopage.py sjf.py fcfs.py STM.doc.txt.tmp
		/bin/rm -f sjfEstimate.py srtfEstimate.py
		/bin/rm -f rr_lrupage.py rr_lrupage_dirty.py *.crunch
		/bin/rm -f elmu2013_ai.ck test343.py testjoinwait.py test343multi.py process_states.py
		/bin/rm -f test343SLOW.py 
		/bin/rm -f /tmp/$(STUDENT)_STM_*.log $(STUDENT)_STM_*.log
		/bin/rm -f test343subgraph.py
		/bin/rm -f demo1fall2015/CSC343Compile.py
		cd ./demo1fall2015 && make clean

test:		testbasic test343 testjoinwait test343multi test343subgraph teststm1 testCPUsched testPaging
		/bin/rm -f demo1fall2015/CSC343Compile.py
		ln CSC343Compile.py demo1fall2015/CSC343Compile.py && cd ./demo1fall2015 && $(MAKE) clean
		cd ./demo1fall2015 && $(MAKE) test

testbasic:
		$(PYTHON) State2CodeParser.py testmachine.txt testmachine.dot
		diff testmachine.dot testmachine.dot.ref > testmachine.dot.dif
		$(PYTHON) State2CodeParser.py testmachine.txt testmachine.dot testmachine.ck State2ChuckMidi State2ChuckMidi
		diff testmachine.dot testmachine.dot.ref > testmachine.dot.dif
		diff testmachine.ck testmachine.ck.ref > testmachine.ck.dif
		$(PYTHON) State2CodeParser.py elmu2013_ai.txt elmu2013_ai.dot elmu2013_ai.ck State2ChuckMidi State2ChuckMidi
		diff elmu2013_ai.dot elmu2013_ai.dot.ref > elmu2013_ai.dot.dif
		diff elmu2013_ai.ck elmu2013_ai.ck.ref > elmu2013_ai.ck.dif

test343:
		@echo COMPILING
		$(PYTHON) State2CodeParser.py test343.stm test343.dot test343.py CSC343Compile CSC343Compile
		diff test343.dot test343.dot.ref > test343.dot.dif
		diff test343.py test343.py.ref > test343.py.dif
		@echo SIMULATING
		$(PYTHON) test343.py 2 2 100 12345 $(SIMLOGLEVEL)
		diff test343.log test343.log.ref > test343.log.dif

test343SLOW:
		@echo COMPILING
		$(PYTHON) State2CodeParser.py test343SLOW.stm test343SLOW.dot test343SLOW.py CSC343Compile CSC343Compile
		diff test343SLOW.py test343SLOW.py.ref > test343SLOW.py.dif
		@echo SIMULATING
		$(PYTHON) test343SLOW.py 2 2 3000000 12345 $(SIMLOGLEVEL)
		diff test343SLOW.log ~parson/OpSys/test343SLOW.log.ref > test343SLOW.log.dif

testjoinwait:
		@echo COMPILING
		$(PYTHON) State2CodeParser.py testjoinwait.stm testjoinwait.dot testjoinwait.py CSC343Compile CSC343Compile
		@echo SIMULATING
		$(PYTHON) testjoinwait.py 2 2 10000 12345 $(SIMLOGLEVEL)
		diff testjoinwait.log testjoinwait.log.ref > testjoinwait.log.dif

test343multi:
		@echo COMPILING
		$(PYTHON) State2CodeParser.py test343multi.stm test343multi.dot test343multi.py CSC343Compile CSC343Compile
		diff test343multi.dot test343multi.dot.ref > test343multi.dot.dif
		diff test343multi.py test343multi.py.ref > test343multi.py.dif
		@echo SIMULATING
		$(PYTHON) test343multi.py 2 2 100 12345 $(SIMLOGLEVEL)
		diff test343multi.log test343multi.log.ref > test343multi.log.dif

test343subgraph:
		@echo COMPILING
		$(PYTHON) State2CodeParser.py test343subgraph.stm test343subgraph.dot test343subgraph.py CSC343Compile CSC343Compile
		diff test343subgraph.dot test343subgraph.dot.ref > test343subgraph.dot.dif
		diff test343subgraph.py test343subgraph.py.ref > test343subgraph.py.dif
		@echo SIMULATING
		$(PYTHON) test343subgraph.py 2 2 100 12345 $(SIMLOGLEVEL)
		diff test343subgraph.log test343subgraph.log.ref > test343subgraph.log.dif

teststm1:
		@echo COMPILING
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py process_states.stm process_states.dot process_states.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"
		@echo "SIMULATING (TESTING)"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) process_states.py 2 2 10000 12345 $(SIMLOGLEVEL)"
		diff process_states.log process_states.log.ref > process_states.log.dif

graphs:		$(JPEGFILES)
		-/bin/bash -c "$(PYTHONLOWCPU) graphcrunch.py m1 MEAN_ready fcfs_crunch sjf_crunch sjfEstimate_crunch rr_crunch"
		-/bin/bash -c "$(PYTHONLOWCPU) graphcrunch.py m1 MIN_ready fcfs_crunch sjf_crunch sjfEstimate_crunch rr_crunch"
		-/bin/bash -c "$(PYTHONLOWCPU) graphcrunch.py m1 MAX_ready fcfs_crunch sjf_crunch sjfEstimate_crunch rr_crunch"
		-/bin/bash -c "$(PYTHONLOWCPU) graphcrunch.py m1 MEAN_running fcfs_crunch sjf_crunch sjfEstimate_crunch rr_crunch"
		-/bin/bash -c "$(PYTHONLOWCPU) graphcrunch.py m1 MIN_running fcfs_crunch sjf_crunch sjfEstimate_crunch rr_crunch"
		-/bin/bash -c "$(PYTHONLOWCPU) graphcrunch.py m1 MAX_running fcfs_crunch sjf_crunch sjfEstimate_crunch rr_crunch"
		-mkdir $(ACCTWWW)
		cp -p $(JPEGFILES) $(ACCTWWW)
		-chmod -R o+r+X $(ACCTWWW)
		@echo "You can browse JPEGS in http://acad.kutztown.edu/~$(STUDENT)"

buildCPUsched:	buildfcfs buildsjf buildrr buildsjfEstimate buildsrtfEstimate

buildfcfs:
		@echo 'COMPILING fcfs'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py fcfs.stm fcfs.dot fcfs.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

testCPUsched:		testfcfs testsjf testrr testsjfEstimate

testfcfs:	buildfcfs
		@echo "SIMULATING (TESTING) fcfs"
		# /bin/rm -f *.tmp *.log *.dif
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. time $(PYTHON) fcfs.py 2 4 110000 12345 $(SIMLOGLEVEL)"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlogV3.py fcfs.log"
		@echo "TESTING COMPLETED"

buildsjf:
		@echo 'COMPILING sjf'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py sjf.stm sjf.dot sjf.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

testsjf:	buildsjf
		@echo "SIMULATING (TESTING) sjf"
		# /bin/rm -f *.tmp *.log *.dif
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. time $(PYTHON) sjf.py 2 4 110000 12345 $(SIMLOGLEVEL)"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlogV3.py sjf.log"
		@echo "TESTING COMPLETED"

buildsjfEstimate:
		@echo 'COMPILING sjfEstimate'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py sjfEstimate.stm sjfEstimate.dot sjfEstimate.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

testsjfEstimate:	buildsjfEstimate
		@echo "SIMULATING (TESTING) sjfEstimate"
		# /bin/rm -f *.tmp *.log *.dif
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. time $(PYTHON) sjfEstimate.py 2 4 110000 12345 $(SIMLOGLEVEL)"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlogV3.py sjfEstimate.log"
		@echo "TESTING COMPLETED"

buildsrtfEstimate:
		@echo 'COMPILING srtfEstimate'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py srtfEstimate.stm srtfEstimate.dot srtfEstimate.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

testsrtfEstimate:	buildsrtfEstimate
		@echo "SIMULATING (TESTING) srtfEstimate"
		# /bin/rm -f *.tmp *.log *.dif
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. time $(PYTHON) srtfEstimate.py 2 4 110000 12345 $(SIMLOGLEVEL)"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlogV3.py srtfEstimate.log"
		@echo "TESTING COMPLETED"

buildrr:
		@echo 'COMPILING rr'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py rr.stm rr.dot rr.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

testrr:	buildrr
		@echo "SIMULATING (TESTING) rr"
		# /bin/rm -f *.tmp *.log *.dif
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. time $(PYTHON) rr.py 2 4 110000 12345 $(SIMLOGLEVEL)"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlogV3.py rr.log"
		@echo "TESTING COMPLETED"

buildPaging:	buildrr_fifopage buildrr_lrupage buildrr_lrupage_dirty

buildrr_fifopage:
		@echo 'COMPILING rr_fifopage'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py rr_fifopage.stm rr_fifopage.dot rr_fifopage.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

buildrr_lrupage:
		@echo 'COMPILING rr_lrupage'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py rr_lrupage.stm rr_lrupage.dot rr_lrupage.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

buildrr_lrupage_dirty:
		@echo 'COMPILING rr_lrupage_dirty'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py rr_lrupage_dirty.stm rr_lrupage_dirty.dot rr_lrupage_dirty.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

testPaging:		testrr_fifopage testrr_lrupage testrr_lrupage_dirty

testrr_fifopage:	buildrr_fifopage
		@echo "SIMULATING (TESTING) rr_fifopage"
		# /bin/rm -f *.tmp *.log *.dif
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. time $(PYTHON) rr_fifopage.py 2 5 120000 12345 $(SIMLOGLEVEL)"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlogV4.py rr_fifopage.log"
		grep 'MEAN_waiting_paging=' *.crunch
		@echo "TESTING COMPLETED"

testnew:	test1_2013 test2_2013

test1_2013:	testrr_lrupage

testrr_lrupage:	buildrr_lrupage
		@echo "SIMULATING (TESTING) rr_lrupage"
		# /bin/rm -f *.tmp *.log *.dif
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. time $(PYTHON) rr_lrupage.py 2 5 120000 12345 $(SIMLOGLEVEL)"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlogV4.py rr_lrupage.log"
		grep 'MEAN_waiting_paging=' *.crunch
		@echo "TESTING COMPLETED"

test2_2013:	testrr_lrupage_dirty

testrr_lrupage_dirty:	buildrr_lrupage_dirty
		@echo "SIMULATING (TESTING) rr_lrupage_dirty"
		# /bin/rm -f *.tmp *.log *.dif
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. time $(PYTHON) rr_lrupage_dirty.py 2 5 120000 12345 $(SIMLOGLEVEL)"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlogV4.py rr_lrupage_dirty.log"
		@echo "TESTING COMPLETED"
		grep 'MEAN_waiting_paging=' *.crunch

doc:
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) ./makedoc.py" > STM.doc.txt.tmp
		@echo "PLEASE EDIT STM.doc.txt.tmp > STM.doc.txt"

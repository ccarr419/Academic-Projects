#       makefile for demo1fall2015, demo 1 for CSC 343 Operating Systems
#       Dr. Dale Parson. Fall 2015

all:		build

TARGET = demo1fall2015
DEBUG = 1
# DPOS := ~parson/OpSys
DPOS := ../..
DPPY := $(DPOS)/state2codeV15

include ../makelib

clean:		subclean
		/bin/rm -f *.out *.dif *.pyc junk parsetab.py *.vmlf
		/bin/rm -f *.dot *.gif *.jpg testmachine.ck junk.* *.tmp *.log
		/bin/rm -f Human1STM.py *.crunch /tmp/$(STUDENT)_STM_*.log $(STUDENT)_STM_*.log

build:
		@echo 'COMPILING Human1STM'
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) $(DPPY)/State2CodeParser.py Human1STM.stm Human1STM.dot Human1STM.py CSC343Compile CSC343Compile"
		@echo "COMPILING COMPLETED"

test:		build
		@echo "SIMULATING (TESTING) Human1STM"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. time $(PYTHON) Human1STM.py 2 4 876000 12345 2"
		/bin/bash -c "PYTHONPATH=$(DPOS):.:.. $(PYTHON) crunchlog.py Human1STM.log"
		@echo "TESTING COMPLETED"

graphs:		$(JPEGFILES)
		-mkdir $(ACCTWWW)
		cp -p $(JPEGFILES) $(ACCTWWW)
		-chmod -R o+r+X $(ACCTWWW)
		@echo "You can browse JPEGS in http://acad.kutztown.edu/~$(STUDENT)"

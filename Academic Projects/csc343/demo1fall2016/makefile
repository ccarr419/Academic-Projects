#       makefile for demo1fall2016, demo 1 for CSC 343 Operating Systems
#       Dr. Dale Parson. Fall 2016

all:		build

TARGET = demo1fall2016
DEBUG = 1
DPOS := /home/KUTZTOWN/parson/OpSys
DPPY := $(DPOS)/state2codeV10

include ./makelib

clean:		subclean
		/bin/rm -f *.out *.dif *.pyc junk parsetab.py *.vmlf *.png
		/bin/rm -f *.dot *.gif *.jpg testmachine.ck junk.* *.tmp *.log
		/bin/rm -f Human1STM.py *.crunch *_crunch.py /tmp/$(STUDENT)_STM_*.log $(STUDENT)_STM_*.log *_crunch.csv

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
		/bin/bash -c "python graphcrunch.py f1 Human1STM_crunch MEAN_infant MEAN_teen MEAN_youngAdult MEAN_midLife MEAN_gettingOld"
		-mkdir $(ACCTWWW)
		-cp -p $(JPEGFILES) *.png $(ACCTWWW)
		-chmod -R o+r+X $(ACCTWWW)
		-ls -l *png $(JPEGFILES)
		@echo "You can browse JPEGS and PNGS in http://acad.kutztown.edu/~$(STUDENT)"
		@echo "Run 'eog *jpg *png' to view all generated graphs."

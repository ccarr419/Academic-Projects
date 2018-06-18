#       makefile for stepvmInC project
#       Dr. Dale Parson. Fall 2017

all:		test

TARGET = prepdata1
PARSONFILES = /home/KUTZTOWN/parson/DataMine

include ./makelib

clean:		subclean
		/bin/rm -f *.out *.o *.arff *.dif *.out
		# Remove the symbolic links
		/bin/rm -f lsTOarff.arff.ref
		/bin/rm -f lsTOarff.rawtestdata.txt
		/bin/rm -f psTOarff.arff.ref
		/bin/rm -f psTOarff.rawtestdata.txt

build:	

# Set LSSTRINGTONOMINAL for the attributes to StringToNominal convert.
LSSTRINGTONOMINAL = 1,12,13,17

test:	testps

testall:	clean testls testps

testps:
		# Install low-space symbolic links for input & reference files.
		/bin/ln -s $(PARSONFILES)/psTOarff.rawtestdata.txt ./psTOarff.rawtestdata.txt
		/bin/ln -s $(PARSONFILES)/psTOarff.arff.ref ./psTOarff.arff.ref
		$(PYTHON) ./psTOarff.py  /home/KUTZTOWN/parson/DataMine/psTOarff.rawtestdata.txt  psTOarff.arff
		grep -v "created at" < psTOarff.arff > psTOarff.out
		diff psTOarff.out $(PARSONFILES)/psTOarff.arff.ref > psTOarff.dif
		# Convert UID, TTY, and CMD strings to nominals
		java -cp /home/KUTZTOWN/parson/weka/weka-3-8-1/weka.jar "weka.filters.unsupervised.attribute.StringToNominal" -R 1,6,8 -i psTOarff.arff -o psTOarffStrNominals.arff
		# Convert PID and PPID numerics to nominals
		java -cp /home/KUTZTOWN/parson/weka/weka-3-8-1/weka.jar "weka.filters.unsupervised.attribute.NumericToNominal" -R 2,3 -i psTOarffStrNominals.arff -o psTOarffNominals.arff

testls:
		# Install low-space symbolic links for input & reference files.
		/bin/ln -s $(PARSONFILES)/lsTOarff.rawtestdata.txt ./lsTOarff.rawtestdata.txt
		/bin/ln -s $(PARSONFILES)/lsTOarff.arff.ref ./lsTOarff.arff.ref
		$(PYTHON) ./lsTOarff.py  /home/KUTZTOWN/parson/DataMine/lsTOarff.rawtestdata.txt  lsTOarff.arff
		grep -v "created at" < lsTOarff.arff > lsTOarff.out
		diff lsTOarff.out $(PARSONFILES)/lsTOarff.arff.ref > lsTOarff.dif
		# Running weka from the command line.
		# See http://www.cs.waikato.ac.nz/~remco/weka_bn/node13.html
		# http://weka.wikispaces.com/Primer also useful for command line.
		java -cp /home/KUTZTOWN/parson/weka/weka-3-8-1/weka.jar "weka.filters.unsupervised.attribute.StringToNominal" -R $(LSSTRINGTONOMINAL) -i lsTOarff.arff -o lsTOarffNominals.arff

# target to build preliminary input data file for psTOarff.py
who:
		./makewho.sh > ./psTOarff.rawtestdata.txt
		echo "cp ./psTOarff.rawtestdata.txt TO ~/DataMine/psTOarff.rawtestdata.txt for assn1"

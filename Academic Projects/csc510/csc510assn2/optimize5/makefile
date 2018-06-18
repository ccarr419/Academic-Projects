#       makefile for optimize5 project
#       Programming Assignment 3, CSC526, Spring 2012, Dr. Dale Parson.
#       Added ability to pass args to the JVM's VM via test_parser.py args.
#       Set bash env variable JVMVMARGS for passing to test_parser.py.
#       See below.

all:		build

TARGET = optimize5
DEBUG = 1

include ./makelib

build:

clean:		subclean
		/bin/rm -f *.out *.dif *.pyc junk parsetab.py *.vmlf
		# cd ./stepvmSub && $(MAKE) clean
		# cd ./stepvmToken && $(MAKE) clean
		# Moved the .ref files to Parson's account to save space.
		# They get linked here from ~parson/OpSys/optimize5 via ../runassn2.sh

test:		testparson testbugfix testvectors testbenchmarks testo1 testo2 testpara teststudent

# Assignment 2 in csc510 fall 2017 uses the VM via the jar files.
# We will link to a frozen VM in Parson's account.
# testvm:
			# cd ./stepvmSub && $(MAKE) test
			# cd ./stepvmToken && $(MAKE) test

testparson:
		/usr/bin/python test_parser.py program0.txt program0.vmlf program0.debug.out O1 > program0.out 2>program0.err.out
		# diff program0.out program0.ref  > program0.dif
		/usr/bin/python test_parser.py program1.txt program1.vmlf program1.debug.out > program1.out 2>program1.err.out
		# diff program1.out program1.ref  > program1.dif
		# -diff program1.debug.out program1.debug.ref > program1.debug.dif
		-/usr/bin/python test_parser.py program2.txt program2.vmlf > program2.out 2>program2.err.out
		# diff program2.out program2.ref  > program2.dif
		/usr/bin/python test_parser.py program3.txt program3.vmlf program3.debug.out > program3.out 2>program3.err.out
		# diff program3.out program3.ref  > program3.dif
		# -diff program3.debug.out program3.debug.ref  > program3.debug.dif
		/usr/bin/python test_parser.py program4.txt program4.vmlf program4.debug.out > program4.out 2>program4.err.out
		# diff program4.out program4.ref  > program4.dif
		# -diff program4.debug.out program4.debug.ref  > program4.debug.dif
		/usr/bin/python test_parser.py program5.txt program5.vmlf program5.debug.out > program5.out 2>program5.err.out
		# diff program5.out program5.ref  > program5.dif
		# -diff program5.debug.out program5.debug.ref  > program5.debug.dif
		/usr/bin/python test_parser.py program6.txt program6.vmlf program6.debug.out > program6.out 2>program6.err.out
		# diff program6.out program6.ref  > program6.dif
		# -diff program6.debug.out program6.debug.ref  > program6.debug.dif

teststudent:
		echo "Add some STUDENT tests here."

testbugfix:
		/usr/bin/python test_parser.py program7.txt program7.vmlf program7.debug.out > program7.out 2>program7.err.out
		# diff program7.out program7.ref  > program7.dif
		# -diff program7.debug.out program7.debug.ref  > program7.debug.dif

testvectors:
		bash ./isPythonNotBill
		/usr/bin/python test_parser.py program8.txt program8.vmlf program8.debug.out O0 > program8.out 2>program8.err.out
		# diff program8.out program8.ref  > program8.dif
		# -diff program8.debug.out program8.debug.ref  > program8.debug.dif
		/usr/bin/python test_parser.py program9.txt program9.vmlf program9.debug.out O0 > program9.out 2>program9.err.out
		# diff program9.out program9.ref  > program9.dif
		# -diff program9.debug.out program9.debug.ref  > program9.debug.dif

testbenchmarks:
		bash ./isPythonNotBill
		sh -c "/usr/bin/python test_parser.py program10.txt program10.vmlf program10.debug.out O0 > program10.out 2>program10.err.out"
		# diff program10.out program10.ref  > program10.dif
		# -diff program10.debug.out program10.debug.ref  > program10.debug.dif
		grep TIME program10.err.out
		sh -c "/usr/bin/python test_parser.py program10.txt program10_O1.vmlf program10_O1.debug.out O1 > program10.out 2>program10.err.out"
		# diff program10.out program10_O1.ref  > program10.dif
		# -diff program10_O1.debug.out program10_O1.debug.ref  > program10.debug.dif
		grep TIME program10.err.out
		sh -c "/usr/bin/python test_parser.py program10.txt program10_O2.vmlf program10_O2.debug.out O2 > program10.tmp.out 2>program10.err.out"
		sed -e "s/<Recursion.*>/CYCLIC SYMTAB PTR/g" -e "s/[0-9][0-9]*]/NNN]/g" program10.tmp.out > program10.out
		# diff program10.out program10_O2.ref  > program10.dif
		# -diff program10_O2.debug.out program10_O2.debug.ref  > program10.debug.dif
		grep TIME program10.err.out

testo1:
		bash ./isPythonNotBill
		sh -c "/usr/bin/python test_parser.py program4.txt program4_O1.vmlf program4_O1.debug.out O1 > program4.out 2>program4.err.out"
		# diff program4.out program4_O1.ref  > program4.dif
		# -diff program4_O1.debug.out program4_O1.debug.ref  > program4.debug.dif
		grep TIME program4.err.out
		/usr/bin/python test_parser.py program8.txt program8_O1.vmlf program8_O1.debug.out O1 > program8.out 2>program8.err.out
		# diff program8.out program8_O1.ref  > program8.dif
		# -diff program8_O1.debug.out program8_O1.debug.ref  > program8.debug.dif
		sh -c "/usr/bin/python test_parser.py program6.txt program6_O1.vmlf program6_O1.debug.out O1 > program6.out 2>program6.err.out"
		# diff program6.out program6_O1.ref  > program6.dif
		# -diff program6_O1.debug.out program6_O1.debug.ref  > program6.debug.dif
		grep TIME program6.err.out

testo2:
		bash ./isPythonNotBill
		/usr/bin/python test_parser.py program8.txt program8_O2.vmlf program8_O2.debug.out O2 > program8.tmp.out 2>program8.err.out
		sed -e "s/<Recursion.*>/CYCLIC SYMTAB PTR/g" -e "s/[0-9][0-9]*]/NNN]/g" program8.tmp.out > program8.out
		# diff program8.out program8_O2.ref  > program8.dif
		# -diff program8_O2.debug.out program8_O2.debug.ref  > program8.debug.dif
		sh -c "/usr/bin/python test_parser.py program6.txt program6_O2.vmlf program6_O2.debug.out O2 > program6.tmp.out 2>program6.err.out"
		sed -e "s/<Recursion.*>/CYCLIC SYMTAB PTR/g" -e "s/[0-9][0-9]*]/NNN]/g" program6.tmp.out > program6.out
		# diff program6.out program6_O2.ref  > program6.dif
		# -diff program6_O2.debug.out program6_O2.debug.ref  > program6.debug.dif
		grep TIME program6.err.out

testpara:		testmsort testpsort testmergesort

testmsort:
		bash ./isPythonNotBill
		sh -c "/usr/bin/python test_parser.py programqsort1m.txt programqsort1m_O2.vmlf programqsort1m_O2.debug.out O2 1 $$JVMVMARGS > programqsort1m.tmp.out 2>programqsort1m.err.out"
		sed -e "s/<Recursion.*>/CYCLIC SYMTAB PTR/g" -e "s/[0-9][0-9]*]/NNN]/g" programqsort1m.tmp.out > programqsort1m.out
		# diff programqsort1m.out programqsort1m_O2.ref  > programqsort1m.dif
		# -diff programqsort1m_O2.debug.out programqsort1m_O2.debug.ref  > programqsort1m.debug.dif
		grep TIME programqsort1m.err.out

testpsort:
		bash ./isPythonNotBill
		/usr/bin/python test_parser.py collect_reduce.txt collect_reduce.vmlf collect_reduce.debug.out O2 1 > collect_reduce.tmp.out 2>collect_reduce.err.out
		sed -e "s/<Recursion.*>/CYCLIC SYMTAB PTR/g" -e "s/[0-9][0-9]*]/NNN]/g" collect_reduce.tmp.out > collect_reduce.out
		# diff collect_reduce.out collect_reduce.ref  > collect_reduce.dif
		# -diff collect_reduce.debug.out collect_reduce.debug.ref  > collect_reduce.debug.dif
		time sh -c "/usr/bin/python test_parser.py programqsort1p.txt programqsort1p_O2.vmlf programqsort1p_O2.debug.out O2 1 $$JVMVMARGS > programqsort1p.tmp.out 2>programqsort1p.err.out"
		sed -e "s/<Recursion.*>/CYCLIC SYMTAB PTR/g" -e "s/[0-9][0-9]*]/NNN]/g" programqsort1p.tmp.out > programqsort1p.out
		# diff programqsort1p.out programqsort1p_O2.ref  > programqsort1p.dif
		# -diff programqsort1p_O2.debug.out programqsort1p_O2.debug.ref  > programqsort1p.debug.dif
		grep TIME programqsort1p.err.out
		-/usr/bin/python test_parser.py programqsort1p_crash.txt programqsort1p_crash.vmlf programqsort1p__crash.debug.out O2 1 > programqsort1p_crash.out 2>programqsort1p_crash.err.out

testmergesort:	clean
		bash ./isPythonNotBill
		time /usr/bin/python test_parser.py mergeSort.txt mergeSort.vmlf /dev/null O2 1 $$JVMVMARGS > mergeSort.tmp.out 2>/dev/null
		sed -e "s/<Recursion.*>/CYCLIC SYMTAB PTR/g" -e "s/[0-9][0-9]*]/NNN]/g" mergeSort.tmp.out > mergeSort.out
		# diff mergeSort.out mergeSort.ref  > mergeSort.dif
		# -diff mergeSort.debug.out mergeSort.debug.ref  > mergeSort.debug.dif
		# grep TIME mergeSort.err.out
		time /usr/bin/python test_parser.py pmergeSort.txt pmergeSort.vmlf /dev/null O2 1 $$JVMVMARGS > pmergeSort.tmp.out 2>/dev/null
		sed -e "s/<Recursion.*>/CYCLIC SYMTAB PTR/g" -e "s/[0-9][0-9]*]/NNN]/g" pmergeSort.tmp.out > pmergeSort.out
		# diff pmergeSort.out pmergeSort.ref  > pmergeSort.dif
		# -diff pmergeSort.debug.out pmergeSort.debug.ref  > pmergeSort.debug.dif
		# grep TIME pmergeSort.err.out
		/usr/bin/python test_parser.py mergeSortMinCopy.txt mergeSortMinCopy.vmlf /dev/null O2 1 $$JVMVMARGS > mergeSortMinCopy.tmp.out 2>/dev/null
		sed -e "s/<Recursion.*>/CYCLIC SYMTAB PTR/g" -e "s/[0-9][0-9]*]/NNN]/g" mergeSortMinCopy.tmp.out > mergeSortMinCopy.out
		# diff mergeSortMinCopy.out mergeSortMinCopy.ref  > mergeSortMinCopy.dif
		# -diff mergeSortMinCopy.debug.out mergeSortMinCopy.debug.ref  > mergeSortMinCopy.debug.dif
		# grep TIME mergeSortMinCopy.err.out
		time /usr/bin/python test_parser.py pmergeSortMinCopy.txt pmergeSortMinCopy.vmlf /dev/null O2 1 $$JVMVMARGS > pmergeSortMinCopy.tmp.out 2>/dev/null
		sed -e "s/<Recursion.*>/CYCLIC SYMTAB PTR/g" -e "s/[0-9][0-9]*]/NNN]/g" pmergeSortMinCopy.tmp.out > pmergeSortMinCopy.out
		# diff pmergeSortMinCopy.out pmergeSortMinCopy.ref  > pmergeSortMinCopy.dif
		# -diff pmergeSortMinCopy.debug.out pmergeSortMinCopy.debug.ref  > pmergeSortMinCopy.debug.dif
		# grep TIME pmergeSortMinCopy.err.out

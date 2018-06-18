# Module test_parser tests package optimize5 module progcalc.
# CSC 425 assignment 4, Fall 2011, PLY grammar and parse tree of
# Python nested lists and Python symbol tables.
# Extended assignment 5 to test output from a working compiler for a
# DirectThreadedVM virtual machine.
# Updated for assignment 3 Spring 2012 Compiler II to use Java-based stepvm.
# Updated for assignment 4 Spring 2012 Compiler II to use multithreading.

from optimize5.progcalc import compile
from optimize5.TypeChecks import printSymtab
from sys import argv, stdin, stdout, stderr, exit
from pprint import PrettyPrinter
import re
import sys
import os
__commentPattern__ = re.compile("^((\s*)|(\s*#.*))$")
printer = PrettyPrinter(indent=4, width=80, stream=stdout)

if __name__=='__main__':
    tty = open('/dev/tty', 'w');
    exitstatus = 0
    rfilehandle = None
    # Do this only if this module is executed as the main module.
    rfilehandle = None
    debugfile = None
    optimizationLevel = 0
    numberContexts = 1
    jvmCmdArgs = ""
    if (len(argv) > 2):
        rfilehandle = open(argv[1], "rU") # portable linefeed handling
        objfilename = argv[2]
        objfilehandle = open(objfilename, "w")
        if (len(argv) > 3):
            debugfile = open(argv[3], "w")
            if (len(argv) > 4):
                if argv[4].startswith('O'):
                    optimizationLevel = int(argv[4][1:])
                    if (optimizationLevel < 0 or optimizationLevel > 2):
                        sys.stderr.write("Optimimization level "    \
                            + str(optimizationLevel) + " not supported.\n")
                        sys.exit(1)
                else:
                    sys.stderr.write("Invalid optimization argument: "  \
                        + argv[4])
                    sys.exit(1)
                if (len(argv) > 5):
                    numberContexts = int(argv[5])
                    if (numberContexts < 1):
                        sys.stderr.write("Invalid numberOfContexts argument: " \
                            + str(numberContexts))
                        sys.exit(1)
                    if (len(argv) > 6):
                        jvmCmdArgs = argv[6].strip()
    else:
        stderr.write(
            "Invalid usage, test driver takes two mandatory file names." \
            + '\n')
        exit(1)
    line = rfilehandle.readline()
    buffer = ''
    while (line):
        if (__commentPattern__.match(line)):
            line = "\n"     # Keep line number intact.
        buffer = buffer + line
        line = rfilehandle.readline()
    rfilehandle.close()
    parsetree, opttree, symtab, codeArray, staticDataArray                   \
        = compile(buffer, optimizationLevel, debugfile)
    objfilehandle.write("PROGRAMMEMORY\n" + str(len(codeArray)) + '\n')
    memix = 0
    for opline in codeArray:
        if type(opline) != str:
            sys.stderr.write("WARNING, vmCode[" + str(memix)        \
                + "] is not a string: " + str(type(opline)) + ": "  \
                + str(opline) + '\n')
        objfilehandle.write(str(opline) + '\n')
        memix += 1
    objfilehandle.write("DATAMEMORY\n" + str(len(staticDataArray)) + '\n')
    memix = 0
    for opline in staticDataArray:
        if type(opline) != str:
            sys.stderr.write("WARNING, vmData[" + str(memix)        \
                + "] is not a string: " + str(type(opline)) + ": "  \
                + str(opline) + '\n')
        objfilehandle.write(str(opline) + '\n')
        memix += 1
    objfilehandle.close()
    printer.pprint(parsetree)
    if not opttree is parsetree:
        print "OPTIMIZED", optimizationLevel, "ABSTRACT SYNTAX TREE"
        printer.pprint(opttree)
    printSymtab(symtab)
    print "PROGRAM EXECUTION:"
    try:
        if ((not 'STEPVM' in os.environ)
                or (not os.environ['STEPVM'] in ['Sub', 'Token'])):
            errmsg = ("STEPVM variable unset or invalid: "
                + (os.environ['STEPVM'] if ('STEPVM' in os.environ)
                    else 'None'))
            tty.write(errmsg + '\n')
            raise ValueError, errmsg
        SUBPACKAGE = os.environ['STEPVM']
        CLP = os.environ['CLASSPATH']
        CLP2 = " -cp stepvm" + SUBPACKAGE + ".jar:" + CLP + " "
        cmdstring = "java " + CLP2 + jvmCmdArgs + " optimize5.stepvm"   \
            + SUBPACKAGE \
            + ".StepVM " \
            + " " + objfilename       \
            + " optimize5.stepvm" + SUBPACKAGE + " " + str(numberContexts)  \
            + " 1"
        sys.stderr.write("RUNNING VM: " + cmdstring + '\n')
        sys.stderr.flush()
        sys.stdout.flush()
        tty.write("\nRUNNING VM: " + cmdstring + '\n\n')
        jstat = os.system(cmdstring)
        if jstat:
            sys.stderr.write("VM exited with non-0 status : "   \
                + str(jstat) + '.\n')
            exitstatus = 1
        else:
            sys.stderr.write("VM exited normally.\n");
    except Exception, exstr:
        print "ERROR during VM execution", str(exstr)
        stdout.flush()
        stderr.flush()
        raise       # Re-throw exception that got us here, for stack trace.
    if debugfile:
        debugfile.close()
    tty.close()
    sys.exit(exitstatus)

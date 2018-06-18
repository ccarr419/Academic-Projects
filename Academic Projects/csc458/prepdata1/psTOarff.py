# Modifications By:     Christian Carreras
# Edited Date:          09/29/2017
# Due Date:             10/05/2017
# Assignment:           #1
# File:                 psTOarff.py
# Professor/Author:     Dr. Dale Parson
# Course:               CSC458 Data Mining & Predictive Analytics I
# University:           Kutztown University of Pennylvania
# Major:                CSC Masters Software Delvopment
# Purpose:              The goals of this assignment are to practice using  
#                       Python programming constructs, data types, and its 
#                       regular  expression library to crack apart a textual 
#                       data file  and create an ARFF file amenable to analysis 
#                       with the Weka data mining tool.

#!/usr/bin/python
# psTOarff.py, handout for fall 2017 csc458 assignment 1, complete
# your assignment here, refering to lsTOarff.py as a model.
# OUTPUT FROM RUNNING (ps -fu parson && ps -fu root) IS BELOW.
# NOTES:
# From "man ps":
# TIME     accumulated cpu time, user + system. The display format is
#          usually "MMM:SS", but can be shifted to the right if the
#          process used more than 999 minutes of cpu time.
# C        processor utilization. Currently, this is the integer
#          value of the percent usage over the lifetime of the
#          process. (see %cpu). Parson note: Looks like HH:MM:SS
# 1. There is/are header line(s) starting with UID to be discarded.
# 2. In each line we have the following:
#*2a. 1 or more non-whitespace chars making up the UID, could be numeric string.
# 2b. 1 or more whitespace characters as separators.
#*2c. 1 or more digits as a PID.
# 2d. 1 or more whitespace characters as separators.
#*2e. 1 or more digits as a PPID.
# 2f. 1 or more whitespace characters as separators.
#*2g  1 or more digits as % CPU time.
# 2h. 1 or more whitespace characters as separators.
#*2i. 1 or more non-whitespace as start time, current day or day this year.
# 2j. 1 or more whitespace characters as separators.
#*2k. 1 or more non-whitespace as terminal (TTY), translate '?' to 'detached'
# 2l. 1 or more whitespace characters as separators.
#*2m. TIME in HH:MM:SS format, where each of those is 1 or more digits.
# 2n. 1 or more whitespace characters as separators.
#*2o. Everything up to end of line, including mixed-in spaces, is CMD.
# The 8 symbols - UID PID PPID C STIME TTY TIME CMD - are your attributes.
# You can hard code them and your scanner can ignore those lines in the
# input; you must use a regular expression to detect (match) them, but
# they do not contribute any data. Some of the data fields are numeric,
# some are strings (that we might post-process into nominals using Weka),
# there is at least one date (using non-Weka formats). Each data line
# in this input corresponds to one Weka record, so there is no need to
# accumulate data across multiple lines like there is in lsTOarff.py.
# STUDENT NOTE that there is at least one line giving date of the input file:
# DATE OF DATA DUMP: 2017-07-27

# STUDENT 1: Find the "import" statements in lsTOarff.py and add them here.
# understand why you are importing those Python modules.
import re       # See https://docs.python.org/2/library/re.html
import datetime
import sys      # Needed to read arguments from command line.

# DATE OF DATA DUMP: 2017-07-27
# UID        PID  PPID  C STIME TTY          TIME CMD
# parson   20993 20962  0 17:40 ?        00:00:01 sshd: parson@pts/0
# parson   20994 20993  0 17:40 pts/0    00:00:00 -bash
# parson   25271 20994  0 20:10 pts/0    00:00:00 -bash
# parson   25274 25271  0 20:10 pts/0    00:00:00 ps -fu parson
# UID        PID  PPID  C STIME TTY          TIME CMD
# root         1     0  0 May24 ?        00:00:32 /sbin/init
# root         2     0  0 May24 ?        00:00:00 [kthreadd]
# root         3     2  0 May24 ?        00:00:00 [migration/0]
# root         4     2  0 May24 ?        00:00:08 [ksoftirqd/0]
# root         5     2  0 May24 ?        00:00:00 [stopper/0]
# root         6     2  0 May24 ?        00:00:05 [watchdog/0]
# root         7     2  0 May24 ?        00:00:00 [migration/1]
# ETC.

# STUDENT 2: Define Python dictionaries (also known as maps)
# attrNameToProperties and attrPosToName in lsTOarff.py, and build the
# 8-attribute data dictionary for this assignment within them, similar
# to the 20 attributes in lsTOarff.py. There are no "synthesized attributes"
# such as chlds in lsTOarff.py -- they are synthesized from other lines
# of data in the input file -- each line of input to psTOarff.py bears
# all of its own attributes.
# CAVEAT 1: Store the date attribute in seconds. Scan it in the HH:MM:SS
# (hours:minutes:seconds) format like 00:00:08, but convert that to seconds
# for the ARFF attribute. Do NOT assume that the leading fields are 0s.
# CAVEAT 2: STIME is a date (starting time), to be stored as a date in ARFF.
# It comes in two formats, such as "May24" or "17:40". You can assume the
# current year, and for value like 17:40, assume the current day & year.
# Don't try to use time-of-day data, only the date. See lsTOarff.py's
# handling of date for the date attribute.
# Here we are only defining the data dictionary. These CAVEATS apply
# later, during the data-scanning loop.
attrNameToProperties = {}   # name -> (position, type descriptor string)
attrPosToName = {}          # position starting at 0 -> name

attrNameToProperties["UID"] = (0, "string")
attrPosToName[0] = "UID"

attrNameToProperties["PID"] = (1, "numeric")
attrPosToName[1] = "PID"

attrNameToProperties["PPID"] = (2, "numeric")
attrPosToName[2] = "PPID"

attrNameToProperties["C"] = (3, "numeric")
attrPosToName[3] = "C"

attrNameToProperties["STIME"] = (4, "date")
attrPosToName[4] = "STIME"

attrNameToProperties["TTY"] = (5, "string")
attrPosToName[5] = "TTY"

attrNameToProperties["TIME"] = (6, "numeric")
attrPosToName[6] = "TIME"

attrNameToProperties["CMD"] = (7, "string")
attrPosToName[7] = "CMD"

# STUDENT 3: I am supplying the re (regular expressions) that match the
# output header lines from 'ps', and the DATE OF DATA DUMP line.
# You must supply the re that
# matches the data lines and that captures the data from those lines.
# Yours will have () around the subexpressions that you want to capture.
# NOTES on re meta-characters:
# ^ matches the start of the string; $ matches the end of the string
# + matches one or more of whatever precedes it; * matches zero or more.
# ? matches 0 or 1. The period . matches any one character, so .* matches
# zero or more of any character, and .+ matches one or more of any character.
# I used escape sequences \s+ \S+ \d+ in my solution.
# HERE IS THE SUBEXPRESSION I USED TO MATCH THE STIME date. USE IT:
# (([A-Z][a-z][a-z]\d+)|(\d+:\d+))
# The | is alternation -- it tries to match the left side, or if that fails,
# it tries to match the right. Note that there are 3 ()-delimted groups,
# one of which will always be empty. Those two alternatives are mutually
# exclusive.
__ignorehdr_re__ = re.compile(r'^UID\s+PID\s+PPID\s+C\s+STIME\s+TTY\s+TIME\s+CMD$')
__date_re__ = re.compile(r'^DATE OF DATA DUMP: (\d+)-(\d+)-(\d+)\s*$')
__attributes_re__ = re.compile(r'^(\S+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(([A-Z][a-z][a-z]\d+)|(\d+:\d+))\s+(\S+)\s+((\d+)+:(\d+)+:(\d+)?)\s+(\S.+)$')

# STUDENT 4: Define your __main__ just like lsTOarff.py, but changing
# the name, usage etc. to psTOarrf where needed. You will have exactly
# the same two command line arguments -- the input file in the format
# seen in /home/KUTZTOWN/parson/DataMine/psTOarff.rawtestdata.txt, and
# the output ARFF file format as in psTOarff.arff.ref. You can open &
# read the input file just as in my lsTOarff.py.

# STUDENT 5: The database list of attrvalues lists, the monthmap, and all
# of the line input code of lsTOarff.py corresponds closely to this program.
# There is no chlds data, there is no curdir across-line data, and you have
# only 3 regular expressions, so your main loop's logic should be simpler.
# Look at psTOarff.arff.ref in /home/KUTZTOWN/parson/DataMine/ to see the
# output from my solution.
# Your output must match it exactly.

if __name__ == "__main__":  # This "if" test is true if called from cmd line.
    usage = "USAGE: python psTOarff.py INFILE OUTARFFFILE.arff"
    # STUDENT CODE GOES BELOW.
    if len(sys.argv) != 3:
        # psTOarff.py is included in the list of command line arguments.
        sys.stderr.write("ERROR, Invalid command line: " + str(sys.argv)
            + "\n")
        sys.stderr.write(usage + "\n")
        sys.exit(1) # non-0 exit reports an error
    ofname = sys.argv[2]    # output file name
    if not ofname.endswith(".arff"):
        sys.stderr.write("ERROR, Invalid output file name: " + ofname
            + "\n")
        sys.stderr.write(usage + "\n")
        sys.exit(1) # non-0 exit reports an error

    ifname = sys.argv[1]    # input file name
    ifile = open(ifname, "r")  # open input for for reading,
    ofile = open(ofname, "w")       # output file for writing

    # Maintain the database in a Python list so we can back-patch the
    # chlds (contained children) attribute for directories after
    # counting them. Also map dir/ names to counts.
    # DATA STRUCTURES USED BY THE CODE BELOW:
    database = []   # Forms as a list of lists, one nested list per element.
    #chlds = {}          # maps directory name -> count of contained entries.
    monthmap = {        # Map ls's output -> a two-digit string.
        "Jan" : "01",
        "Feb" : "02",
        "Mar" : "03",
        "Apr" : "04",
        "May" : "05",
        "Jun" : "06",
        "Jul" : "07",
        "Aug" : "08",
        "Sep" : "09",
        "Oct" : "10",
        "Nov" : "11",
        "Dec" : "12"
    }
    linenum = 0                 # Used for error messages, incr for each line.
    line = ifile.readline()
    while line:                 # While not at end-of-input-file:
        line = line.strip()     # Discard leading/trailing white space.
        linenum = linenum + 1
        m = __attributes_re__.match(line) # Is it a regular "ps -fu" entry?
        if m:
            # DATA STRUCTURE attrvalues forms as a list of
            # attribute values to be appended to list database.
            attrvalues = [m.group(1)]    # Start a list attribute values.
            attrvalues.append(m.group(2))  # PID as int
            attrvalues.append(m.group(3))  # PPID as int
            attrvalues.append(m.group(4))  # C as int
            
            datestring = datayear
            if m.group(7):  # This is exact time-of-day, use this year, month and day
                datestring = datestring + "-" + datamonth + "-" + dataday
            else:
                monthname = m.group(5)
                monthname = monthname[0:3]
                if monthmap.has_key(monthname):
                    datestring = datestring + "-" + monthmap[monthname]
                    # Append -01 to -12 to year name.
                    # datestring is now yyyy-MM of yyyy-MM-dd
                else:
                    sys.stderr.write("ERROR, Invalid month in line "
                        + str(linenum) + " IN FILE " + ifname + ": "
                        + monthname + "\n")
                    sys.exit(1)
                day = m.group(6)
                day = day[3:]
                if len(day) == 1:
                    day = "0" + day     # Make a 2-digit string.
                datestring = datestring + "-" + day
                
            # datestring is now yyyy-MM-dd of yyyy-MM-dd
            attrvalues.append(datestring)
            # TTY
            tty = m.group(8)
            if not tty == "?":
                attrvalues.append(m.group(8))
            else:
                attrvalues.append("detached")
            
            # TIME HH-MM-SS converted to total seconds
            total_seconds = (int((m.group(10)))*3600 + int((m.group(11)))*60 + int(m.group(12)))
            attrvalues.append(total_seconds)
            attrvalues.append(m.group(13)) # CMD
            
            # We update chlds count until after we have seen all.
            database.append(attrvalues)
            # list database holds our ARFF database of entries.
            
        elif __date_re__.match(line):
            m = __date_re__.match(line)
            datayear = m.group(1)   # current year
            datamonth = m.group(2)  # current month
            dataday = m.group(3)    # current day
        elif not __ignorehdr_re__.match(line):
            sys.stderr.write("INVALID LINE " + str(linenum)
                + " IN FILE " + ifname + ": "
                + line + "\n")
            sys.exit(1)
        line = ifile.readline()
        
    # WRITE THE DATA TO THE ARFF FILE, STARTING WITH COMMENTS AT THE TOP:
    ofile.write("% " + ofname + " created at " 
        +  str(datetime.datetime.now()) + "\n")
    ofile.write("% " + str(sys.argv) + "\n")    # Comment shows the cmd line.
    ofile.write("@relation " + ofname[0:-5] + "\n") # Do not include ".arff"
    # SORT THE ATTRIBUTE DECLARATIONS BY POSITION 0..N-1, THEN WRITE THEM.
    attrpositions = attrPosToName.keys()    # Get and sort attribute positions.
    attrpositions.sort()    # sort list attrpositions
    for attrindex in attrpositions:
        attrname = attrPosToName[attrindex]
        attrtype = attrNameToProperties[attrname][1]
        ofile.write("@attribute " + attrname + " ")
        if attrtype == "numeric":
            ofile.write("numeric\n")
        elif attrtype == "string":
            ofile.write("string\n")
        elif attrtype == "date":
            ofile.write("date 'yyyy-MM-dd'\n")
    # WRITE THE DATA RECORDS, 1 ROW AT A TIME:
    ofile.write("@data\n")
    # This is where the records in list database are written to ARFF.
    for row in database:
        ofile.write(str(row)[1:-1] + "\n") # Discard leading "[", trailing "]".
    ofile.close()   # Done!
    ifile.close()

#!/usr/bin/python
# lsTOarff.py, D. Parson, Fall 2017, convert (ls -lR `pwd`)
# output to an arff file.

# Regular expressions to match & extract data from strings in module re:
import re       # See https://docs.python.org/2/library/re.html
import datetime
# For ARFF file format see http://www.cs.waikato.ac.nz/ml/weka/arff.html
# See also Python string (str) documentation at that site.
import sys      # Needed to read arguments from command line.

# Students will use this as a model for converting "ps -fu USER" for all
# users logged in into an ARFF file. Format of
# (date --rfc-3339=date && ls -lR `pwd`)
# is like this on Linux(IGNORE LEADING "# "):
# DATE OF DATA DUMP: 2017-07-27
# /home/KUTZTOWN/parson/JavaLang:
# total 447900
# drwxr-xr-x 2 parson csit_faculty      4096 Jan 26  2012 anthem
# -rw-r--r-- 1 parson csit_faculty  12322607 Mar 11  2013 atomgame.11mar2013.zip
# -rw-r--r-- 1 parson csit_faculty  12323720 Apr 12  2013 atomgame.12apr2013.pre354.zip
# -rw-r--r-- 1 parson csit_faculty  12325337 Mar 11  2013 atomgame.12mar2013.zip
# drwxr-xr-x 2 parson csit_faculty      4096 Aug 18  2014 atomimages
# -rw-r--r-- 1 parson csit_faculty  12209281 May 16  2013 atomimages.zip
# drwxr-xr-x 2 parson csit_faculty      4096 Jan 26  2012 audio
# drwxr-xr-x 4 parson csit_faculty      4096 Mar  1 10:22 FillWord5
# LINES ELIDED HERE, THEN:
# drwxr-xr-x 4 parson csit_faculty      4096 Feb 20  2014 xshuffle
# -rw-r--r-- 1 parson csit_faculty    138443 Feb 19  2013 xshuffle.solution.zip
# 
# /home/KUTZTOWN/parson/JavaLang/anthem:
# total 0
# 
# 
# /home/KUTZTOWN/parson/JavaLang/atomimages:
# total 61920
# -rw-r--r-- 1 parson csit_faculty  44884 Mar  3  2012 atom0e.0.png
# -rw-r--r-- 1 parson csit_faculty  40600 Dec  2  2012 atom0e.1.png
#     __ls_re__ = re.compile(r'^(\S+)\s+(\d+)\s+(\S+)\s+(\S+)\s+(\d+)\s+([A-Z][a-z]+)\s+(\d+)\s+(\d+(:\d+)?)\s+(\S.+)$')
# ETC.
# 
# Things to note about incoming data from "ls -lR PATH" to be cleaned
# & formatted:
# 1. The first line in a block of directory entries is the path to the
#    directory, followed by a colon. An empty (white space) line precedes
#    subsequent directory record sets.
# 2. The opening string like "-rw-r--r--" is a set of 10 attrvalues:
#     File type, where "-" means a regular file, and other letters
#     indicate other file types.
# 
#     rwx read-write-execute permissions for the file owner. A "-" means
#     no permission for that field.
# 
#     rwx read-write-execute permissions for the file owner's group.
# 
#     rwx read-write-execute permissions for other (anyone on the system).
# 
#     Ignore any non-whitespace chars after the permissions in this string.
# 3. After white space(s) is the link count for this file, which is >= 1.
#    A single file in Unix may be linked from multiple directory entries.
# 4. The next string is the user/owner of the file, may be number, text, mixed.
# 5. The next string is the user's group of the file, may be num, text, mixed.
# 6. Next comes a modification date stamp. It starts with a month, may include
#    spaces, and ends with a time or year. If no year, then the year is the
#    current year.
# 7. The last field is the file's name, which may also include spaces.
# ATTRIBUTES FOR THE OUTPUT ARFF FILE:
attrNameToProperties = {}   # name -> (position, type descriptor string)
attrPosToName = {}          # position starting at 0 -> name
# 1. ftype   string          type of the file from the 1st character
attrNameToProperties["ftype"] = (0, "string")
attrPosToName[0] = "ftype"
# 2. ur      num (0 or 1)    0 for no user read, 1 for user read
attrNameToProperties["ur"] = (1, "numeric")
attrPosToName[1] = "ur"
# 3. uw      num (0 or 1)    0 for no user write, 1 for user write
attrNameToProperties["uw"] = (2, "numeric")
attrPosToName[2] = "uw"
# 4. ux      num (0 or 1)    0 for no user exe, 1 for user exe
attrNameToProperties["ux"] = (3, "numeric")
attrPosToName[3] = "ux"
# 5. gr      num (0 or 1)    0 for no grp read, 1 for grp read
attrNameToProperties["gr"] = (4, "numeric")
attrPosToName[4] = "gr"
# 6. gw      num (0 or 1)    0 for no grp write, 1 for grp write
attrNameToProperties["gw"] = (5, "numeric")
attrPosToName[5] = "gw"
# 7. gx      num (0 or 1)    0 for no grp exe, 1 for grp exe
attrNameToProperties["gx"] = (6, "numeric")
attrPosToName[6] = "gx"
# 8. or      num (0 or 1)    0 for no other read, 1 for other read
attrNameToProperties["or"] = (7, "numeric")
attrPosToName[7] = "or"
# 9. ow      num (0 or 1)    0 for no other write, 1 for other write
attrNameToProperties["ow"] = (8, "numeric")
attrPosToName[8] = "ow"
# 10. ox     num (0 or 1)    0 for no other exe, 1 for other exe
attrNameToProperties["ox"] = (9, "numeric")
attrPosToName[9] = "ox"
# 11. links  num             number of hard links to this file
attrNameToProperties["links"] = (10, "numeric")
attrPosToName[10] = "links"
# 12. user   string          alhpa, or numeric, or alphanumeric string
attrNameToProperties["user"] = (11, "string")
attrPosToName[11] = "user"
# 13. group  string          alhpa, or numeric, or alphanumeric string
attrNameToProperties["group"] = (12, "string")
attrPosToName[12] = "group"
# 14. fsize  num             size of file in bytes
attrNameToProperties["fsize"] = (13, "numeric")
attrPosToName[13] = "fsize"
# 15. mtime  date            modification time stamp on file
attrNameToProperties["date"] = (14, "date")
attrPosToName[14] = "date"  # date gets special treatment on output, not a str
# 16. fname  string          name of the file
attrNameToProperties["fname"] = (15, "string")
attrPosToName[15] = "fname"
# 17. ext    string          extension starting at trailing "." or empty string
attrNameToProperties["ext"] = (16, "string")
attrPosToName[16] = "ext"
# 18. dpath  string          path of the directory holding the file.
attrNameToProperties["dpath"] = (17, "string")
attrPosToName[17] = "dpath"
# 19. fpath  string          full path, which is dpath + "/" + fname
attrNameToProperties["fpath"] = (18, "string")
attrPosToName[18] = "fpath"
# 20. chlds  num             number of entries for a dir/, 0 for other types.
attrNameToProperties["chlds"] = (19, "numeric")
attrPosToName[19] = "chlds"
# Our data dictionary (schema) ends here.

if __name__ == "__main__":  # This "if" test is true if called from cmd line.
    usage = "USAGE: python lsTOarff.py INFILE OUTARFFFILE.arff"
    if len(sys.argv) != 3:
        # lsTOarff.py is included in the list of command line arguments.
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
    # TWO TESTS OF A re (regular expression) USING INTERACTIVE PYTHON:
    # >>> __ls_re__ = re.compile(r'^(\S+)\s+(\d+)\s+(\S+)\s+(\S+)\s+(\d+)\s+([A-Z][a-z]+)\s+(\d+)\s+(\d+(:\d+)?)\s+(\S.+)$')
    # >>> s = "-rw-r--r-- 1 parson csit_faculty  12322607 Mar 11  2013 atomgame.11mar2013.zip"
    # >>> s
    # '-rw-r--r-- 1 parson csit_faculty  12322607 Mar 11  2013 atomgame.11mar2013.zip'
    # >>> m = __ls_re__.match(s)
    # >>> m
    # <_sre.SRE_Match object at 0x7fae13702870>
    # >>> m.group(1)
    # '-rw-r--r--'
    # >>> m.group(2)
    # '1'
    # >>> m.group(3)
    # 'parson'
    # >>> m.group(4)
    # 'csit_faculty'
    # >>> m.group(5)
    # '12322607'
    # >>> m.group(6)
    # 'Mar'
    # >>> m.group(7)
    # '11'
    # >>> m.group(8)
    # '2013'
    # >>> m.group(9)
    # >>> m.group(10)
    # 'atomgame.11mar2013.zip'
    # >>> s = "drwxr-xr-x 4 parson csit_faculty      4096 Mar  1 10:22 FillWord5"
    # >>> m = __ls_re__.match(s)
    # >>> m
    # <_sre.SRE_Match object at 0x7fae13600840>
    # >>> m.group(1)
    # 'drwxr-xr-x'
    # >>> m.group(2)
    # '4'
    # >>> m.group(3)
    # 'parson'
    # >>> m.group(4)
    # 'csit_faculty'
    # >>> m.group(5)
    # '4096'
    # >>> m.group(6)
    # 'Mar'
    # >>> m.group(7)
    # '1'
    # >>> m.group(8)
    # '10:22'
    # >>> m.group(9)
    # ':22'
    # >>> m.group(10)
    # 'FillWord5'
    __date_re__ = re.compile(r'^DATE OF DATA DUMP: (\d+)-(\d+)-(\d+)\s*$')
    __ls_re__ = re.compile(r'^(\S+)\s+(\d+)\s+(\S+)\s+(\S+)\s+(\d+)\s+([A-Z][a-z]+)\s+(\d+)\s+(\d+(:\d+)?)\s+(\S.+)$')
    __path_re__ = re.compile(r'^(/.*):$')   # detect a directory path line
    __total_re__ = re.compile(r'^total\s+(\d+)$') # detect a total line
    __blank_re__ = re.compile(r'^\s*$')     # detect a blank line
    ifname = sys.argv[1]    # input file name
    ifile = open(ifname, "r")  # open input for for reading,
    ofile = open(ofname, "w")       # output file for writing
    curdir = "unknown"              # current directory in data
    curdirsize = 0
    # Replace datadate and datayear with DATE OF DATA DUMP in input file.
    # STUDENT assignment requires similar logic for these 2 variables.
    datadate = str(datetime.date.today())
    datayear = datadate[0:4]   # current year
    # Maintain the database in a Python list so we can back-patch the
    # chlds (contained children) attribute for directories after
    # counting them. Also map dir/ names to counts.
    # DATA STRUCTURES USED BY THE CODE BELOW:
    database = []   # Forms as a list of lists, one nested list per element.
    chlds = {}          # maps directory name -> count of contained entries.
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
        m = __path_re__.match(line) # Does the line look like a directory path?
        if m:
            curdir = m.group(1)
            curdirsize = 0
            chlds[curdir] = 0   # We will count entries later.
        else:
            m = __total_re__.match(line)    # A total (blocks) line follows.
            if m:
                curdirsize = int(m.group(1)) # Convert numeric string to an int.
            else:
                m = __ls_re__.match(line) # Is it a regular "ls -lR" entry?
                if m:
                    chlds[curdir] = chlds[curdir] + 1   # another dir entry
                    perms = m.group(1)  # Copy out the permissions field.
                    ftype = perms[0:1]  # First char gives file type.
                    if ftype == "-":
                        ftype = "r" # for regular file
                    # DATA STRUCTURE attrvalues forms as a list of
                    # attribute values to be appended to list database.
                    attrvalues = [ftype]    # Start a list attribute values.
                    perms = perms[1:]   # Discard first character.
                    # Loop through user-group-other
                    for who in ['u', 'g', 'o']:
                        # Loop through read-write-execute
                        for what in ['r', 'w', 'x']:
                            # Is first character the current 'r' 'w' or 'x'?
                            if perms[0] == what:    # If it is turned on?
                                attrvalues.append(1)
                            else:
                                attrvalues.append(0)
                            perms = perms[1:]   # Advance to next character.
                    attrvalues.append(int(m.group(2)))  # links as int
                    attrvalues.append(m.group(3))       # user/owner
                    attrvalues.append(m.group(4))       # group
                    attrvalues.append(int(m.group(5)))  # bytes in file as int
                    datestring = ""
                    if m.group(9):  # This is exact time-of-day, use this year
                        datestring = datayear
                    else:
                        datestring = m.group(8) # year of last modification.
                    # datestring is now yyyy of yyyy-MM-dd
                    monthname = m.group(6)
                    if monthmap.has_key(monthname):
                        datestring = datestring + "-" + monthmap[monthname]
                        # Append -01 to -12 to year name.
                        # datestring is now yyyy-MM of yyyy-MM-dd
                    else:
                        sys.stderr.write("ERROR, Invalid month in line "
                            + str(linenum) + " IN FILE " + ifname + ": "
                            + monthname + "\n")
                        sys.exit(1)
                    day = m.group(7)
                    if len(day) == 1:
                        day = "0" + day     # Make a 2-digit string.
                    datestring = datestring + "-" + day
                    # datestring is now yyyy-MM-dd of yyyy-MM-dd
                    attrvalues.append(datestring)
                    filename = m.group(10)
                    attrvalues.append(filename)
                    startofExtension = filename.rfind(".") # -1 on no "."
                    # If there is a trailing ., it starts the extension.
                    if (startofExtension >= 0):
                        extension = filename[startofExtension:]
                    else:
                        extension = ""
                    attrvalues.append(extension)
                    attrvalues.append(curdir)       # directory
                    attrvalues.append(curdir+"/"+filename) # full path
                    attrvalues.append(0)            # initialize chlds attr.
                    # We update chlds count until after we have seen all.
                    database.append(attrvalues)
                    # list database holds our ARFF database of entries.
                elif __date_re__.match(line):
                    m = __date_re__.match(line)
                    datayear = m.group(1)
                    # Note continuation char \ at end of next line.
                    # You need that for a multi-line statements that is not
                    # a (parenthesized expression).
                    datadate = datayear + "-" + m.group(2)  \
                        + "-" + m.group(3)
                elif not __blank_re__.match(line):
                    sys.stderr.write("INVALID LINE " + str(linenum)
                        + " IN FILE " + ifname + ": "
                        + line + "\n")
                    sys.exit(1)
        line = ifile.readline()
    # Now back-patch the dir/ chlds counts into the attrvalues.
    ftypeindex = attrNameToProperties["ftype"][0]   # [0] gets the index.
    chldsindex = attrNameToProperties["chlds"][0]
    dpathindex = attrNameToProperties["dpath"][0]
    fnameindex = attrNameToProperties["fname"][0]
    for row in database:
        if row[ftypeindex] == 'd':
            fullpath = row[dpathindex] + "/" + row[fnameindex]
            if not chlds.has_key(fullpath):
                sys.stderr.write("WARNING, missing chlds count for "
                    + fullpath + "\n")
                # sys.exit(1)
                # Note -- I am truncating the big data file by hand so
                # as not to overflow student accounts with big files.
                # That may cause the loss of some chlds counts.
                row[chldsindex] = 0
            else:
                row[chldsindex] = chlds[fullpath]   # copy the count
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

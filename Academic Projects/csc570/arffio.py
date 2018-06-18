# arffio.py, Dale E. Parson, January 2018, adapted from:
# bayescalc.py, Dale E. Parson, Summer 2013
# This module is for reading & writing ARFF
# files (attribute Relation File Format) used by Weka.
# main is a test driver

# small modifications made by Christian Carreras, March 2018
'''
readARFF and writeARFF are the main library functions of
use in this module. The non-private functions (__functions__() are private)
are useful as well. The __main__ code is a test driver.
'''

import sys
import re
import copy
import math
import os.path
import datetime

# __attr_re__ = re.compile(r'^\s*@attribute\s+(\S+)\s+(\S+)')
# __date_re__ parenthesizes name and date-format
__date_re__ = re.compile(r'^\s*@attribute\s+(\S+)\s+date\s+(\S+.*)$')
# __attr_re__ parenthesizes name and type
__attr_re__ = re.compile(r'^\s*@attribute\s+(\S+)\s+(\S+.*)$')
# __data_re__ is the @data card
__data_re__ = re.compile(r'^\s*@data.*$')

def __getAttrIndices__(af):
    '''
    Returns a map from attribute name to (offset, type) pair,
    where offset is attribute position, starting at 0, and type is
    described in the readARFF function documentation.
    Parameter af is the already-open ARFF file handle.
    Return value is the in-core map "result[aname] = (attrindex, atype)",
    where aname is the attribute name, attrindex is its index starting at 0,
    and atype is per the readARFF comments.
    '''
    result = {}
    attrCount = 0
    line = af.readline()
    while line:
        sline = line.strip()
        dm = __date_re__.match(sline)
        am = __attr_re__.match(sline)
        if dm:
            aname = dm.group(1)
            wformat = dm.group(2).strip()
            # wformat is Weka format, see
            # https://www.cs.waikato.ac.nz/ml/weka/arff.html
            # Appears to be based on Java format in java.text.SimpleDateFormat
            # https://docs.oracle.com/javase/8/docs/api/index.html
            # Internal we must use Python's datetime strptime() format:
            # https://docs.python.org/2/library/time.html#time.strptime
            # https://docs.python.org/2/library/datetime.html#strftime-strptime-behavior
            # This section converts Weka's format string wformat to
            # Python's pformat, and stores the type as a
            # ('date', wformat, pformat) 3-tuple.
            pformat = ''
            wremains = wformat
            while wremains:
                if wremains.startswith('yyyy') or wremains.startswith('YYYY'):
                    pformat = pformat + "%Y"
                    wremains = wremains[4:]
                elif wremains.startswith('yy') or wremains.startswith('YY'):
                    pformat = pformat + "%y"
                    wremains = wremains[2:]
                elif wremains.startswith('MM'):
                    pformat = pformat + "%m"
                    wremains = wremains[2:]
                elif wremains.startswith('M'):
                    pformat = pformat + "%m"
                    wremains = wremains[1:]
                elif wremains.startswith('dd'):
                    pformat = pformat + "%d"
                    wremains = wremains[2:]
                elif wremains.startswith('HH'):
                    pformat = pformat + "%H"
                    wremains = wremains[2:]
                elif wremains.startswith('mm'):
                    pformat = pformat + "%M"
                    wremains = wremains[2:]
                elif wremains.startswith('ss'):
                    pformat = pformat + "%S"
                    wremains = wremains[2:]
                elif (wremains.startswith('z') or wremains.startswith('Z')
                        or wremains.startswith('X')):
                    pformat = pformat + "%Z"
                    wremains = wremains[1:]
                else:
                    pformat = pformat + wremains[0]
                    wremains = wremains[1:]
            result[aname] = (attrCount, ('date', wformat, pformat))
            attrCount += 1
            # print("DEBUG mapped", aname, "TO", result[aname])
        elif am:
            aname = am.group(1)
            atype = am.group(2).strip()
            if atype.startswith('{') and atype.endswith('}'):
                nlist = atype[1:-1].strip().split(',')
                for i in range(0,len(nlist)):
                    nlist[i] = nlist[i].strip();
                realtype = ('nominal', atype, nlist)
            else:
                realtype = atype
            result[aname] = (attrCount, realtype)
            attrCount += 1
            # print("DEBUG mapped", aname, "TO", result[aname])
        elif __data_re__.match(sline):
            break
        line = af.readline()
    return result

def __getDataset__(af, amap):
    # Start helper function __mergeInstanceStrings__.
    def __mergeInstanceStrings__(instlist):
        # We have split along ','; fix cases here ',' is in a quoted string.
        # WHEN A STRING CONTAINS A "," MERGE WITH ITS PARTNER
        result = []
        ix = 0
        while ix < len(instlist):
            field = instlist[ix]
            if (field.startswith("'") or field.startswith('"')):
                terminator = field[0]
                fld = field
                if fld.endswith(terminator):
                    result.append(fld)
                    ix += 1
                else:
                    ix += 1
                    while ix < len(instlist):
                        f = instlist[ix]
                        # Re-insert the commas as part of the quoted string.
                        if (f.endswith(terminator)):
                            fld = fld + ',' + f
                            ix += 1
                            break
                        else:
                            fld = fld + ',' + f
                            ix += 1
                    result.append(fld)
            else:
                result.append(field)
                ix += 1
        return result
    # End helper function __mergeInstanceStrings__.
    result = []
    line = af.readline()
    while line:
        sline = line.strip()
        if sline[0:1] == '%':       # Comment line
            line = af.readline()
            continue
        instance = sline.split(',')
        # WHEN A STRING CONTAINS A "," MERGE WITH ITS PARTNER
        instance = __mergeInstanceStrings__(instance)
        for a in amap.keys():
            pos, t = amap[a]
            # print("DEBUG dataset", a, pos, t, instance[pos], instance)
            if pos >= len(instance):
                sys.stderr.write("ERROR, attribute " + str(a)
                    + "maps to position, type " + str(pos) + "," + str(t)
                    + ", instance has length " + str(len(instance))
                    + ":\n\t" + str(instance) + "\n")
                sys.stderr.flush()
            if instance[pos] == '?':
                instance[pos] = None
            elif t == 'numeric':
#               sys.stderr.write("DEBUG instance[pos]: "
#                   + str(instance[pos]) + '\n')
                vf = float(instance[pos])
                vi = int(vf)
                v = vi if (vi == vf and not '.' in instance[pos]) else vf
                instance[pos] = v
            elif t == 'string' and instance[pos].startswith("'"):
                instance[pos] = instance[pos][1:-1]
            elif isinstance(t, tuple) and len(t) == 3 and t[0] == 'date':
                # No need to strip anything.
                instance[pos] = (instance[pos],
                    datetime.datetime.strptime(instance[pos], t[2]))
            elif isinstance(t, tuple) and len(t) == 3 and t[0] == 'nominal':
                #instance[pos] = (instance[pos], instance[pos])
                instance[pos] = (instance[pos])
        result.append(instance)
        # print("DEBUG instance", instance)
        line = af.readline()
    return result

def readARFF(fname):
    '''
    Reads ARFF file named fname and returns (attrmap, dataset), where
    attrmap is the map from attrname -> (offset, type) returns by
    __getAttrIndices__, and dataset is a 2D list indexed on [row][offset]
    that holds in actual data instances.
    This offset is attribute position, starting at 0, and type is
    one of a date-3-tuple, 'numeric', 'string', a nominal set in {} delimiters,
    or a ARFF datetime value. A nominal type field is a 3-tuple of
    ('nominal', {NOMINAL_LIST_IN_STRING_FORM}, PYTHON_LIST_OF_NOMINAL_SYMBOLS),
    and a datetime (Weka date) is a 3-tuple consisting of
    ('date', Weka-format-string, Python-datetime-strptime-format-string).
    A nominal attribute-value in the dataset is a 2-tuple of
    (STRING_VALUE, NOMINAL_SYMBOL), and a date attribute-value is a 2-tuple
    (STRING_VALUE, Python datetime.datetime object).
    '''
    af = open(fname, 'r')
    amap = __getAttrIndices__(af)
    dataset = __getDataset__(af, amap)
    af.close()
    return((amap, dataset))

def writeARFF(fname, attrmap, dataset, isDebugMode=False):
    '''
    Writes ARFF file named fname with data in attrmap and dataset, where
    attrmap is the map from attrname -> (offset, type) returns by
    __getAttrIndices__, and dataset is a 2D list indexed on [row][offset]
    that holds in actual data instances. Set isDebugMode to True
    (default is False) for debugging output to sys.stderr.
    '''
    def __quoteAttr__(datum):
        # Fix strings attributes that need to be wrapped in quotes.
        # print("DEBUG datum 1 ",datum)
        if (" " in datum) or ("," in datum) or ("'" in datum) or ('"' in datum):
            # print("DEBUG datum 2 ",datum)
            if ((datum.startswith("'") and datum.endswith("'"))
                    or (datum.startswith('"') and datum.endswith('"'))):
                pass # It already is delimited.
            elif "'" in datum:
                datum = '"' + datum + '"'
            else:
                datum = "'" + datum + "'"
        return datum
    fout = open(fname, 'w')
    relationstring = sys.argv[0]
    for arg in sys.argv[1:]:
        relationstring = relationstring + " " + arg
    # relationstring = relationstring + " @ " + str(datetime.datetime.now())
    if "'" in relationstring:
        relationstring = '"' + relationstring + '"'
    else:
        relationstring = "'" + relationstring + "'"
    # fout.write('@relation tmprelation\n')
    fout.write('@relation ' + relationstring + '\n')
    fout.write('% ARFF file generated @ ' + str(datetime.datetime.now()) + '\n')
    newmap = remapAttributes(attrmap)
    newkeys = newmap.keys()
    newkeys.sort()
    for k in newkeys:
        fout.write('@attribute ' + newmap[k][0] + ' '
            + ('numeric' if (newmap[k][1] == 'float' or newmap[k][1] == 'int')
                else ('date ' + newmap[k][1][1])
                    if (isinstance(newmap[k][1],tuple)
                        and newmap[k][1][0] == 'date')
                else (newmap[k][1][1])
                    if (isinstance(newmap[k][1],tuple)
                        and newmap[k][1][0] == 'nominal')
                else newmap[k][1]) + '\n')
    fout.write('@data\n')
    for rix in range(0, len(dataset)):  # Iterate over rows in relation.
        row = dataset[rix]
        datum = row[0]
        if (isinstance(datum,tuple) and len(datum) == 2):
            # nominal or date, use the string form
            datum = datum[0]
        datum = __quoteAttr__(str(datum) if (not datum is None) else '?')
        fout.write(datum)
        for colix in range(1, len(row)):
            datum = row[colix]
            if (isinstance(datum,tuple) and len(datum) == 2):
                # nominal or date, use the string form
                datum = datum[0]
            datum = __quoteAttr__(str(datum) if (not datum is None) else '?')
            fout.write("," + datum)
            if isDebugMode:
                # Test whether reading a test arff file's datetime
                # field into a Python datetime works correctly.
                if (isinstance(newmap[colix][1],tuple)
                        and len(newmap[colix][1]) == 3
                        and newmap[colix][1][0] == 'date'):
                    dt = row[colix][1]
                    sys.stderr.write("DEBUG PYTHON DATETIME FIELD "
                        + newmap[colix][0] + ": " + str(dt) + '\n')
        fout.write('\n')
    fout.close()

def remapAttributes(attrmap):
    '''
    attrmap is a map from "attrname -> (offset, type)", and
    remapAttributes returns a map "offset -> (attrname, type)"
    '''
    newmap = {}
    for attrname in attrmap.keys():
        newmap[attrmap[attrname][0]] = (attrname, attrmap[attrname][1])
    return newmap

def mean(valueList):
    '''
    Return the mean of valueList as a float.
    '''
    sum = 0
    try:
        for v in valueList:
            sum = sum + v
        floater = sum / float(len(valueList))
        return floater
    except:
        sys.stderr.write('TYPE ERROR, call to mean for list: '
            + str(valueList) + '\n')
        return None

def median(valueList):
    '''
    Return the median of valueList, where median is the center value
    after sorting a copy of valueList. If there are an even number of elements,
    median returns the mean of the two central elements. Otherwise, any
    element type amenable to a sort may be in the valueList.
    '''
    try:
        vl = copy.copy(valueList)
        vl.sort()
        if ((len(vl) & 1) == 1):        # odd number of elements
            return vl[int(len(vl) / 2)]
        upper = int(len(vl) / 2)
        if vl[upper-1] == vl[upper]:
            return vl[upper]
        sum = vl[upper-1] + vl[upper]
        floater = sum / 2.0
        return floater
    except:
        sys.stderr.write('TYPE ERROR, call to median for list: '
            + str(valueList) + '\n')
        return None

def stddev(valueList, average=None, issample=False):
    '''
    Return the population standard deviation of valueList.
    If the caller supplies the average parameter, stddev uses that as the
    mean in computing the standard deviation. Otherwise, stddev invokes
    mean() to compute the mean, but returns only the standard deviation.
    If parameter issample is true, returns the sample standard deviation.
    '''
    try:
        if average == None:
            avg = mean(valueList)
        else:
            avg = average
        variance = 0.0
        for v in valueList:
            diff = v - avg
            variance = variance + (diff * diff)
        if issample:
            divisor = len(valueList)-1
        else:
            divisor = len(valueList)
        result = math.sqrt(variance / float(divisor))
        return result
    except:
        sys.stderr.write('TYPE ERROR, call to stddev for list: '
            + str(valueList) + '\n')
        return None

def minmax(valueList):
    '''
    Return the ordered pair (minimum, maximum) of valueList as an ordered pair.
    '''
    try:
        min = valueList[0]
        max = valueList[0]
        for v in valueList[1:]:
            if min is None or ((not v is None) and v < min):
                min = v
            if max is None or ((not v is None) and v > max):
                max = v
        return((min, max))
    except:
        sys.stderr.write('TYPE ERROR, call to minmax for list: '
            + str(valueList) + '\n')
        return ((None, None))

if __name__ == '__main__':
    if len(sys.argv) != 3:
        sys.stderr.write("USAGE: python arffio.py INARFFFILE OUTARFFFILE\n")
        sys.exit(1)
    infilename = sys.argv[1]
    outfilename = sys.argv[2]
    if os.path.exists(outfilename):
        sys.stderr.write("ERROR, file " + outfilename + " currently exists.\n")
        sys.exit(2)
    attrmap, dataset = readARFF(infilename)
    writeARFF(outfilename, attrmap, dataset, isDebugMode=True)

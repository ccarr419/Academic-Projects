'''
# Author:       Christian Carreras
# File:         arffToCsv.py
# Date:         03/16/2018
# Purpose:      Conversion of .arff files to .csv files using a module by
#               Dr. Parson of Kutztown University and the Python csv module.
'''
from __future__ import absolute_import
from __future__ import print_function

import csv
import sys
import time
import arffio
import argparse
from pathlib import Path

"""Get the default name for the .csv file to create"""
"""Default name only applies when no csv name argument is given"""
def _defaultName():
    args = parser.parse_args(sys.argv[1:])
    if args.csv == '':
        return args.arff.replace('.arff', '.csv')
    else:
        return args.csv

parser = argparse.ArgumentParser()
parser.add_argument('--arff', default='', type=str, 
    help="The location and name of the arff file to transform.")
parser.add_argument('--csv', default='', type=str, 
    help="The location and name of the new csv file.")
parser.add_argument('--header', default=False, type=bool, 
    help="1 to include a header, 0 to not include a header")

"""Checks the input file for correct format (.arff) and that it exists"""    
def _checkARFF(args):
    arffFile = args.arff
    assert arffFile.find('.arff') != -1, ("Only .arff files can be transformed.")
    file = Path(arffFile)
    assert (file.is_file()), ("File '%s' does not exist." % arffFile)
    print("Reading file " + arffFile)

"""Checks the output file and sees if it exists already"""
"""If the file exists the user will be prompted to overwrite the file"""    
def _checkCSV(args):
    csvFile = _defaultName()
    assert csvFile.find('.csv') != -1, ("Only .csv files can be created.")
    file = Path(csvFile)
    if file.is_file():
        try:
            command = input("\nYou are about to overwrite another file! Continue? \
            \nPRESS ENTER TO CONTINUE OR CTRL-C (^C) TO QUIT\n")
            print("Overwritting file " + csvFile)
        except:
            print("\nQuitting.")
            sys.exit(0)
    else:
        print("Writing to file " + csvFile)

def main():
    start = time.time() # Time the program if conversion times need to be noted
    args = parser.parse_args(sys.argv[1:])
    _checkARFF(args) # Make sure the given .arff file can be read
    amap, dataset = arffio.readARFF(args.arff)
    _checkCSV(args) # Make sure user is prompted to overwrite if necessary
    with open(_defaultName(), 'w') as csvfile:
        # Get column names from .arff file
        fieldnames=[]
        for key in amap:
            fieldnames.append(key)
        
        # Create a writer object to write to the csv file using fieldnames
        # Use quotes minimalistically->only use quotes when necessary
        writer = csv.DictWriter(csvfile, fieldnames=fieldnames, 
            quoting=csv.QUOTE_MINIMAL)
            
        if args.header:
            writer.writeheader()
        
        # Create a dictionary for each row in the dataset then write it to file
        for i in range(len(dataset)):
            row_dict = {}
            for j in range(len(fieldnames)):
                row_dict[fieldnames[j]] = dataset[i][j]       
            writer.writerow(row_dict)
    end = time.time() # Display that the program finished with this time
    print("Done at " + "{:.2f}".format(end-start) + " seconds.")
            
if __name__ == '__main__':
    main()
    
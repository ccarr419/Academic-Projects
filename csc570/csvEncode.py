'''
# Author:       Christian Carreras
# File Name:    csvEncode.py
# Date:         03/20/2018
# Purpose:      To take a .csv file and turn all nominal (categorical) column
#               data into numerical (continous) column data through the use of
#               label encoding in the sklearn preprocessing module.
#               One file argument is to be entered and a new file will be
#               created where all nominal columns are changed to numeric
#               columns. Original files are unchanged by default.
'''
from __future__ import absolute_import
from __future__ import print_function

import sys
import time
import argparse
import numpy as np
import pandas as pd
from pathlib import Path
from sklearn import preprocessing

"""Get the default name for the .csv file to create"""
"""Default name only applies when no csv name argument is given"""
def _defaultName():
    args = parser.parse_args(sys.argv[1:])
    if args.dest_dir == '':
        return args.file_dir.replace('.csv', '_e.csv')
    else:
        return args.dest_dir

parser = argparse.ArgumentParser()
parser.add_argument('--file_dir', default='', type=str, 
    help="The location and name of the file to encode.")
parser.add_argument('--dest_dir', default='', type=str, 
    help="The location and name for the newly created encoded file.")
parser.add_argument('--header', default=0, type=int, 
    help="Row number in file_dir to use as column names, use -1 for no headers.")
 
"""Checks the input file for correct format (.csv) and that it exists"""  
def _checkArgs(args):
    argFile = args.file_dir
    assert argFile.find('.csv') != -1, ("Only .csv files can be encoded.")
    file = Path(argFile)
    assert (file.is_file()), ("File '%s' does not exist." % argFile)
    return argFile

"""Read the file with either no header or the position of the file header"""
def _input_fn(csv_file, args):
    if args.header < 0:
        return pd.read_csv(csv_file, header=None)
    else:
        return pd.read_csv(csv_file, header=args.header)

"""Checks to see if the output file is of correct format and existance"""
"""If the file exists the user will be prompted to overwrite the file"""        
def _output_fn(enc_data):
    dest_file = _defaultName()
    assert dest_file.find('.csv') != -1, ("Only .csv files can be created.")
    file = Path(dest_file)
    if file.is_file():
        try:
            command = input("\nYou are about to overwrite another file! Continue? \
            \nPRESS ENTER TO CONTINUE OR CTRL-C (^C) TO QUIT\n")
            print("Overwritting file " + dest_file)
            enc_data.to_csv(dest_file, header=False, index=False)
        except:
            print("\nQuitting.")
            sys.exit(0)
    else:
        enc_data.to_csv(dest_file, header=False, index=False)

"""Find the columns in the dataset that contain nominal (categroical) data"""
"""Return a 2d list containing the unique values for each nominal column"""
"""Return a list containing the column numbers of each nominal column"""       
def findNominalColumns(dataset):
    data = dataset.values
    uni_col = [] # List of nominal columns and their unique nominal values
    itr_col = [] # List of nominal columns numbers
    for i in range(len(data[0])):
        nom_col = []
        if type(data[0][i]) is str: # Only work with nominal(str) data
            nom_col = data[:,i] # Get all row data for this column
            nom_col = np.unique(nom_col) # Get rid of all duplicates
            uni_col.append(list(nom_col)) # Convert nparry to list
            itr_col.append(i)
    return uni_col, itr_col

"""Encode each nominal column with an integer identifier based on their data"""
"""Return a pandas.DataFrame so that it can easily be written to csv"""
def _encodeColumns(dataset, uni_col, itr_col):
    le = preprocessing.LabelEncoder()
    data = dataset.values # Get values so that data slices can be worked with
    for i in range(len(itr_col)):
        le.fit(uni_col[i]) # Fit the columns nominal values
        data[:,itr_col[i]] = le.transform(data[:,itr_col[i]]) # Column data->int
    return pd.DataFrame(data)
        
def main():
    start = time.time() # Time the program if conversion times need to be noted
    args = parser.parse_args(sys.argv[1:])
    print("Authenticating file...")
    csv_file = _checkArgs(args)
    print("Reading from file " + str(args.file_dir))
    dataset = _input_fn(csv_file, args)
    print("Searching for nominal columns...")
    uni_col, itr_col = findNominalColumns(dataset)
    print("Encoding Labels...")
    enc_data = _encodeColumns(dataset, uni_col, itr_col)
    print("Writing to file " + _defaultName())
    _output_fn(enc_data)
    end = time.time() # Display that the program finished with this time
    print("Done at " + "{:.2f}".format(end-start) + " seconds.")
    
if __name__ == '__main__':
    main()

'''
Author:         Christian Carreras
Project Name:   Optimal Overwatch™ Hero Selection (OOHS)
File Name:      oohs.py
File Date:      04/21/2017
Professor:      Dr. Rieksts
Semester:       SPRING 2017
Course:         CSC 548 Artificial Intelligence II
Institution:    Kutztown University of Pennsylvania
Purpose:        The purpose of this project is to create a machine-learning
                algorithm that is able to successfully predict the success
                rate of an enemy hero compared to the player's pick. The 
                algorithm will take the enemy's and player's skill into 
                account and compare them with training data. Skills the 
                algoritm will look at are eliminations/min, kill/death ratio, 
                accuracy, damage/min, damage blocked/min, healing/min, and 
                critical hits/min. By using a linear regression method, the 
                algorithm will predict the success rate of new data based on 
                training data and their success rates. Overwatch™ is an online,
                team-based, first-person shooter that heavily relies on picking
                the right hero to fill a role or counter an enemy hero. I chose
                this project as I enjoy playing this game and I was curious if
                I could create an algorithm that would choose the best hero for 
                me given the circumstances of the current match and players.
                
                This file assumes that you are using the Spyder IDE as a 
                python environment and that your working directory is the 
                spyder-py3 folder. If you are not using the Spyder IDE, you
                must change the code to match your working directory.
                Alternatively, you can create the spyder-py3 folder in the 
                "C:/Users/%USERNAME%/" directory if you are using Windows. 
                If you are using Linux or Mac, create a spyder-py3 folder in 
                your user directory or change the code to fit your needs.
                
                You have full permission to edit the code and upload it
                anywhere as long as it for academic or self-use only.
                Just be sure to credit me if you do upload/post it anywhere.
                Code is as is and has absolutely NO warranty.
                
Future Additions:
    - Real-life training data made from player v. player.
    - All heroes will be taken into account
    - Algorithm will take game-map into account
    - Algorithm will take game-mode into account
    - See if other stats not taken into account affect decision

Data and averages (besides success rates) were all collected from
https://masteroverwatch.com
I do not own this data and all data and is for academic/self-use use only.

All trademarks referenced herein are the properties of their respective owners.
© MasterOverwatch.com 2017. All rights reserved.
© 2017 Blizzard Entertainment, Inc. All rights reserved.
'''
import pandas # Used for organizing and accessing data
import pickle # Used for packaging and un-packaging data
import os.path as path # Used for accessing files at a certain location
from pandas.tools.plotting import scatter_matrix # Used for scatter-matix
import matplotlib.pyplot as plt # Used in showing graphs/visible data
from sklearn import model_selection # Used to split dataset into multiple sets
from sklearn.linear_model import LinearRegression # Main algorithm for ml
from sklearn import preprocessing # Used in label encoding
import numpy as np # Used in score calculation
from datetime import datetime # Used in random seed generation
import random # Used in random seed generation

# Path to the data file. If your working directory is different or you are not
# using the Spyder IDE change to: 
# dataPath = ("PATH") where PATH is the file's location
dataPath = path.expanduser("~/.spyder-py3/OOHSData.txt")

# The headers for each column in the dataset
columnNames = ['eHero', 'eElimPerMin', 'eKDRatio', 'eAccuracy', 'eDamPerMin',
               'eBlockPerMin', 'eHealPerMin', 'eCritPerMin', 'pHero',
               'pElimPerMin', 'pKDRatio', 'pAccuracy', 'pDamPerMin',
               'pBlockPerMin','pHealPerMin', 'pCritPerMin', 'SuccessRate']

# The list of heroes currently used in the algorithm and dataset
heroList = ["Ana", "Bastion", "Lucio", "McCree", "Mei", "Reaper", "Roadhog",
            "Soldier:76", "Torbjorn", "Zarya", "Zenyatta"]

# This function takes any data as a first parameter and pickles it into a .pkl
# file for later use. The name of the new file is given in the second param.            
def stoDB(db, fn):
    fn = open(fn+'.pkl','wb')
    pickle.dump(db,fn)
    fn.close()

# This function tries to find a .pkl file by the name given in the first param.
# If there is such a file, the file is unpickled and returned. If there is no
# such file, None is returned instead.                                                                                                              
def getDB(fn):
    # Check if the file exists in the user's directory
    # If your working directory is different or you are not
    # using the Spyder IDE change to:
    # path.isfile("PATH"+fn+".pkl") where PATH is the file's location
    if (path.isfile(path.expanduser("~/.spyder-py3/"+ fn + ".pkl"))):
        dbFile = open(fn+'.pkl','rb')
        db = pickle.load(dbFile) # Unpickle and load the dataset
        dbFile.close()
        return db
    else: # File does not exist
        return None
   
# This function loads the dataset to use for the machine-learning algorithm.
# If the dataset already has been pickled, retrieve it for use. Otherwise,
# generate a new dataset from the data file to use.     
def initialize():
    dataset = getDB("oohs")
    if (dataset is None): # .pkl does not exist, create one
        dataset = pandas.read_csv(dataPath, names=columnNames)
        stoDB(dataset, "oohs")
        print("Saved dataset to new pkl file.\n")
    return dataset              

# This function prints the whole dataset in its entirety instead of printing
# a subset of the data (aka the head and tail of the dataset)
def print_full():
    dataset = initialize()
    pandas.set_option('display.max_rows', len(dataset))
    print(dataset)
    pandas.reset_option('display.max_rows') #reset to normal

# Create a box plot depicting the dataset
def boxPlot():
    dataset = initialize()
    dataset.plot(kind='box', subplots=True, layout=(4,4), figsize=(12,12),
                 sharex=False, sharey=False)
    plt.show()

# Create a histogram bar graph depicting the dataset
def histogram():
    dataset = initialize()
    dataset.hist(layout=(4,4), figsize=(12,12), xrot=90, xlabelsize=8)
    plt.show()

# Create a scatter plot matrix depicting the dataset
def scatterMatrix():
    dataset = initialize()
    scatter_matrix(dataset, figsize=(24,24))
    plt.show()   

# This function turns all non-numerical data in a dataset into integers
# All references of a hero name in the dataset will be turned into a
# corresponding integer. e.g. Ana will turn to 0, Bastion to 1, etc.
def encodeLabels(array):
    le = preprocessing.LabelEncoder() # LabelEncoder will do all the work
    le.fit(heroList) # Tell le to change any hero name to its int value
    array[:,0] = le.transform(array[:,0]) # Transform enemy heroes to ints
    array[:,8] = le.transform(array[:,8]) # Transform player heroes to ints
    return le

# This function prints the results of a prediction. Print only, no calculation.
def printResults(playerHero, enemyHero, pred, y):
    print("Matchup: " + playerHero + " vs " + enemyHero +
              "; Prediction: ", end='')
    print(pred, end='')
    # Print the actual value of the value being predicted
    print("%; Actual value: ", end='')
    print(round(y,4)*100, end='')
    print("%")

# This function prints the mean squared error and variance score of a
# prediction compared to it's actual values. Calculation is done inside print.
def printStats(regr, X_validation, Y_validation):
    print("Mean squared error: %.2f" % np.mean((regr.predict(X_validation) -
                                                Y_validation) ** 2))
    print('Variance score: %.2f' % regr.score(X_validation, Y_validation))

# This function predicts the outcome (aka success rate) of the player hero
# against an enemy hero. The method used to elicit a prediction was a linear
# regression. First the algorithm will train with a portion of the dataset
# then it will try to predict the values of the rest of the dataset. It will
# then print the results so the user can easily understand what happened.
def makePredictions(X_train, Y_train, X_validation, Y_validation, le):
    regr = LinearRegression()
    regr.fit(X_train, Y_train) # Train with a portion of the dataset
    predictions = regr.predict(X_validation) # Then predict the remaining
    # Go through all the items in the testing dataset and print the results
    for k in range(0, X_validation.shape[0]):
        # Change back to hero names instead of printing ints in results
        enemyHero = le.inverse_transform(X_validation[k][0])
        playerHero = le.inverse_transform(X_validation[k][8])
        pred = round(predictions[k],4)*100 # Change from floating to percent
        printResults(playerHero, enemyHero, pred, Y_validation[k])

    print('')
    printStats(regr, X_validation, Y_validation) # Print algorithm score

# This function starts the process of creating needed variables, splitting
# the dataset into training and testing data, training, and then making
# predictions. All the functionality of this machine-learning algorithm 
# besides displaying dataset graphs is presented in this function.   
def start():
    # Create pseudo-random seed from current time to ensure no test is the same
    seed = random.seed(datetime.now()) 
    validation_size = 0.20 # Percent to split from the dataset to testing data
    dataset = initialize() # Get or create the dataset
    # Make an array from the dataset so it can be encoded and split
    array = dataset.values
    le = encodeLabels(array) # Change string data in the dataset to ints
    X = array[:,0:16] # Get all rows from columns 0-15
    Y = list(array[:,16]) # Get all rows from column 16
    # Split the dataset into training and testing data
    X_train, X_validation, Y_train, Y_validation = model_selection.train_test_split(
                                X, Y, test_size=validation_size, random_state=seed)
    # Make predictions based on the newly split data after training
    makePredictions(X_train, Y_train, X_validation, Y_validation, le)


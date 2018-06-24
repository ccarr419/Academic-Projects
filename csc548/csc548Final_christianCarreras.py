import math
import operator
from mnist import MNIST # https://pypi.python.org/pypi/python-mnist/
from random import shuffle

# Find the euclidean distance between the training and testing instances
def euclideanDistance(instance1, instance2, length):
    distance = 0
    for x in range(length):
        distance += pow((instance1[x] - instance2[x]), 2)
    return math.sqrt(distance)

# Find the closest neighbors to the test instance by finding the euclidean
# distance of each training instance compared to the current test instance.
# Then keep only k of the closest neighbors
def getNeighbors(trainingSet, testInstance, k):
    distances = []
    length = len(testInstance)-1
    for x in range(len(trainingSet[0])):
        dist = euclideanDistance(testInstance, trainingSet[0][x], length)
        distances.append((trainingSet[1][x], dist))
        # Print a dot every so often to show progress
        if x % 10000 == 0:
            print('. ', end='')
    print('')
    distances.sort(key=operator.itemgetter(1))
    neighbors = []
    for x in range(k):
        neighbors.append(distances[x][0])       
    return neighbors

# Find the neighbor that appears the most in the group and respond with that
def getResponse(neighbors):
    classVotes = {}
    for x in range(len(neighbors)):
        response = neighbors[x]
        if response in classVotes:
            classVotes[response] += 1
        else:
            classVotes[response] = 1
    sortedVotes = sorted(classVotes.items(), key=operator.itemgetter(1), reverse=True)
    return sortedVotes[0][0]

# Return the accuracy of the algorithm by the amount of predictions so far
def getAccuracy(testSet, predictions):
    correct = 0
    for x in range(len(predictions)):
        if testSet[x] == predictions[x]:
            correct += 1
    return (correct/float(len(predictions))) * 100.0

def main():
    # Prepare data
    # Dataset location: http://yann.lecun.com/exdb/mnist/
    mndata = MNIST('./samples/')
    trainingSet = mndata.load_training()
    testSet = mndata.load_testing()

    # Randomize test set
    testPictures = list(testSet[0])
    testLabels = list(testSet[1])
    combined = list(zip(testPictures, testLabels))
    shuffle(combined)
    testPictures[:], testLabels[:] = zip(*combined)
    
    # Generate predictions
    predictions=[]
    k = 3
    for x in range(len(testSet[0])):
        print(mndata.display(testPictures[x]))
        print('\nTest #' + repr(len(predictions)+1))
        print('Processing ', end='')
        neighbors = getNeighbors(trainingSet, testPictures[x], k)
        result = getResponse(neighbors)
        predictions.append(result)
        # Print results
        print('Prediction: ' + repr(result))
        print('Actual: ' + repr(testLabels[x]))
        accuracy = getAccuracy(testLabels, predictions)
        print('Accuracy: ' + repr(accuracy) + '%')
    print("Testing Complete")
    
main()
    
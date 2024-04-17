# Online Python compiler (interpreter) to run Python online.
# Write Python 3 code in this online editor and run it.
# print("Try programiz.pro")/

import random
import numpy as np

MAX_VALUE = 30

frames = np.zeros(MAX_VALUE)

lastIndexCounter = 0
numFramesAdded = 0
currIndex = 0
prevIndex = 0


def circularIncrement(cur, MAX_VAL):
    cur += 1
    if(cur >= MAX_VAL):
        cur = 0
    return cur
    
def circularDecrement(cur, MAX_VAL):
    cur -= 1
    if(cur < 0):
        cur = MAX_VAL - 1
    return cur
    
def computeAvg(frames, startIndex, MAX_VAL):
    A = -0.153505673
    weight = MAX_VAL
    sumWeights = 0
    index = startIndex
    avg = 0.0
    for i in range(len(frames)):
        weight = np.exp(A * i)
        sumWeights += weight
        avg += weight * frames[index]
        print(f"Multiplying: {frames[index]} at index {index} with weight {weight}")
        index = circularDecrement(index, MAX_VAL)
    avg /= sumWeights
    print("Next\n\n")
    return avg

# index = 0
for i in range(0, 10):
    # index = circularDecrement(index, MAX_VALUE)
    # print(index)
    f = random.randint(-10, 10)
    # print(f)
    frames[currIndex] = f
    prevIndex = currIndex
    currIndex = circularIncrement(currIndex, MAX_VALUE)
    print(frames)
    print(prevIndex)
    print(computeAvg(frames, prevIndex, MAX_VALUE))
    
    
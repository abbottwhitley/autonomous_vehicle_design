import numpy as np 
import time

n = 10000               # list & array length

aList = list(range(n))

# returns seconds as a float
start = time.time()
for i, item in enumerate(aList): 
    aList[i] = aList[i]*2
stop = time.time()

elapsed = stop - start 
print("list time:  " + str(elapsed*1000) + " msec")

aArray = np.arange(n)
start = time.time()
aArray = aArray * 2
stop = time.time()
elapsed = stop - start
print("array time: " + str(elapsed*1000) + " msec")




'''
aList = list(range(4))
for i, item in enumerate(aList):
    aList[i] = aList[i]*2
print(aList)


print("-- List versus array, scalar multiplication --")
print("aList    ", end='')
print(aList)
# multiplication of a list extends and repeats the list
print("aList*2  ", end='')
print(aList*2)


# create an array
aArray = np.arange(4)
print("aArray   ", end='')
print(aArray)
# each element in array is multiplied by the scalar value
print("aArray*2 ", end = '')
print(aArray*2)
'''


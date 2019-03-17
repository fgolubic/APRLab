#!/usr/local/bin/python3
import matplotlib.pyplot as plt
import numpy as np
"""
===SCRIPT FOR PLOTTING NUMERICAL INTEGRATION RESULTS IN EACH STEP===
    This scipt plots Runge Kutta and Trapezoidal results of numerical
    integration.
    Runge Kutta results are stored in result.txt.
    Trapezoidal results are stored in resultTrap.txt.
    Both files are located in working directory of C++ program.
    Script first reads step of integration and it's boundary.
    Then it reads values of point in each step and loads it in numpy array
    of size number of steps x dimension of vector.
    After all information has been loaded it plots a graph for each method.

"""
plots = list()

fp = open('./result.txt')

line = fp.readline()
splitted = line.rstrip().split(" ")
T=float(splitted[0])
TMax = float(splitted[1])
y = []
x = []
line = fp.readline()
while line.rstrip():
    splitted = line.rstrip().split()
    point = np.array([float(x) for x in splitted])
    y.append(point)
    line = fp.readline()

print(y)
x = np.arange(0, TMax + T, T)
plt.figure(1)
plt.plot(x,y,label = 'Runge Kutta graph')
plt.show()
fp.close()

fp = open('./resultTrap.txt')

line = fp.readline()
splitted = line.rstrip().split(" ")
T=float(splitted[0])
TMax = float(splitted[1])
y = []
x = []
line = fp.readline()
while line.rstrip():
    splitted = line.rstrip().split()
    point = np.array([float(x) for x in splitted])
    y.append(point)
    line = fp.readline()

print(y)
x = np.arange(0, TMax + T, T)
plt.figure(2)
plt.plot(x,y,label = 'Trapeziodal graph')
plt.show()
fp.close()


    

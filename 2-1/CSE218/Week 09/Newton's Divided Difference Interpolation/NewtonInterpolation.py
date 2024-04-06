import numpy as np
import math
import matplotlib.pyplot as plt
from sympy import *

def findProducts(index, x, value):
    pro = 1
    for i in range(index):
        pro = pro * (value - x[i])
    return pro


def calculateTable(x, y, n):
    for i in range(1, n):  # goes down
        for j in range(n - i):  # goes right
            y[j][i] = (y[j][i - 1] - y[j + 1][i - 1]) / (x[j] - x[j + i])


def findValue(value, x, y, n):
    sum = y[0][0]
    for i in range(1, n):
        sum = sum + findProducts(i, x, value) * y[0][i]
    return sum


def plotGraph(xx, yy, n, lower, upper):
    # creating numpy array from range x = -1.99 to 10 with increament 0.05
    x = np.arange(0, 40, 0.05)
    y = findValue(x, xx, yy, n)
    # y[y > 100] = np.nan  # erasing asymptote
    # y[y < -100] = np.nan  # erasing asymptote

    # Plotting the graphs
    plt.ylim([lower, upper])  # limiting y axis value
    # plt.plot([-3, 10], [0, 0], color='blue')  # x-axis
    # plt.plot([0, 0], [-15, 15], color='blue')  # y-axis
    plt.plot(x, y, color='green', linestyle='dashed', linewidth=3)  # main graph

    # Creating axis
    plt.grid(True, which='both')
    plt.axhline(y=0, color='blue')
    plt.axvline(x=0, color='blue')

    # Labeling axis
    plt.xlabel('x - axis')
    plt.ylabel('y - axis')

    plt.show()


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    np.set_printoptions(suppress=True)
    # mass = [[19,1203],[22,1245],[26,1378],[28,1315],[30,1475]]
    mass = [[0,0],[np.pi/4,1/(2**0.5)],[np.pi/2,1]]
    n = len(mass)
    x = [0] * n
    dimensions = (n, n)
    y = np.zeros(dimensions)
    for i in range(n):
        x[i] = mass[i][0]
        y[i][0] = mass[i][1]
    calculateTable(x, y, n)

    # Result = findValue(25, x, y, n)
    # print("The mass at 25 sec is", Result)
    # plotGraph(x,y,5,1000,2000)

    X = Symbol('x')

    print("Interpolation Table:")
    print(y)

    print("Interpolated Equation")
    f = findValue(X, x, y, n)
    print(f)

    print("Simplified equation:")
    f = simplify(f)
    print(f)


# See PyCharm help at https://www.jetbrains.com/help/pycharm/

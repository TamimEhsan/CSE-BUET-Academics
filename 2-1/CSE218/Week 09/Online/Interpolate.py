import numpy as np
import math
import matplotlib.pyplot as plt

## Newton's Divided difference

def findProducts(index,x,value):
    pro = 1
    for i in range(index):
        pro = pro*(value-x[i])
    return pro


def calculateTable(x,y,n):
    for i in range(1,n):
        for j in range(n-i):
            y[j][i] = (y[j][i-1] - y[j+1][i-1])/(x[j] - x[j+i])

def findValue(value,x,y,n):
    sum = y[0][0]
    for i in range(1,n):
        sum = sum+ findProducts(i,x,value)*y[0][i]
    return sum

def findTable(values):
    n = len(values)
    x = [0] * n
    dimensions = (n, n)
    y = np.zeros(dimensions)
    for i in range(n):
        x[i] = values[i][0]
        y[i][0] = values[i][1]
    calculateTable(x, y, n)
    return x,y,n

def plotGraph(xx,yy,n,lower,upper):
    # creating numpy array from range x = -1.99 to 10 with increament 0.05
    x = np.arange(0, 40, 0.05)
    y = findValue(x,xx,yy,n)
    # y[y > 100] = np.nan  # erasing asymptote
    # y[y < -100] = np.nan  # erasing asymptote

    py = [0]*n
    for i in range(n):
        py[i] = yy[i][0]
    plt.scatter(xx, py,color='red')
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
    mass = [[19,1203],[22,1245],[26,1378],[28,1315],[30,1475]]

    n = 4
    x = [0]*n
    dimensions = (n, n)
    y = np.zeros(dimensions)
    for i in range(1,n):
        x[i] = mass[i][0]
        y[i][0] = mass[i][1]
    calculateTable(x,y,n)
    Result3 = findValue(25,x,y,n)
    n = 5
    x = [0] * n
    dimensions = (n, n)
    y = np.zeros(dimensions)
    for i in range(n):
        x[i] = mass[i][0]
        y[i][0] = mass[i][1]
    calculateTable(x, y, n)
    Result4 = findValue(25, x, y, n)

    error = math.fabs(Result4-Result3)/Result4*100

    print("The mass at 25 sec is",Result4)
    print("Abosulte Relative Error", error,"%")
    plotGraph(x,y,5)





# See PyCharm help at https://www.jetbrains.com/help/pycharm/

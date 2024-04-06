import numpy as np
import math
import Interpolate

if __name__ == '__main__':
    mass = [[19,1203],[22,1245],[26,1378],[28,1315],[30,1475]]

    n = 4
    x = [0]*n
    dimensions = (n, n)
    y = np.zeros(dimensions)
    for i in range(1,n):
        x[i] = mass[i][0]
        y[i][0] = mass[i][1]
    Interpolate.calculateTable(x,y,n)
    Result3 = Interpolate.findValue(25,x,y,n)
    n = 5
    x = [0] * n
    dimensions = (n, n)
    y = np.zeros(dimensions)
    for i in range(n):
        x[i] = mass[i][0]
        y[i][0] = mass[i][1]
    Interpolate.calculateTable(x, y, n)
    Result4 = Interpolate.findValue(25, x, y, n)

    error = math.fabs(Result4-Result3)/Result4*100

    print("The mass at 25 sec is",Result4)
    print("Abosulte Relative Error", error,"%")
    Interpolate.plotGraph(x,y,5,1000,2000)





# See PyCharm help at https://www.jetbrains.com/help/pycharm/

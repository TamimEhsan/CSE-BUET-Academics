import numpy as np
import math
import Interpolate

# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    mass = [[19,3000],[22,3500],[26,4000],[28,4500],[30,5000]]

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

    print("The velocity at 25 sec is",Result4)
    print("Abosulte Relative Error", error,"%")
    Interpolate.plotGraph(x, y, 5,2500,5500)




# See PyCharm help at https://www.jetbrains.com/help/pycharm/

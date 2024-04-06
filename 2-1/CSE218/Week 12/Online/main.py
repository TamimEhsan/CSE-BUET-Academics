import numpy as np
import math
from matplotlib import pyplot as plt

def f(b,xx,yx,xex,e2x,yex):
    return yex-(yx-b*xex)*xex/xx - b*e2x

def Fx(x,a,b):
    return a*x+b*np.exp(x)

def find_Root_By_Bisection_Method(lower,upper,ERROR,MAX_ITERATION,xx,yx,xex,e2x,yex):
    iteration = 0
    prev_solution = 0
    for iteration in range(MAX_ITERATION):
        mid = (lower+upper)/2
        if mid == 0:
            mid = ERROR
        if iteration!=1:
            error = math.fabs((mid-prev_solution)/mid)*100
            if( error<ERROR ):
                return mid,error
        prev_solution = mid
        if f(lower,xx,yx,xex,e2x,yex)*f(mid,xx,yx,xex,e2x,yex)<0:
            upper = mid
        else:
            lower = mid
    return mid,False;

def plotGraph(X,Y,a,b):
    plt.xlabel('x')
    plt.ylabel('y')
    plt.scatter(X, Y, color='#1f77b4',marker='+',label="Points")
    plt.grid(True, which='both')

    x = np.arange(0, 2.01, .1)
    y = Fx(x,a, b)
    plt.plot(x, y, color='#ff8011',label="y=ax+be^x")

    plt.legend()
    plt.show()

def readFile():
    datas = []
    x = []
    y = []
    with open('data.txt') as f:
        datas = f.readlines()
    for data in datas:
        a,b = map(float,data.split())
        x.append(a)
        y.append(b)
    return len(x),x,y

if __name__ == '__main__':
    n,x,y = readFile()
    x = np.array(x)
    y = np.array(y)
    yx = sum(y*x)
    xx = sum(x*x)
    xex = sum(x*np.exp(x))
    e2x = sum(np.exp(2*x))
    yex = sum(y*np.exp(x))
    b,error = find_Root_By_Bisection_Method(-1,1,0.00001,20,xx,yx,xex,e2x,yex)

    a = (y[0]-b*np.e**x[0])/x[0]
    print('a =',a,'b =',b)
    plotGraph(x,y,a,b)

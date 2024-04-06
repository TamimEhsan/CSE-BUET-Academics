import numpy as np
from matplotlib import pyplot as plt

from readData import readFile
import LinearRegression
import ExpotentialRegressionModel
import PolynomialModelRegression

def plotLinear(X,Y):
    a0,a1 = LinearRegression.findLinearRegression(X,Y)
    x = np.arange(min(X), max(X), .1)
    y = LinearRegression.fx(a0,a1,x)
    plt.plot(x, y, color='#2279b5')

def plotExpotential(X,Y):
    a0, a1 = ExpotentialRegressionModel.findExpotentialRegression(X, Y)
    x = np.arange(min(X), max(X), .1)
    y = ExpotentialRegressionModel.fx(a0, a1, x)
    plt.plot(x, y, color='#ff8011')

def plotPolynomial(X,Y,degree,color,label):
    constants = PolynomialModelRegression.findPolynomialRegression(X, Y,degree)
    x = np.arange(min(X), max(X), .1)
    y = PolynomialModelRegression.fx(constants, x)
    plt.plot(x, y, color=color,label = label)

def plotGraph(x,y):
    plt.xlabel('x')
    plt.ylabel('y')
    plt.scatter(x, y, color='#1f77b4',s=1,marker='+')
    plt.grid(True, which='both')

    ## Plot Linear Model
    # plotLinear(x,y)

    ## Plot expotential
    # plotExpotential(x,y)

    ## Plot polynomial curves
    plotPolynomial(x, y, 1, '#2279b5', 'First-Order')
    plotPolynomial(x, y, 2, '#ff8011', 'Second-Order')
    plotPolynomial(x, y, 3, '#38a538', 'Third-Order')
    plt.legend()
    plt.show()

if __name__ == '__main__':
    n,x,y = readFile()
    x = np.array(x)
    y = np.array(y)
    plotGraph(x,y)
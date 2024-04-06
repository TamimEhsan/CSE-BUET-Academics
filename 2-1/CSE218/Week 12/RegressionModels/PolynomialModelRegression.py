import  numpy as np

from GaussianElimination import GaussianEliminationPP


def fx(constansts,x):
    n = len(constansts)
    y = 0
    for i in range(n):
        y+= constansts[i]* (x**i)
    return y

def getMatrices(x,y,N):
    n = len(x)
    X = np.zeros((N,N))
    Y = np.zeros((N,1))
    Xpotential = np.ones(n)
    sum_x = np.zeros(2*N-1)
    for i in range(2*N-1):
        sum_x[i] = sum(Xpotential)
        if i<N:
            Y[i] = sum(Xpotential*y)
        Xpotential = Xpotential*x

    for i in range(N):
        for j in range(N):
            X[i][j] = sum_x[i+j]

    return X,Y


def findPolynomialRegression(x,y,degree):
    X, Y = getMatrices(x, y, degree+1)
    status, coefficients = GaussianEliminationPP(X, Y)
    return coefficients

if __name__ == '__main__':
    x = [80, 40, -40, -120, -200, -280, -340]
    y = [6.47e-6, 6.24e-6, 5.72e-6, 5.09e-6, 4.30e-6, 3.33e-6, 2.45e-6]
    x = np.array(x)
    y = np.array(y)
    # n = int(input("input the number of points: "))
    # print("Enter the points ")
    # x = np.zeros(n)
    # y = np.zeros(n)
    # for i in range(n):
    #     x[i],y[i] = map(float,input().split())
    X, Y = getMatrices(x, y, 3)

    status, coefficients = GaussianEliminationPP(X, Y)
    # print(coefficients)


# 7
# 80 6.47
# 40 6.24
# -40 5.72
# -120 5.09
# -200 4.3
# -280 3.33
# -340 2.45
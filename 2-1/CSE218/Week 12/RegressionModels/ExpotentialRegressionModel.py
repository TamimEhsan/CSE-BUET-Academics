import numpy as np

def fx(a,b,x):
    return a*(np.e**(b*x))

def findExpotentialRegression(x,y):
    n = len(x)
    y = np.log(y)
    denominator = n*sum(x*x)-sum(x)*sum(x)
    a1 = (n*sum(x*y) - sum(x)*sum(y))/denominator
    a0 = ( sum(x*x)*sum(y) - sum(x)*sum(x*y) )/denominator
    a0 = np.e**a0
    return a0, a1


if __name__ == '__main__':
    n = int(input("input the number of points: "))
    print("Enter the points ")

    x = np.zeros(n)
    y = np.zeros(n)
    for i in range(n):
        x[i], y[i] = map(float, input().split())

    findExpotentialRegression(x, y)

# 5
# 0.698132 0.188224
# 0.959931 0.209138
# 1.134464 0.230052
# 1.570796 0.250965
# 1.919862 0.313707


# 7
# 1 0.5
# 2 2.5
# 3 2.0
# 4 4.0
# 5 3.5
# 6 6.0
# 7 5.5
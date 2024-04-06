import numpy as np
from math import ceil, floor, pow
def roundd(x,n):
    return np.format_float_positional(x, precision=n, unique=False, fractional=False, trim='.')

def truncc(N):
    neg = False
    if N<0:
        neg = True
        N = -N
    n = 5
    b = N
    i = 0;
    while (b >= 1):
        b = b / 10
        i = i + 1

    d = n - i
    b = N
    b = b * pow(10, d)
    e = b
    if (float(e) == float(ceil(b))):
        f = (ceil(b))
        h = f - 2
        if (h % 2 != 0):
            e = e - 1
    j = floor(e)
    m = pow(10, d)
    j = j / m
    if neg:
        j = -j
    return np.around(j,n)


def GaussianElimination(A, B, d):
    n = len(A)
    x = np.zeros(n)
    A = np.append(A, B, axis=1)
    # Naive Gaussian Elimination
    for j in range(n):  # goes right
        for i in range(j + 1, n):  # goes down
            if A[j][j] == 0:
                print("Error! found Zero!")
                return [False, x]
            factor = A[i][j] / A[j][j]
            factor = truncc(factor)
            # print("#######################")
            # print("factor ", factor, "\n")
            # print("current row ", A[j], "\n")
            # print("chamged row ")
            # for k in range(n+1):
            #     print(truncc(A[j][k]*factor))

            for k in range(n+1):
                t = A[j][k] * factor
                print("DDD ",A[i][k])
                print("DDD ",truncc(t))
                t = truncc(t)
                A[i][k] = A[i][k] - t
                print("debig",A[i][k])
                A[i][k] = truncc(A[i][k])
                print("debuuuug",A[i][k])

            if d == 1:
                print(A, "\n")

    # Back calculation
    for i in range(n - 1, -1, -1):
        x[i] = A[i][n]
        for j in range(i + 1, n):
            x[i] = x[i] - x[j] * A[i][j]
        x[i] = x[i] / A[i][i]
    return [True, np.around(np.array([x]).T, 4)]


if __name__ == '__main__':
    np.set_printoptions(suppress=True)
    print(2.5-2.49)
    exit(0)
    # A = np.array([[25,5,1],[64,8,1],[144,12,1]],float)
    # B = np.array([[106.8],[177.2],[279.2]],float)
    n = int(input())
    A = np.zeros((n, n))
    B = np.zeros((n, 1))
    for i in range(n):
        A[i] = np.array([list(map(float, input().split()))], float)

    for i in range(n):
        B[i][0] = float(input())

    status, x = GaussianElimination(A, B, 1)
    if status:
        for row in x:
            print(row[0])

# 3
# 25 5 1
# 64 8 1
# 144 12 1
# 106.8
# 177.2
# 279.2

import numpy as np

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

            print("#######################")
            print("factor ", factor, "\n")
            print("current row ", A[j], "\n")
            print("chamged row ", A[j] * factor, "\n")

            A[i] = A[i] - A[j] * factor

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

import numpy as np

def GaussianEliminationPP(A, B):
    n = len(A)
    x = np.zeros(n)

    A = np.append(A, B, axis=1)
    # Naive Gaussian Elimination
    for j in range(n):  # goes right

        maxindex = abs(A[j:,j]).argmax() + j
        if maxindex != j:
            A[[j, maxindex]] = A[[maxindex, j]]
            B[[j, maxindex]] = B[[maxindex, j]]
        for i in range(j + 1, n):  # goes down
            if A[j][j] == 0:
                print("Error! found Zero!")
                return [False, x]
            factor = A[i][j] / A[j][j]
            for k in range(n + 1):
                A[i][k] = A[i][k] - factor * A[j][k]


    # Back calculation
    for i in range(n - 1, -1, -1):
        x[i] = A[i][n]
        for j in range(i + 1, n):
            x[i] = x[i] - x[j] * A[i][j]
        x[i] = x[i] / A[i][i]
    return [True, np.array([x]).T]


import numpy as np

def random_symmetric_matrix(n):
    
    # generate a random invertible symmetric matrix
    A = np.random.randint(1, 10, size=(n,n))
    A = A + A.T
    det = np.linalg.det(A)
    while det == 0:
        # generate a random matrix
        A = np.random.randint(1, 10, size=(n,n))
        A = A + A.T
        # find determinant of matrix
        det = np.linalg.det(A)
    # return matrix
    return A
    

# write main function and take input n
if __name__ == "__main__":
    n = int(input("Enter the value of n: "))
    # call random_eigen function
    A = random_symmetric_matrix(n)
    
    # find eigen values and eigen vectors
    eigen_values, eigen_vectors = np.linalg.eig(A)
    
    # reconstruct matrix from eigen values and eigen vectors
    B = np.dot(np.dot(eigen_vectors, np.diag(eigen_values)), np.linalg.inv(eigen_vectors))
    # check if A and B are equal
    if np.allclose(A, B):
        print("A and B are equal")
    else:
        print("A and B are not equal")

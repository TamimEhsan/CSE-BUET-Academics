import cv2
import numpy as np
import matplotlib.pyplot as plt

def low_rank_approximation(img, k):
  
    # singular value decomposition
    u, s, v = np.linalg.svd(img)
    # low rank approximation
    img_approx = np.matrix(u[:, :k]) * np.diag(s[:k]) * np.matrix(v[:k, :])
    return img_approx

if __name__ == "__main__":
    # Read the image
    img = cv2.imread("image.jpg")
    # downsample the image
    img = cv2.resize(img, None, fx=0.25, fy=0.25)
    # Convert to grayscale
    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    
    low = 1
    high = min(img.shape[0], img.shape[1])
    res = high

    images = []
    images.append([low, low_rank_approximation(img, low)])
    images.append([high, low_rank_approximation(img, high)])
    while low <= high:
        mid = (low + high) // 2
        img_approx = low_rank_approximation(img, mid)
        images.append([mid, img_approx])
        plt.imshow(img_approx, cmap="gray")
        plt.show(block=False)
        decision = int(input("Can you read author name? "+str(mid)+"  (1/0)"))
        plt.close()
        if decision == 1:
            res = mid
            high = mid - 1
        else:
            low = mid + 1
    print("Rank of the image is: ", res)
    # sort the images by rank
    images.sort(key=lambda x: x[0])
    # display the images in a subplot
    fig = plt.figure(figsize=(8, 16))
    columns = 4
    rows = 3
    for i in range(1, len(images) + 1):
        fig.add_subplot(rows, columns, i)
        plt.imshow(images[i-1][1], cmap="gray")
        if images[i-1][0] == res:
            plt.title("Rank: "+str(images[i-1][0])+" (lowest readable)",fontsize = 10)
        else:
            plt.title("Rank: "+str(images[i-1][0]),fontsize = 10)
    plt.show()
    

   


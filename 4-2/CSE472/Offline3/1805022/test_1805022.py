import pickle
import numpy as np
import pandas as pd
from sklearn.metrics import f1_score
import torchvision.datasets as ds
from torchvision import transforms
from train_1805022 import *

# load the pickle file
with open('model_1805022.pkl', 'rb') as f:
    model = pickle.load(f)

# test the model
# read the test data
independent_test_dataset = ds.EMNIST(root='./data', split='letters',
                                train=False,
                                transform=transforms.ToTensor())



test_arr = preprocess(independent_test_dataset)

# split into X_test, Y_test
X_test = np.array([data[0]/255. for data in test_arr])
Y_test = np.array([data[1] for data in test_arr])
Y_test = one_hot_encode(Y_test)
# predict the result
predictions = predict(model, X_test)
accuracy = calculate_accuracy(predictions, Y_test)
print(f"test accuracy:" + str(accuracy*100))
print(f"test f1 score:" + str(f1_score(np.argmax(Y_test, axis=1), np.argmax(predictions, axis = 1), average='macro')*100))

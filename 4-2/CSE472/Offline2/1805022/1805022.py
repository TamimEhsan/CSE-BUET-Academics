import pandas as pd
import numpy as np
# import matplotlib.pyplot as plt

from sklearn.preprocessing import StandardScaler
from sklearn.metrics import classification_report
from sklearn.model_selection import train_test_split

def entropy(q):
    if q == 0 or q == 1:
        return 0
    return -q * np.log2(q) - (1 - q) * np.log2(1 - q)

def information_gain(X,y,feature):
    # find unique values in feature
    unique_values = np.unique(X[feature])
    # print(len(unique_values))
    
    # find entropy of each unique value in feature
    remainder = 0
    dictpk = {}
    dictnk = {}
    p = 0
    n = 0
    
    
    
    for i in range(X.shape[0]):
        value = X[feature][i]
        if y[i] == 1:
            p += 1
            if value in dictpk:
                dictpk[value] += 1
            else:
                dictpk[value] = 1
        else:
            n += 1
            if value in dictnk:
                dictnk[value] += 1
            else:
                dictnk[value] = 1
        
        
    for value in unique_values:
        if value in dictpk:
            pk = dictpk[value]
        else:
            pk = 0
        if value in dictnk:
            nk = dictnk[value]
        else:
            nk = 0
        remainder += (pk + nk) / X.shape[0] * entropy(pk / (pk + nk))

        # print("pk = ",pk)
        # print("nk = ",nk)
    
    y_entropy = entropy(p / (p + n))

    gain = y_entropy - remainder
        
    return gain

def find_k_best_feature(X,y,k):
    print("X.shape = ",X.shape)
    # find information gain for each feature
    information_gains = []
    for feature in X.columns:
        information_gains.append([information_gain(X,y,feature),feature])
        # break
        
    # print("information_gains = ",information_gains)
    # sort the information gains in descending order
    information_gains.sort(reverse=True)
    # print("information_gains = ",information_gains)
    # return
    # find the feature names
    feature_names = []
    for i in range(k):
        feature_names.append(information_gains[i][1])
    
    # print("feature_names = ",feature_names)
    return feature_names
    
def Telco_Customer_Data_Processing():
    # read data
    df = pd.read_csv('Dataset/WA_Fn-UseC_-Telco-Customer-Churn.csv')
    
    # Seperate the target variable
    y = df['Churn']
    X = df.drop(['Churn','customerID'], axis=1)


    y = y.map({'Yes':1, 'No':0})
    
    # data type of columns
    # print("X.dtypes = \n",X.dtypes)

    # Process column 'TotalCharges' to numeric
    X['TotalCharges'] = pd.to_numeric(X['TotalCharges'], errors='coerce')

    # replace missing values with mean
    X['TotalCharges'] = X['TotalCharges'].fillna(X['TotalCharges'].mean()) 

    # replace missing values with mode
    # X['tenure'] = X['tenure'].fillna(X['tenure'].mode()[0]) 

    # find k best features
    filter = find_k_best_feature(X,y,10)
    # print(X.shape)
    X = X[filter]
    # print(X.shape)
    # Find the categorical columns
    categorical_columns = X.select_dtypes(include=['object'])

    # Convert categorical columns to numeric
    X = pd.get_dummies(X, columns=categorical_columns.columns)
    
    # normalize the data
    scaler = StandardScaler()
    X_scaled = scaler.fit_transform(X)
    # transform to dataframe
    X = pd.DataFrame(X_scaled, columns=X.columns)
    
    # map target variable to 0 and 1
    
    
    X = X.values
    y = y.values
    # Split the data into train and test
    X_train,X_test,y_train,y_test = train_test_split(X,y,test_size=0.2,random_state=42)
    # y_train = y_train.reshape(-1, 1)
    # y_test = y_test.reshape(-1, 1)
    return (X_train,X_test,y_train,y_test)



def Adult_Salary_Data_Processing():
    # read data
    df = pd.read_csv('Dataset/Adult/adult.data', header=None)
    
    # Seperate the target variable
    y = df[14]
    X = df.drop([14], axis=1)

    # map values in y to 0 and 1
    y = y.map({' <=50K':0, ' >50K':1})

    # print(X.head())
    # find k best features
    filter = find_k_best_feature(X,y,10)
    # print(X.shape)
    X = X[filter]
    # data type of columns
    # print("X.dtypes = \n",X.dtypes)

    # Find missing values
    # print("X.isnull().sum() = \n",X.isnull().sum())

    # Find categorical columns
    categorical_columns = X.select_dtypes(include=['object'])

    # Convert categorical columns to numeric
    X = pd.get_dummies(X, columns=categorical_columns.columns,drop_first=True)
    categorical_columns = X.select_dtypes(include=['object'])
    # print unique values in categorical columns
    # for col in categorical_columns:
    #     print(categorical_columns[col].value_counts())
    #     print("=====================================")

    # print("X.shape = ",X.shape)

    # normalize the data
    scaler = StandardScaler()
    # convert to numpy array
    

    X_scaled = scaler.fit_transform(X.values)
    # transform to dataframe
    X = pd.DataFrame(X_scaled, columns=X.columns)
    # print(y[0])
    
    X = X.values
    y = y.values
    # print(y.shape)
    # print(y.head())
    # Split the data into train and test
    X_train,X_test,y_train,y_test = train_test_split(X,y,test_size=0.2,random_state=42, stratify=y)
    return (X_train,X_test,y_train,y_test)

    
def Credit_Card_Data_Processing(smaller_dataset=False):
    # read data
    df = pd.read_csv('Dataset/creditcard.csv')

    if smaller_dataset:
        positive_data = df[df['Class'] == 1]
        negative_data = df[df['Class'] == 0].sample(n=20000, random_state=42)
        df = pd.concat([positive_data,negative_data],ignore_index=True)
        df = df.sample(frac=1, random_state=42).reset_index(drop=True)


    X = df.drop(['Class'], axis=1)
    y = df['Class']

    # find k best features
    filter = find_k_best_feature(X,y,10)
    # print(X.shape)
    X = X[filter]
    
    # normalize the data
    scaler = StandardScaler()
    X_scaled = scaler.fit_transform(X.values)
    # transform to dataframe
    X = pd.DataFrame(X_scaled, columns=X.columns)
    
    # Split the data into train and test
    X = X.values
    y = y.values
    X_train,X_test,y_train,y_test = train_test_split(X,y,test_size=0.2,random_state=42, stratify=y)
    return (X_train,X_test,y_train,y_test)

    
# sigmoid function for squishing the values between 0 and 1
def sigmoid(z):
    return 1 / (1 + np.exp(-z))

# normalize the input data
def normalize(X):
    return (X - np.mean(X, axis=0)) / np.std(X, axis=0)

def calculate_loss(y_true, y_pred):
    return np.mean((y_true - y_pred)**2) 

def gradient(X, y_true, y_pred):
    return -np.dot(X.T, (y_pred - y_true)) / y_true.shape[0]





def train(X, y_true, epochs, learning_rate, loss_threshold):
    # add bias column, f(x) = bias + w.T * x
    X = np.insert(X, 0, 1, axis=1)
    # initialize weights for each feature
    W = np.zeros((X.shape[1],1))
    # reshape target variable
    # print("y_true.shape prev = ",y_true.shape)
    y_true = y_true.reshape(-1, 1)
    # print("y_true.shape after = ",y_true.shape)
    # initialize loss list
    
    # initialize epoch counter
    
    for i in range(epochs):
        
        y_pred = sigmoid(np.dot(X, W))
        loss = calculate_loss(y_true, y_pred)

        if loss < loss_threshold:
            break
        
        # print("current_loss = ",current_loss)
        # print("loss_list[-1] = ",loss_list[-1])
        # print("loss_list[-1] - current_loss = ",loss_list[-1] - current_loss)
        
        # print("W = ",W)
        # print("gradient(X, y_true, y_pred) = ",gradient(X, y_true, y_pred))
        W = W + learning_rate * gradient(X, y_true, y_pred)
        
    return W

def predict(X,w):
    X = normalize(X)

    # add bias column, f(x) = bias + w.T * x
    X = np.insert(X, 0, 1, axis=1)
    y_pred = sigmoid(np.dot(X, w))

    # convert probabilities to 0 and 1
    y_pred = [1 if elem >= 0.5 else 0 for elem in y_pred]
    
    return np.array(y_pred)

    
### adabost


def weighted_majority(hypothesis, z):
    weight = np.zeros(len(hypothesis[0]))
    for i in range(len(hypothesis)):
        for j in range(len(hypothesis[i])):
            weight[j] += hypothesis[i][j]*z[i]
    # weight = weight/np.sum(weight)
    return weight




def adaboost(X, y, boosting_round):
    # W is the weight of each sample not each feature
    W = np.full(X.shape[0],1/ X.shape[0]) 
    hypothesis = []
    z = []

    for _ in range(boosting_round):
        # resample the data
        idx = np.random.choice(X.shape[0], X.shape[0], p=W)
        X_train = X[idx]
        y_train = y[idx]
        # train the model
        w = train(X_train, y_train, epochs=100, learning_rate=0.01, loss_threshold=0.1)
        # predict the output
        y_pred = predict(X, w)
        # calculate error
        error = np.sum(W * (y_pred != y_train))

        if error > 0.5:
            continue
        for i in range(len(y_pred)):
            if y_pred[i] == y_train[i]:
                W[i] = W[i] * error / (1 - error)
        
        W = W / np.sum(W)
        hypothesis.append(w)
        z.append(np.log2((1 - error) / error))
    # print(hypothesis)
    return weighted_majority(hypothesis, z)


def performance(y_true, y_pred,only_accuracy=False):
    num_samples = y_true.shape[0]
    
    true_positive = 0
    false_negative = 0
    true_negative = 0
    false_positive = 0
    
    for i in range(num_samples):
        if y_true[i] == 1 and y_pred[i] == 1:
            true_positive = true_positive + 1
        elif y_true[i] == 1 and y_pred[i] == 0:
            false_negative = false_negative + 1
        elif y_true[i] == 0 and y_pred[i] == 0:
            true_negative = true_negative + 1
        else:
            false_positive = false_positive + 1
            
    
    # print("true_positive = ",true_positive)
    # print("false_negative = ",false_negative)
    # print("true_negative = ",true_negative)
    # print("false_positive = ",false_positive)

    accuracy = (true_positive + true_negative) / num_samples
    sensitivity = true_positive / (true_positive + false_negative)
    specificity = true_negative / (true_negative + false_positive)
    precision = true_positive / (true_positive + false_positive+1)
    false_discovery_rate = false_positive / (true_positive + false_positive+1)
    f1_score = 2 * sensitivity * precision / (sensitivity + precision)

    if only_accuracy:
        print("accuracy = ",round(accuracy,4))
    else:
        print("accuracy = ",round(accuracy,4))
        print("sensitivity = ",round(sensitivity,4))
        print("specificity = ",round(specificity,4))
        print("precision = ",round(precision,4))
        print("false_discovery_rate = ",round(false_discovery_rate,4))
        print("f1_score = ",round(f1_score,4))
    return 

def telco_logres():
    X_train,X_test,y_train,y_test = Telco_Customer_Data_Processing()


    w = train(X_train, y_train, epochs=1000, learning_rate=0.01, loss_threshold=0.01)

    print("\nTelco train\n")
    y_pred = predict(X_train,w)
    performance(y_train,y_pred)

    print("\nTelco test\n")
    y_pred = predict(X_test,w)
    performance(y_test,y_pred)

def adult_logres():
    X_train,X_test,y_train,y_test = Adult_Salary_Data_Processing()


    w = train(X_train, y_train, epochs=1000, learning_rate=0.01, loss_threshold=0.01)

    print("\nAdult train\n")
    y_pred = predict(X_train,w)
    performance(y_train,y_pred)

    print("\nAdult test\n")
    y_pred = predict(X_test,w)
    performance(y_test,y_pred)



def credit_logres():
    X_train,X_test,y_train,y_test = Credit_Card_Data_Processing()

    w = train(X_train, y_train, epochs=1000, learning_rate=0.01, loss_threshold=0.01)

    print("\nCredit train\n")
    y_pred = predict(X_train,w)
    performance(y_train,y_pred)

    print("\nCredit test\n")
    y_pred = predict(X_test,w)
    performance(y_test,y_pred)


def telco_adaboost():
    X_train,X_test,y_train,y_test = Telco_Customer_Data_Processing()
    

    for boosting_round in [5,10,15,20]:
        print("\nboosting_round = ",boosting_round)
        w = adaboost(X_train, y_train,boosting_round)
        
        print("telco train")
        y_pred = predict(X_train,w)
        performance(y_train,y_pred,True)
        
        print("\nTelco test")
        y_pred = predict(X_test,w)
        performance(y_test,y_pred,True)
    


def adult_adaboost():
    X_train,X_test,y_train,y_test = Adult_Salary_Data_Processing()
    

    for boosting_round in [5,10,15,20]:
        print("\nboosting_round = ",boosting_round)
        w = adaboost(X_train, y_train,boosting_round)
        
        print("telco train")
        y_pred = predict(X_train,w)
        performance(y_train,y_pred,True)
        
        print("\nTelco test")
        y_pred = predict(X_test,w)
        performance(y_test,y_pred,True)
    

def credit_adaboost():
    X_train,X_test,y_train,y_test = Credit_Card_Data_Processing()


    for boosting_round in [5,10,15,20]:
        print("\nboosting_round = ",boosting_round)
        w = adaboost(X_train, y_train,boosting_round)
        
        print("Credit train")
        y_pred = predict(X_train,w)
        performance(y_train,y_pred,True)
        
        print("\nCredit test")
        y_pred = predict(X_test,w)
        performance(y_test,y_pred,True)


telco_logres()
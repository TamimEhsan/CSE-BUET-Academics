import numpy as np 
import torchvision.datasets as ds
from torchvision import transforms
from matplotlib import pyplot as plt
from sklearn.metrics import accuracy_score, f1_score
np.random.seed(1)

def preprocess(dataset):
    train_val = []
    # convert to numpy
    for data in dataset:
        image = np.array(list(map(float, data[0].numpy().flatten())))
        label = np.array(data[1])

        if not np.isnan(label):
            train_val.append((image, label))

    train_val = np.array(train_val, dtype=object)
    np.random.shuffle(train_val)
    return train_val

def load_data():
    
    train_validation_dataset = ds.EMNIST(root='./data', split='letters',
                                train=True,
                                transform=transforms.ToTensor(),
                                download=True)


    independent_test_dataset = ds.EMNIST(root='./data', split='letters',
                                train=False,
                                transform=transforms.ToTensor())


    train_val = preprocess(train_validation_dataset)

    # split the data into train and validation
    train_set = train_val[:int(len(train_val) * 0.85)]
    val_set = train_val[int(len(train_val) * 0.85):]

    # split into X_train, Y_train, X_val, Y_val
    X_train = np.array([data[0]/255. for data in train_set])
    Y_train = np.array([data[1] for data in train_set])
    X_validate = np.array([data[0]/255. for data in val_set])
    Y_validate = np.array([data[1] for data in val_set])

    # convert to numpy
    test = preprocess(independent_test_dataset)

    # split into X_test, Y_test
    X_test = np.array([data[0]/255. for data in test])
    Y_test = np.array([data[1] for data in test])

    print(Y_test[0])


    return X_train, Y_train, X_validate, Y_validate, X_test, Y_test

def one_hot_encode(Y):
    Y = Y.astype(int)
    Y = Y-1
    Y = np.squeeze(Y)
    Y = np.eye(26)[Y.reshape(-1)]
    # Y = np.reshape(Y, (len(Y), 26, 1))
    return Y

def Adam_update(param, gradient, m, v, t, beta1=0.9, beta2=0.999, epsilon=1e-8, alpha=0.001):
    m = beta1 * m + (1-beta1) * gradient
    v = beta2 * v + (1-beta2) * np.power(gradient, 2)
    m_hat = m / (1 - np.power(beta1, t))
    v_hat = v / (1 - np.power(beta2, t))
    param = param - alpha * m_hat / (np.sqrt(v_hat) + epsilon)
    return param, m, v

class Layer:
    def __init__(self):
        self.input = None
        self.output = None

    def forward(self, input):
        # TODO: return output
        pass

    def backward(self, output_gradient, learning_rate):
        # TODO: update parameters and return input gradient
        pass


class Dense(Layer):
    def __init__(self, input_size, output_size):
        self.m_w = np.zeros((input_size, output_size))
        self.v_w = np.zeros((input_size, output_size))
        self.m_b = np.zeros(output_size)
        self.v_b = np.zeros(output_size)
        self.t = 0
        # he initialization
        self.weights = np.random.randn(input_size,output_size) * np.sqrt(2.0 / input_size)
        self.bias = np.random.randn(output_size)
        

    def forward(self, input):
        self.input = input
        self.output = np.dot(self.input,self.weights) + self.bias
        return self.output

    def backward(self, output_gradient, learning_rate):
        input_gradient = np.dot(output_gradient,self.weights.T) / output_gradient.shape[1]
        weights_gradient = np.dot(self.input.T,output_gradient) / output_gradient.shape[1]
        bias_gradient = np.mean(output_gradient,axis=0)
        
        # adam update
        self.t += 1
        self.weights, self.m_w, self.v_w = Adam_update(self.weights, weights_gradient, m = self.m_w, v=self.v_w, t=self.t, alpha=learning_rate)
        self.bias, self.m_b, self.v_b = Adam_update(self.bias, bias_gradient, m=self.m_b, v=self.v_b, t=self.t, alpha=learning_rate)
    
        return input_gradient

class Dropout(Layer):
    def __init__(self, rate):
        self.rate = rate
        self.mask = None

    def forward(self, input):
        self.mask = np.random.binomial(1, self.rate, size=input.shape) / self.rate
        self.output = input * self.mask
        return self.output

    def backward(self, output_gradient, learning_rate):
        return output_gradient * self.mask

class Softmax(Layer):
    def __init__(self):
        pass

    def forward(self, input):
        self.input = input
        exp = np.exp(input - np.max(input, axis=-1, keepdims=True))
        self.output = exp / np.sum(exp, axis=-1, keepdims=True)
        return self.output

    def backward(self, output_gradient, learning_rate):
        return self.output - output_gradient

class Activation(Layer):
    def __init__(self, activation, activation_prime):
        self.activation = activation
        self.activation_prime = activation_prime

    def forward(self, input):
        self.input = input
        return self.activation(self.input)

    def backward(self, output_gradient, learning_rate):
        return np.multiply(output_gradient, self.activation_prime(self.input))


class Tanh(Activation):
    def __init__(self):
        def tanh(x):
            return np.tanh(x)

        def tanh_prime(x):
            return 1 - np.tanh(x) ** 2

        super().__init__(tanh, tanh_prime)

class Sigmoid(Activation):
    def __init__(self):
        def sigmoid(x):
            return 1 / (1 + np.exp(-x))

        def sigmoid_prime(x):
            s = sigmoid(x)
            return s * (1 - s)

        super().__init__(sigmoid, sigmoid_prime)

class ReLU(Layer):
    def __init__(self):
        self.input = None

    def forward(self, input):
        self.input = input
        return np.maximum(0, input)

    def backward(self, output_gradient, learning_rate):
        return np.multiply(output_gradient, np.where(self.input > 0, 1, 0))

def mse(y_true, y_pred):
    return  np.mean(np.mean(np.power(y_true - y_pred, 2), axis=1))

def mse_prime(y_true, y_pred):
    return 2 * (y_pred - y_true) / np.size(y_true)

def cross_entropy(y, output):
    """
    Assumes y and output are 2D numpy arrays
    """
    epsilon = 1e-11
    output = np.clip(output, epsilon, 1. - epsilon)
    return -np.sum(y * np.log(output)) / y.shape[0]

def cross_entropy_prime(y, output):
    """
    Assumes y and output are 2D numpy arrays
    """
    epsilon = 1e-11
    output = np.clip(output, epsilon, 1. - epsilon)
    return -y / output / y.shape[0]



def predict(network, input):
    output = input
    for layer in network:
        output = layer.forward(output)
    return output

# mini-batch gradient descent
def train(network, loss, x_train, y_train, x_val, y_val, epochs=10, learning_rate=0.01, batch_size=1024):
    train_loss = []
    validation_loss = []
    training_acc = []
    val_acc = []
    val_f1_scores = []

    best_model_params = None
    best_val_score = 0.0

    lr_dec = learning_rate / epochs

    for i in range(epochs):
        # shuffle the training data
        shuffle = np.random.permutation(x_train.shape[0])
        x_train = x_train[shuffle]
        y_train = y_train[shuffle]
        acc = 0.0
        correct_train = 0
        correct_val = 0
        total = 0
        training_loss = 0.0
        val_loss = 0.0

        # mini-batch gradient descent
        for j in range(0, len(x_train), batch_size):
            # forward propagation
            x_batch = x_train[j:j+batch_size]
            output = x_batch

            y_batch = y_train[j:j+batch_size]

            for layer in network:
                output = layer.forward(output)

            y_true = y_batch

            # calculate loss
            error = loss(output, y_true) / len(x_batch)
            training_loss += error.sum()

            # calculate accuracy
            correct_train += np.sum(np.argmax(output, axis=1) == np.argmax(y_true, axis=1))
            total += len(y_batch)

            # backward propagation
            error_prime = y_batch
            for layer in reversed(network):
                error_prime = layer.backward(error_prime, learning_rate)

        train_loss.append(training_loss)
        training_acc.append(correct_train / total)
                          
        # calculate validation loss
        output = x_val

        for layer in network:
            output = layer.forward(output)

        y_true = y_val
        error = loss(output, y_true)
        val_loss = error.sum()
        validation_loss.append(val_loss)

        # calculate validation accuracy
        correct_val += np.sum(np.argmax(output, axis=1) == np.argmax(y_true, axis=1))
        acc = correct_val / len(x_val)
        val_acc.append(acc)

        # save the best model
        if acc > best_val_score:
            best_val_score = acc
            best_model_params = network
            
        # calculate f1
        f1 = f1_score(np.argmax(y_true, axis=1), np.argmax(output, axis=1), average='macro')
        val_f1_scores.append(f1)

        if i % 5 == 0:
            print(f"Epoch {i+1}/{epochs}, Train Loss: {training_loss}, Val Loss: {val_loss}")
            print(f"Train Accuracy: {correct_train / total * 100}, Val Accuracy: {correct_val / len(y_val) * 100}", f"F1 Score: {f1 * 100}")

        learning_rate -= lr_dec

    # plot graphs
    import matplotlib.pyplot as plt
    # show both training and validation loss in the same graph wrt epoch
    plt.plot(train_loss, label='Train Loss')
    plt.plot(validation_loss, label='Val Loss')
    plt.xlabel('Epoch')
    plt.ylabel('Loss')
    plt.legend()
    plt.show()

    plt.plot(training_acc, label='Train Accuracy')
    plt.plot(val_acc, label='Val Accuracy')
    plt.xlabel('Epoch')
    plt.ylabel('Accuracy')
    plt.legend()
    plt.show()

    plt.plot(val_f1_scores, label='Val F1 Score')
    plt.xlabel('Epoch')
    plt.ylabel('F1 Score')
    plt.legend()
    plt.show()

    # confusion matrix
    import seaborn as sn
    from sklearn.metrics import confusion_matrix
    import pandas as pd

    output = x_val
    for layer in best_model_params:
        output = layer.forward(output)
    val_predictions = np.argmax(output, axis=1)
    cm = confusion_matrix(np.argmax(y_val, axis=1), val_predictions)
    df_cm = pd.DataFrame(cm, index = [i for i in "ABCDEFGHIJKLMNOPQRSTUVWXYZ"],
                columns = [i for i in "ABCDEFGHIJKLMNOPQRSTUVWXYZ"])
    plt.figure(figsize = (10,7))
    sn.heatmap(df_cm, annot=True, fmt='g')
    plt.show()

    return train_loss, val_loss

def calculate_accuracy(predictions, labels):
    predictions = np.argmax(predictions, axis=1)
    labels = np.argmax(labels, axis=1)
    print(predictions[:10])
    print(labels[:10])

    return np.mean(predictions == labels)


def emnist():
    X_train, Y_train, X_validate, Y_validate, X_test, Y_test = load_data()
    Y_train = one_hot_encode(Y_train)
    Y_validate = one_hot_encode(Y_validate)
    Y_test = one_hot_encode(Y_test)

    networks = [
        [
            Dense(28 * 28, 256),
            ReLU(),
            Dense(256, 26),
            Softmax()
        ],
        [
            Dense(28*28, 512),
            ReLU(),
            Dropout(0.8),
            Dense(512, 256),
            ReLU(),
            Dropout(0.8),
            Dense(256, 26),
            Softmax()
        ],
        [
            Dense(28*28, 256),
            ReLU(),
            Dropout(0.8),
            Dense(256, 26),
            Softmax()
        ]
    ]

    best_score = 0.0
    best_model = None

    learning_rates = [5e-3, 1e-3, 5e-4, 8e-3]

    
    for learning_rate in learning_rates:
        for network in networks:
            #initialize the network
            for layer in network:
                if isinstance(layer, Dense):
                    layer.m_b = np.zeros(layer.bias.shape[0])
                    layer.v_b = np.zeros(layer.bias.shape[0])
                    layer.m_w = np.zeros(layer.weights.shape)
                    layer.v_w = np.zeros(layer.weights.shape)
                    layer.t = 0
                    layer.weights = np.random.randn(layer.weights.shape[0], layer.weights.shape[1]) * np.sqrt(2.0 / layer.weights.shape[0])
                    layer.bias = np.random.randn(layer.bias.shape[0])
                
            # train
            train(network, cross_entropy, X_train, Y_train, X_validate, Y_validate, epochs=50, learning_rate=learning_rate)
            
            model = predict(network, X_test)
            accuracy = calculate_accuracy(model, Y_test)
            print(f"test accuracy:" + str(accuracy*100))
            print(f"test f1 score:" + str(f1_score(np.argmax(Y_test, axis=1), np.argmax(model, axis=1), average='macro')*100))

            if accuracy > best_score:
                best_score = accuracy
                best_model = network
    return best_model
    
# best_model = emnist()

# # store in pickle
# import pickle
# with open('1805022.pkl', 'wb') as f:
#     # first clear all unnecessary values
#     for layer in best_model:
#         layer.input = None
#         layer.output = None
#     pickle.dump(best_model, f)
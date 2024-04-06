import numpy as np
import matplotlib.pyplot as plt
import sys

n = len(sys.argv)
if n > 1:
    file_name = sys.argv[1]
# file_name = "6D_data_points"
np.random.seed(123)

def load_data():
    data = np.loadtxt('./Data/'+file_name+'.txt',delimiter=',',dtype=np.float32)
    return data

data = load_data()

N,M = data.shape
print(N,M)


# SL: https://stats.stackexchange.com/a/240492
def principal_component_analysis(_data):
    N,M = _data.shape
    # standardize data
    data = _data - np.mean(_data,axis=0)
    data = data/np.std(_data,axis=0)

    # pca analysis using svd
    u, s, v = np.linalg.svd(data)
    # reduce dimension
    s = np.diag(s)
    x_reduced = u[:,:M-1].dot(s[:M-1,:M-1])

    return x_reduced 


def truncate_dimension(data):
    N,M = data.shape
    while M > 2:
        data = principal_component_analysis(data)
        N,M = data.shape
        print(N,M)
    return data

data_truncated = truncate_dimension(data)
print(data_truncated[:5,:])


# plot the data
plt.scatter(data_truncated[:,0],data_truncated[:,1])
plt.savefig('1805022_'+file_name+'_data.png')
plt.show()



class GaussianMixtureModel:

    def __init__(self,data,k):
        self.data = data
        self.k = k
        self.N,self.M = data.shape
        self.miu = np.zeros((k,self.M))
        self.sigma = np.zeros((k,self.M,self.M))
        self.pi = np.zeros(k)
        self.gamma = np.zeros((self.N,self.k))

    def init_parameters(self):
        self.miu = self.data[np.random.choice(self.N,self.k,replace=False)]
        self.sigma = np.array([np.eye(self.M)]*self.k)
        self.pi = np.array([1/self.k]*self.k)

    def e_step(self):
        self.gamma = self.pi * np.array([self.gaussian(self.data, self.miu[j], self.sigma[j]) for j in range(self.k)]).T
        self.gamma /= self.gamma.sum(axis=1, keepdims=True)


    def m_step(self):
        Nk = np.sum(self.gamma, axis=0)
        self.miu = np.dot(self.gamma.T, self.data) / Nk[:, None]

        diff = self.data[:, None, :] - self.miu
        self.sigma = np.sum(self.gamma[:, :, None, None] * diff[:, :, :, None] * diff[:, :, None, :], axis=0) / Nk[:, None, None]

        # Ensure numerical stability using Cholesky decomposition
        for j in range(self.k):
            try:
                np.linalg.cholesky(self.sigma[j])
            except np.linalg.LinAlgError:
                # If Cholesky decomposition fails, add a small diagonal perturbation
                self.sigma[j] += 1e-6 * np.eye(self.M)


    # f(x) = (1/√(2πσ2)) (e[-(x-μ)^2]/2σ^2)
    def gaussian(self, x, miu, sigma):
        diff = x - miu
        exponent = -0.5 * np.sum(np.dot(diff, np.linalg.inv(sigma)) * diff, axis=-1)
        normalization = 1.0 / np.sqrt((2 * np.pi) ** self.M * np.linalg.det(sigma))
        return normalization * np.exp(exponent)


    # link: https://stephens999.github.io/fiveMinuteStats/intro_to_em.html
    def log_likelihood(self):
        temp = np.zeros((self.N, self.k))

        for j in range(self.k):
            temp[:, j] = self.pi[j] * self.gaussian(self.data, self.miu[j], self.sigma[j])

        ll = np.sum(np.log(np.sum(temp, axis=1)))

        return ll
  
    # done
    def fit(self, epoch):
        self.init_parameters()
        last_log_likelihood = self.log_likelihood()

        for i in range(epoch):
            self.e_step()
            self.m_step()

            current_log_likelihood = self.log_likelihood()
            if np.abs(current_log_likelihood - last_log_likelihood) < 1e-2:
                break

            last_log_likelihood = current_log_likelihood

            if i % 10 == 0:
                print('Epoch: ', i, ' Log Likelihood: ', current_log_likelihood)


    def predict(self):
        return np.argmax(self.gamma,axis=1)
    

    def plot(self, K):
        # scatter plot
        cluster = self.predict()
        print(cluster.shape)
        print(cluster[:5])
        plt.scatter(self.data[:,0],self.data[:,1],c=cluster)
        plt.savefig('1805022_'+file_name+'_scatter_'+str(K)+'.png')
        plt.show()

# model = GaussianMixtureModel(data_truncated,5)
# model.fit(100)
# model.plot()

# exit(0)

K_vs_log_likelihood = []
for K in range(3, 9):
    
    best_model = None
    best_log_likelihood = -np.inf
    for _ in range(5):
        print('K: ',K,' Iteration: ',_)
        model = GaussianMixtureModel(data_truncated,K)
        model.fit(500)
        
        current_log_likelihood = model.log_likelihood()
        if current_log_likelihood > best_log_likelihood:
            best_log_likelihood = current_log_likelihood
            best_model = model
           
    best_model.plot(K)
    
    K_vs_log_likelihood.append([K,best_log_likelihood])
    

    
K_vs_log_likelihood = np.array(K_vs_log_likelihood)
plt.plot(K_vs_log_likelihood[:,0],K_vs_log_likelihood[:,1], marker='o')
plt.xlabel('K')
plt.ylabel('Log Likelihood')
plt.savefig('1805022_'+file_name+'_log_likelihood.png')
plt.show()

# # find the best K
# best_K = K_vs_log_likelihood[np.argmax(K_vs_log_likelihood[:,1]),0]
# print('Best K: ',best_K)

# # plot the best model
# best_model = GaussianMixtureModel(data_truncated,int(best_K))
# best_model.fit(500)
# best_model.plot()
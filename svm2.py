#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Mar 31 17:03:20 2021

@author: zyy
"""



import numpy as np
import cvxopt
import cvxopt.solvers

# reference
# @ https://seanlee97.github.io/2018/06/01/SVM%E4%BB%8E%E5%85%A5%E9%97%A8%E5%88%B0%E4%BB%A3%E7%A0%81%E5%AE%9E%E7%8E%B0/
class SVC(object):
    def __init__(self, kernel='linear', C=1.0, sigma=1.0, **kwargs):
        if kernel not in ['linear', 'gaussian']:
            raise ValueError("Now only support linear and gaussian kernel")
        elif kernel == 'linear':
            kernel_fn = Kernel.linear()
        else:
            kernel_fn = Kernel.gaussian(sigma)

        self.kernel = kernel_fn  # kernel func
        self.C = C
        self._predictor = None

    def fit(self, X, y):
        lagr = self._lagr_multiplier(X, y)   # 获取拉格朗日乘子
        self._predictor = self._fit(X, y, lagr)

    def predict(self, X):
        return self._predictor.predict(X)
        
    
    def score(self, X, Y):
        total = len(X)
        correct = 0
        for i in range(0, total):
            predict_y =  self.predict(X[i])
            if predict_y == Y[i]:
                correct = correct + 1
        return correct / total
    
    def _fit(self, X, y, lagr, support_vector_threhold=1e-5):
        # 支持向量
        support_vectors_id = lagr > support_vector_threhold
        support_lagr = lagr[support_vectors_id]
        support_vectors = X[support_vectors_id]
        support_vector_tags = y[support_vectors_id]

        # 计算偏差
        bias = np.mean([y_k - Predictor(kernel=self.kernel,
                                        bias=0.0,
                                        W=support_lagr,
                                        support_vectors=support_vectors,
                                        support_vector_tags=support_vector_tags).predict(x_k) for (y_k, x_k) in zip(support_vector_tags, support_vectors)])

        return Predictor(kernel=self.kernel,
                         bias=bias,
                         W=support_lagr,
                         support_vectors=support_vectors,
                         support_vector_tags=support_vector_tags)

    def _lagr_multiplier(self, X, y):
        samples, features = X.shape

        k = self._mapping(X)
        # 二次规划
        P = cvxopt.matrix(np.outer(y, y)*k)
        q = cvxopt.matrix(-1 * np.ones(samples))
        
        G_std = cvxopt.matrix(np.diag(np.ones(samples)*-1))
        h_std = cvxopt.matrix(np.zeros(samples))
        
        # a_i \leq C
        G_slack = cvxopt.matrix(np.diag(np.ones(samples)))
        h_slack = cvxopt.matrix(np.ones(samples) * self.C)
        
        G = cvxopt.matrix(np.vstack((G_std, G_slack)))
        h = cvxopt.matrix(np.vstack((h_std, h_slack)))
       
        #y = y.reshape((1, y.shape[0]))
        A = cvxopt.matrix(y, (1, samples))
        b = cvxopt.matrix(0.0)
    
        solution = cvxopt.solvers.qp(P, q, G, h, A, b)
        # lagr multiplier
        return np.ravel(solution['x'])

    def _mapping(self, X):
        samples, features = X.shape
        k = np.zeros((samples, samples))
        # 空间映射
        for i, xi in enumerate(X):
            for j, xj in enumerate(X):
                k[i, j] = self.kernel(xi, xj)
        return k

class Predictor(object):
    def __init__(self,
                 kernel,
                 bias,
                 W,
                 support_vectors,
                 support_vector_tags):
        self._kernel = kernel
        self._bias = bias
        self._W = W
        self._support_vectors = support_vectors
        self._support_vector_tags = support_vector_tags
        assert len(support_vectors) == len(support_vector_tags)
        assert len(W) == len(support_vector_tags)

    def softmax(self, x):
        """Compute softmax values for each sets of scores in x."""
        x = np.array(x)
        x = np.exp(x)
        x.astype('float32')
        if x.ndim == 1:
            sumcol = sum(x)
            for i in range(x.size):
                x[i] = x[i]/float(sumcol)
        if x.ndim > 1:
            sumcol = x.sum(axis = 0)
            for row in x:
                for i in range(row.size):
                    row[i] = row[i]/float(sumcol[i])
        return x

    def predict(self, x):
        result = self._bias
        for z_i, x_i, y_i in zip(self._W,
                                 self._support_vectors,
                                 self._support_vector_tags):
            result += z_i * y_i * self._kernel(x_i, x)
        return np.sign(result).item()

class Kernel(object):
    # 线性核
    @staticmethod
    def linear():
        return lambda X, y: np.inner(X, y)

    # 高斯核
    @staticmethod
    def gaussian(sigma):
        return lambda X, y: np.exp(-np.sqrt(np.linalg.norm(X-y) ** 2 / (2 * sigma ** 2)))






from sklearn.model_selection import train_test_split



#Store variables as target y and the first two features as X (sepal length and sepal width of the iris flowers)
fname = 'complete.csv'
with open(fname, 'r+', encoding='utf-8') as f:
    s = [i[:-1].split(',') for i in f.readlines()]

X = []
y = []
for i in s:
    X.append(i[0:13])
    y.append(i[13])
    
num = len(X)
for i in range(0, num):
    X[i] = list(map(float, X[i]))
for i in range(0, num):
    y[i] = list(map(float, y[i]))

X = np.array(X)
y = np.array(y)
X_train, X_test, y_train, y_test = train_test_split(X, y, train_size=0.8, random_state = 0)

# y : 0 - 4
X_train_new = []
y_train_new = []
for i in range(0,5):
    t = []
    for j in range(0,len(y_train)):
        if y_train[j] == i:
            t.append(X_train[j])
    t = np.array(t)
    X_train_new.append(t)
    y_train_new.append(np.ones(len(t)) * i)
X_train_new = np.array(X_train_new)
y_train_new = np.array(y_train_new)

# DGA
error = 0.01
def jud(sample):
    res = [1,1,1,1,1]
    judge_one = 0
    judge_two = 1
    while res.count(1) > 1:
        clf = SVC(kernel="linear", C = 1)
        xx = []
        for i in X_train_new[judge_one]:
            xx.append(i)
        for i in X_train_new[judge_two]:
            xx.append(i)
        xx = np.array(xx)
        
        yy = []
        for i in y_train_new[judge_one]:
            yy.append(i)
        for i in y_train_new[judge_two]:
            yy.append(i)
        yy = np.array(yy)
        
        
        clf.fit(xx, yy)
        if abs(clf.predict(sample) - judge_one) < error:
            res[judge_two] = 0
            for i in range(0,5):
                if res[i] == 1 and i != judge_one:
                    judge_two = i
        elif abs(clf.predict(sample) - judge_two) < error:
            res[judge_one] = 0
            for i in range(0,5):
                if res[i] == 1 and i != judge_two:
                    judge_two = i     
        else:
            print('判断错误')
    return np.argmax(res)



total = len(X_test)
correct = 0
for i in range(0, total):
    predict_y =  jud(X_test[i])
    if predict_y == y_test[i]:
        correct = correct + 1
acu = correct / total
print(acu)

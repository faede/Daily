import pandas as  pd
import numpy as np
from sklearn.model_selection import  train_test_split
from sklearn.metrics import confusion_matrix
from sklearn import metrics
import matplotlib.pyplot as plt
from sklearn.metrics import accuracy_score



fname = 'sonar.all-data.csv'
raw_data = pd.read_csv(fname)
data = raw_data.values
X = np.array(data[:, 0:60])
Y = np.array(data[:, 60])
Y_to_int = []
for i in range(0, len(Y)):
    if Y[i] == 'R':
        Y_to_int.append(0)
    else:
        Y_to_int.append(1)
        
Y = np.array(Y_to_int)   

test_size = 0.2
seed = 0
X_train,X_test,Y_train,Y_test = train_test_split(X, Y, test_size = test_size, random_state = seed)



###################################### SVM ###################################
from sklearn import svm
svm = svm.SVC(kernel = 'rbf', gamma = 1, C = 1).fit(X_train, Y_train)
svm_pred = svm.predict(X_test)
#accuracy_svm = svm.score(X_test, Y_test)
#print("Accuracy of SVM Radial Basis Kernel:", accuracy_svm)
accuracy_svm = metrics.f1_score(Y_test, svm_pred, average = 'weighted')  
print("F1 of SVM:", accuracy_svm)





###################################### EM ###################################
from sklearn.mixture import GaussianMixture
gm = GaussianMixture(n_components = 2, random_state = 0).fit(X_train, Y_train)
gm_pred = gm.predict(X_test)
accuracy_gm = gm.score(X_test, Y_test)
#accuracy_em = accuracy_score(Y_test, gm_pred)
#print("Result of EM:", accuracy_em)
accuracy_em = metrics.f1_score(Y_test, gm_pred, average = 'weighted')  
print("F1 of EM:",accuracy_em)





###################################### KMeans ###################################
from sklearn.cluster import KMeans
kmeans = KMeans(n_clusters = 2, random_state = 0).fit(X_train, Y_train)
kmeans_pred = kmeans.predict(X_test)
accuracy_kmeans = metrics.f1_score(Y_test, kmeans_pred, average = 'weighted')  
print("F1 of K-Means:", accuracy_kmeans)





################################## KNeighbors ########################
from sklearn.neighbors import KNeighborsClassifier
neigh = KNeighborsClassifier(n_neighbors=3).fit(X_train, Y_train)
neigh_pred = neigh.predict(X_test)
accuracy_knn = metrics.f1_score(Y_test, neigh_pred, average = 'weighted')  
print("F1 of KNN:", accuracy_knn)





################################# Cart ###############################
from sklearn import tree
cart = tree.DecisionTreeClassifier().fit(X_train, Y_train)
cart_pred = cart.predict(X_test)
accuracy_cart = metrics.f1_score(Y_test, cart_pred, average = 'weighted')  
print("F1 of Cart:", accuracy_cart)




################################# C4.5 ###############################
from sklearn import tree
c45 = tree.DecisionTreeClassifier(criterion="entropy").fit(X_train, Y_train)
c45_pred = c45.predict(X_test)
accuracy_c45 = metrics.f1_score(Y_test, c45_pred, average = 'weighted')  
print("F1 of C4.5:", accuracy_c45)




################################# AdaBoost ############################
from sklearn.ensemble import AdaBoostClassifier
ada = AdaBoostClassifier(n_estimators=100, random_state=0).fit(X_train, Y_train)
ada_pred = ada.predict(X_test)
accuracy_ada = metrics.f1_score(Y_test, ada_pred, average = 'weighted')  
print("F1 of AdaBoost:", accuracy_ada)




################################# naive_bayes ############################
from sklearn.naive_bayes import GaussianNB
naive_bayes = GaussianNB().fit(X_train, Y_train)
naive_bayes_pred = ada.predict(X_test)
accuracy_naive_bayes = metrics.f1_score(Y_test, naive_bayes_pred, average = 'weighted')  
print("F1 of Naive Bayes:", accuracy_naive_bayes)

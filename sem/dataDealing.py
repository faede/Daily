#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Jul 16 01:58:22 2021

@author: zyy
"""


import numpy as np
from numpy import arange
from matplotlib import pyplot
from pandas import read_csv
from pandas import set_option
from pandas.plotting import scatter_matrix
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
from sklearn.model_selection import KFold
from sklearn.model_selection import cross_val_score
from sklearn.model_selection import GridSearchCV
from sklearn.linear_model import LinearRegression
from sklearn.linear_model import Lasso
from sklearn.linear_model import ElasticNet
from sklearn.tree import DecisionTreeRegressor
from sklearn.neighbors import KNeighborsRegressor
from sklearn.svm import SVR
from sklearn.pipeline import Pipeline
from sklearn.ensemble import RandomForestRegressor
from sklearn.ensemble import GradientBoostingRegressor
from sklearn.ensemble import ExtraTreesRegressor
from sklearn.ensemble import AdaBoostRegressor
from sklearn.metrics import mean_squared_error


# import  data 
filename = '02-boston_house_prices.csv'
names = ['CRIM','ZN','INDUS','CHAS','NOX','RM','AGE','DIS','RAD','TAX','PRTATTO','B', 'LSTAT','MEDV']
dataset = read_csv(filename, names = names,encoding = 'utf-8', header = 1)
# out
# print data dim
print(dataset.shape)
# check data type 
print(dataset.dtypes)

#dataset['CRIM'] = dataset['CRIM'].astype(np.float)
# check 30 head
print(dataset.head(10))



print('DATA decribe:')
print(dataset.describe())


print('Pearson Corr:')
print(dataset.corr(method='pearson'))


#####################################################################
#                    Data Visualization
#####################################################################



# Histogram
dataset.hist(sharex = False, sharey = False, xlabelsize = 1, ylabelsize = 1)
pyplot.show() 


# Density
dataset.plot(kind ='density',subplots = True, layout=(4,4), sharex = False, fontsize = 1)
pyplot.show()


# Boxplot
dataset.plot(kind ='box', subplots = True, layout = (4,4), sharex = False, sharey = False, fontsize = 8)
pyplot.show()


# Scatter Matrix
scatter_matrix(dataset)
pyplot.show()

# Correlation matrix
fig = pyplot.figure()
ax = fig.add_subplot(111)
ca = ax.matshow(dataset.corr(), vmin = -1, vmax = 1, interpolation = 'none')
fig.colorbar(ca)
ticks = np.arange(0, 14, 1)
ax.set_xticks(ticks)
ax.set_yticks(ticks)
ax.set_xticklabels(names)
ax.set_yticklabels(names)
pyplot.show()



# Split
array = dataset.values
X = array[:, 0:13]
Y = array[:, 13]

validation_size = 0.2
seed = 7
X_train, X_validation, Y_train, Y_validation = train_test_split(X, Y,test_size = validation_size, random_state = seed, shuffle = True)


# 10 flod check, using NMSE Function Evaluate
num_folds = 10
seed = 7
scoring = 'neg_mean_squared_error'


# Linear Model: 
# Linear Regression（LR）
# least absolute shrinkage and selection（LASSO）
# ElasticNet（EN）

models = {}
models['LR'] = LinearRegression()
models['LASSO'] = Lasso()
models['EN'] = ElasticNet()

# non-Linear Model：
# Classification And Regression Tree（CART）
# Support vector machine（SVM）
# k-nearest neighbors （KNN）
models['KNN'] = KNeighborsRegressor()
models['CART'] = DecisionTreeRegressor()
models['SVM'] = SVR()



results = []
for key in models:
    kfold = KFold(n_splits = num_folds, random_state = seed, shuffle = True)
    cv_result = cross_val_score(models[key], X_train, Y_train, cv = kfold, scoring = scoring)
    results.append(cv_result)
    print('%13s: mean: %.4f    std: %.4f' % (key, cv_result.mean(), cv_result.std()))

# Boxplot
fig = pyplot.figure()
fig.suptitle('Algorithm Comparison')
ax = fig.add_subplot(111)
pyplot.boxplot(results)
ax.set_xticklabels(models.keys())
pyplot.show()



# Evaluate
# Use normally distributed data to evaluate the model
pipelines = {}
pipelines['ScalerLR'] = Pipeline([('Scaler', StandardScaler()), ('LR',
LinearRegression())])
pipelines['ScalerLASSO'] = Pipeline([('Scaler', StandardScaler()), ('LASSO', Lasso())])
pipelines['ScalerEN'] = Pipeline([('Scaler',StandardScaler()), ('EN', ElasticNet())])
pipelines['ScalerKNN'] = Pipeline([('Scaler',StandardScaler()), ('KNN',
KNeighborsRegressor())])
pipelines['ScalerCART'] = Pipeline([('Scaler',StandardScaler()), ('CART',
DecisionTreeRegressor())])
pipelines['ScalerSVM'] = Pipeline([('Scaler',StandardScaler()), ('SVM', SVR())])

results = []
for key in pipelines:
    kfold = KFold(n_splits=num_folds, random_state = seed, shuffle = True)
    cv_result = cross_val_score(pipelines[key], X_train, Y_train, cv = kfold, scoring = scoring)
    results.append(cv_result)    
    print('%13s: mean: %.4f    std: %.4f' % (key, cv_result.mean(), cv_result.std()))

# Boxplot
fig = pyplot.figure()
fig.suptitle('Algorithm Comparison')
ax = fig.add_subplot(111)
pyplot.boxplot(results)
ax.set_xticklabels(pipelines.keys())
pyplot.show()




print('\n*************************  KNN  *************************')
# Choice Best Neighbor Number
scaler = StandardScaler().fit(X_train)
rescaledX = scaler.transform(X_train)
param_grid = {'n_neighbors': [1, 2, 3, 4, 5, 7, 9, 11, 15, 17, 20]}
model = KNeighborsRegressor()
kfold = KFold(n_splits = num_folds, random_state = seed, shuffle = True)
grid = GridSearchCV(estimator = model, param_grid = param_grid, scoring = scoring, cv = kfold)
grid_result = grid.fit(X = rescaledX, y = Y_train)
print('Best KNN Result parameter: %s  Use: %s' % (grid_result.best_score_, grid_result.best_params_))
cv_results = zip(grid_result.cv_results_['mean_test_score'],
grid_result.cv_results_['std_test_score'],grid_result.cv_results_['params'])
for mean, std, param in cv_results:
    print('mean: %.4f std: %f with %r' % (mean, std, param))

    
####################################  Enseemble  ####################################
#
# Bagging : randomForest（RF）Extremely randomized trees(ET)
# Boosting：AdaBoost（Ada）Gradient Boosting Machin（GBT）
#
######################################################################################

print('\n*************************  Bagging  *************************')
ensembles = {}
# CartReg
ensembles['ScaledAB'] = Pipeline([('Scaler',StandardScaler()), ('AB', AdaBoostRegressor())])
ensembles['ScaledAB-KNN'] = Pipeline([('Scaler',StandardScaler()), ('ABKNN', AdaBoostRegressor(base_estimator = KNeighborsRegressor(n_neighbors = 3)))])
ensembles['ScaledAB-LR'] = Pipeline([('Scaler',StandardScaler()), ('ABLR',AdaBoostRegressor(LinearRegression()))])
ensembles['ScaledGBR'] = Pipeline([('Scaler',StandardScaler()), ('RBR', GradientBoostingRegressor())])

# *********************************  Add  ******************************
ensembles['ScaledAB-DR'] = Pipeline([('Scaler',StandardScaler()), ('RBR',AdaBoostRegressor(DecisionTreeRegressor()))])



ensembles['ScaledRFR'] = Pipeline([('Scaler',StandardScaler()), ('RFR', RandomForestRegressor())])
ensembles['ScaledETR'] = Pipeline([('Scaler',StandardScaler()), ('ETR', ExtraTreesRegressor())])

results = []
for key in ensembles:
    kfold = KFold(n_splits = num_folds, random_state = seed, shuffle = True)
    cv_result = cross_val_score(ensembles[key], X_train, Y_train, cv = kfold, scoring = scoring)
    results.append(cv_result)
    print('%13s: mean: %.4f    std: %.4f' % (key, cv_result.mean(), cv_result.std()))

# Boxplot
fig = pyplot.figure()
fig.suptitle('Algorithm Comparison')
ax = fig.add_subplot(111)
pyplot.boxplot(results)
ax.set_xticklabels(ensembles.keys())
pyplot.show()








# Adjustment parameters  ---- GBM
print('\n*************************  GBM  *************************')
caler = StandardScaler().fit(X_train)
rescaledX = scaler.transform(X_train)
param_grid = {'n_estimators': [10, 50, 100, 200, 300, 400, 500, 600, 700, 800, 900]}
model = GradientBoostingRegressor()
kfold = KFold(n_splits = num_folds, random_state = seed, shuffle = True)
grid = GridSearchCV(estimator = model, param_grid=param_grid, scoring=scoring, cv = kfold)
grid_result = grid.fit(X = rescaledX, y = Y_train)
print('Best GBM: %s Use :%s' % (grid_result.best_score_, grid_result.best_params_))



# Adjustment parameters  ---- ET 
print('\n*************************  ET  *************************')
scaler = StandardScaler().fit(X_train)
rescaledX = scaler.transform(X_train)
param_grid = {'n_estimators': [5, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100]}
model = ExtraTreesRegressor()
kfold = KFold(n_splits = num_folds, random_state = seed, shuffle = True)
grid = GridSearchCV(estimator = model, param_grid = param_grid, scoring = scoring, cv = kfold)
grid_result = grid.fit(X = rescaledX, y = Y_train)
print(' Best ET: %s USe:%s' % (grid_result.best_score_, grid_result.best_params_))


# Adjustment parameters  ---- AdaDT
print('\n*************************  Ada_DecisionTreeRegressor  *************************')
scaler = StandardScaler().fit(X_train)
rescaledX = scaler.transform(X_train)
param_grid = {'n_estimators': [100, 120, 130, 140 ,150]}
model = AdaBoostRegressor(DecisionTreeRegressor(max_depth = 100), random_state = seed, loss='linear')
kfold = KFold(n_splits = num_folds, random_state = seed, shuffle = True)
grid = GridSearchCV(estimator = model, param_grid = param_grid, scoring = scoring, cv = kfold)
grid_result = grid.fit(X = rescaledX, y = Y_train)
print(' Best Ada: %s USe:%s' % (grid_result.best_score_, grid_result.best_params_))




################################ Final Training ################################
print('\n*************************  Final Training  *************************')
# Training
caler = StandardScaler().fit(X_train)
rescaledX = scaler.transform(X_train)
gbr = ExtraTreesRegressor(n_estimators = 80)
gbr.fit(X = rescaledX, y = Y_train)
# Test
rescaledX_validation = scaler.transform(X_validation)
predictions = gbr.predict(rescaledX_validation)
print('Prediction set ET', mean_squared_error(Y_validation, predictions))


# Training
caler = StandardScaler().fit(X_train)
rescaledX = scaler.transform(X_train)
gbr = GradientBoostingRegressor(n_estimators = 600)
gbr.fit(X = rescaledX, y = Y_train)
# Test
rescaledX_validation = scaler.transform(X_validation)
predictions = gbr.predict(rescaledX_validation)
print('Prediction set GBR', mean_squared_error(Y_validation, predictions))

# Training
caler = StandardScaler().fit(X_train)
rescaledX = scaler.transform(X_train)
gbr = AdaBoostRegressor(DecisionTreeRegressor(max_depth = 100), random_state=seed, loss='linear')
gbr.fit(X = rescaledX, y = Y_train)
# Test
rescaledX_validation = scaler.transform(X_validation)
predictions = gbr.predict(rescaledX_validation)
print('Prediction set AdaDR', mean_squared_error(Y_validation, predictions))

    
    
    
    
    
    
    
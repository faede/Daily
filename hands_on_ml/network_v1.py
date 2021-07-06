#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jul  6 08:56:35 2021

@author: zyy
"""
import tensorflow as tf
from numpy.random import RandomState

batch_size = 8

tf.compat.v1.disable_eager_execution()


w1 = tf.Variable(tf.random.normal((2, 3), stddev = 1, seed = 1))
w2 = tf.Variable(tf.random.normal((3, 1), stddev = 1, seed = 1))

x = tf.compat.v1.placeholder(tf.float32, shape = (None, 2), name = "x-input")
y_ = tf.compat.v1.placeholder(tf.float32, shape = (None, 1), name = "y-input")

a = tf.matmul(x, w1)
y = tf.matmul(a, w2)

y = tf.sigmoid(y)

cross_entropy = -tf.compat.v1.reduce_mean(
    y_ * tf.math.log(tf.clip_by_value(y, 1e-10, 1.0))\
     +(1 - y_) * tf.math.log(tf.clip_by_value(1-y, 1e-10, 1.0)))


learning_rate = 0.001
train_step = tf.compat.v1.train.AdamOptimizer(learning_rate).minimize(cross_entropy)

rdm = RandomState(1)
dataset_size = 128
X = rdm.rand(dataset_size, 2)
Y = [[int(x1 + x2 < 1)] for (x1, x2) in X]

with tf.compat.v1.Session() as sess:
    init_op = tf.compat.v1.global_variables_initializer()
    sess.run(init_op)
    print(sess.run(w1))
    print(sess.run(w2))
    
    STEPS = 5000
    for i in range(STEPS):
        start = (i * batch_size) % dataset_size
        end = min(start + batch_size, dataset_size)
        sess.run(train_step, feed_dict = {x:X[start:end], y_: Y[start:end]})
        
        if i % 1000 == 0:
            total_cross_entropy = sess.run(cross_entropy, feed_dict = {x:X, y_: Y})
            print("After %d tranining step(s), crosee entropy on all data is %g"%(i, total_cross_entropy))
    print(sess.run(w1))
    print(sess.run(w2))
    
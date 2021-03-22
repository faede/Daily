#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Mar 22 15:13:10 2021

@author: zyy
"""

import pandas as pd
import numpy as np
import math
df = pd.read_csv('ID3data.csv', header= None, sep = ',',names = ['ages','in','stu','dp','res'])




agevar = [0, 1, 2]
invar = [0, 1]
stuvar = [0, 1]
dpvar = [0, 1]
revar = ["yes", "no"]




def GetPoEn(i :int, col : list) -> int:
    att = ['ages','in','stu','dp','res']
    pval = [[0, 1, 2], [0, 1], [0, 1], [0, 1], ["yes", "no"]]
    total = col.count()
    ent = 0
    for i in pval[i]:
        n1 = col.loc[col[att[i]] == i].shape[0]
        ent += - n1/total * math.log(n1/total)
    return ent


for i in agevar:
    for j in invar:
        for k in stuvar:
            for m in dpvar:
                for n in revar:
                    print(df.loc[ (df["ages"] == i)  &  (df["in"] == j ) &  \
                                 (df["stu"] == k ) & (df["dp"] == m) & (df["res"] == n)].shape[0]  )
                    pass
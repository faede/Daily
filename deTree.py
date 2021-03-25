#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Mon Mar 22 15:13:10 2021

@author: zyy
"""

import pandas as pd
import numpy as np
import math

import copy
import math
import queue
import cv2
import sys
import os
import subprocess
from PIL import Image




T_lambda = 1
MAX_ENTROPY = 1e10
att = ['Age','Income','Student','Reputation','Result']
pval = [[0, 1, 2], [0, 1], [0, 1], [0, 1], ["yes", "no"]]
ALPHA = 2

def GetPoEn(chara:int, col : list) -> int:
    total = col.count().max()
    ent = 0
    for i in pval[chara]:
        #  D_i / D  , \sum D_i / D = 1
        per = col.loc[col[att[chara]] == i].shape[0] / total
        
        # entropy of Di
        # pos and neg
        pos_num = col.loc[ (col[att[chara]] == i ) & (col[att[4]] == 'yes')].shape[0] 
        neg_num = col.loc[ (col[att[chara]] == i ) & (col[att[4]] == 'no')].shape[0] 
        pro_pos = (pos_num + T_lambda)/(total + T_lambda)
        pro_neg = (neg_num + T_lambda)/(total + T_lambda)
        
        H_Di = - pro_pos * math.log(pro_pos) - pro_neg * math.log(pro_neg)
        
        ent += per * H_Di      
    return ent


def GetMaxEntGain(df: list, use) -> int:
    max_p = 0
    save_max = MAX_ENTROPY
    # The greater the information gain, the smaller the corresponding entropy
    for i in range(0,4):
        # print('chara :',i)
        en = GetPoEn(i, df)
        # print(en)
        if en < save_max and use[i] == 0:
            max_p = i
            save_max = en
    return max_p


def CheckAllCharaIsSame(df :list) -> bool:
    if df.loc[df['Result'] == 'no' ].shape[0] == 0 or  \
        df.loc[df['Result'] == 'yes' ].shape[0] == 0:
        return True
    return False

def CacCheckNeedPruning(chara: int , df: list, sz: int):
    total = df.shape[0]
    # actualy sz is 2 or 3
    sz = sz - 1
    # Before Pruing 
    C_Before = 0
    for i in pval[chara]:
        pos_num = df.loc[(df[att[chara]] == i)&(df['Result'] == 'yes')].shape[0]
        neg_num = df.loc[(df[att[chara]] == i)&(df['Result'] == 'no')].shape[0]
        C_Before +=  -(pos_num + T_lambda) * math.log( (pos_num + T_lambda)/(total + T_lambda) )
        C_Before +=  -(neg_num + T_lambda) * math.log( (neg_num + T_lambda)/(total + T_lambda) )
        pass
    C_Before += ALPHA * sz
    
    # After Pruning , |T| = 1
    # pos and neg
    pos_num = df.loc[df['Result'] == 'yes'].shape[0]
    neg_num = df.loc[df['Result'] == 'no'].shape[0]
    C_After = 0
    C_After +=  -(pos_num + T_lambda) * math.log((pos_num + T_lambda)/(total + T_lambda))
    C_After +=  -(neg_num + T_lambda) * math.log((neg_num + T_lambda)/(total + T_lambda))
    C_After += ALPHA * 1
    if C_After <= C_Before:
        return True
    else:
        return False

class node_id:
    num = 0
    
class Node(node_id):
    def __init__(self):
        self.val = None
        self.fa = None
        self.left = None
        self.three = None
        self.right = None
        self.chara = 0
        self.hasused = [0, 0 , 0, 0]
        self.dep = 0
        self.size = 0
        node_id.num += 1
        self.id = node_id.num
class Tree():
    k = 3
    def __init__(self) :
        self.root = Node()
    def BuildTree (self,elems: list):
        used = [0, 0 , 0, 0]
        self.root = self.__Build(self.root, elems, used, 0 ,0)
        self.root.chara = self.root.chara[3:]
        self.__SetSize(self.root)
        
        
        
    def __SetSize(self, root) -> int:
        if root == None:
            return 0
        root.size = self.__SetSize(root.left) + self.__SetSize(root.right)  \
                            + self.__SetSize(root.three) + 1
        return root.size
    
    
    def __Build(self, root: Node, col: list, uesd: list, dep: int, judg: int) -> Node:
        
        if CheckAllCharaIsSame(col):
            root = Node()
            root.val = col.copy()
            if col.loc[df['Result'] == 'no' ].shape[0] == 0:
                root.chara = 'yes '
            else:
                 root.chara = 'no '
            if judg == 0:
                root.chara = '0: ' + root.chara
            elif judg == 1:
                root.chara = '1: ' + root.chara
            else:
                root.chara = '2:' + root.chara
            return root
        root = Node()
        root.val = col.copy()
        root.hasused = uesd.copy()
        root.dep = dep
        if col.count().max() == 0:
            return None
        # pass to  next level 
        chara = GetMaxEntGain(col,root.hasused)
        
        if root.hasused[chara] == 1:
            return None
        
        chose_son = 0
        
        root.hasused[chara] = 1
            
        for i in  pval[chara]:
            psn = col.loc[col[att[chara]] == i]
            
            if chose_son == 0:
                root.left = self.__Build(root.left, psn, root.hasused, dep + 1, 0)
            elif chose_son == 1:
                root.right = self.__Build(root.right, psn, root.hasused, dep + 1, 1)
            else:
                root.three = self. __Build(root.three, psn, root.hasused, dep + 1, 2)
               
            root.chara = att[chara]
            if judg == 0:
                root.chara = '0: ' + root.chara
            elif judg == 1:
                root.chara = '1: ' + root.chara
            else:
                root.chara = '2:' + root.chara
                
            if root.left != None:
                root.left.fa = root
            if root.right != None:
                root.right.fa = root
            if root.three != None:
                root.three.fa = root
                
            
            chose_son += 1
            
        
        return root
    
    
    #re-define leaf as, which all son node is 'real leaf'
    def GetLeaf() -> list:
        pass
    def Pruing():
        pass
    
    
    def Graphviz(self):
        with open('detree.dot', 'a') as f:
            print("digraph G {", file = f)
        q = queue.Queue()
        q.put(self.root.left)
        q.put(self.root.right)
        while  not q.empty():
            top = q.get()
            with open('detree.dot', 'a') as f:
                print( top.fa.id,'[label=" ', top.fa.chara,'"]', file = f)
                print( top.id,'[label=" ', top.chara,'"]', file = f)
                print(top.fa.id,' -> ' , top.id, file = f)
            if top.left != None:
                q.put(top.left)
            if top.right != None:
                q.put(top.right)
            if top.three != None:
                q.put(top.three)
                
        with open('detree.dot', 'a') as f:
            print("}", file = f)
        
        # need Graphviz and set PATH right
        # subprocess.Popen('dot -Tpng -o kdtree.png kdtree.dot',shell=True)
        subprocess.Popen('/usr/local/bin/dot -Tpng -o detree.png detree.dot', shell = True)
        
        img = Image.open('detree.png')
        img.show()
        
        #image = cv2.imread('kdtree.png')
        #cv2.imshow("kd-Tree", image)
        # cv2.waitKey(0)        
        # cv2.destroyAllWindows()
            
        
        # import matplotlib.pyplot as plt
        # import matplotlib.image as mpimg
        # I = mpimg.imread('kdtree.png')
        # plt.imshow(I)
        
        
if __name__ == "__main__":
    
    df = pd.read_csv('ID3data.csv', header= None, sep = ',',names = att)
 
    t = Tree()
    t.BuildTree(df)
    t.Graphviz()
    # used = [0,0,0,0,0]
    #print(GetMaxEntGain(df))
    #print(df[550:560])
    print(t.root.chara)
    print(t.root.left.left.chara)
    print(t.root.left.chara)
    print(t.root.left.fa.chara)
    print(t.root.left.left.chara)
    print(t.root.right.chara)
    print(t.root.size)
    print(t.root.left.size)
    #print(t.root.val)
    #print(t.root.left.left.val)
    
    print(CacCheckNeedPruning(0, t.root.left.val, t.root.left.size))
    
    
    
    
    
    
    
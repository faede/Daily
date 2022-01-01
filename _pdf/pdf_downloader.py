#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec 31 12:19:35 2021

@author: zyy
"""

import requests
import os
import sys


def urldownload(url,filename=None):
    down_res = requests.get(url)
    with open(filename,'wb+') as file:
        file.write(down_res.content)
        
def create_dir(path, add_mode = 0):
    # if add_mode == 0, will not add files into unempty file
    folder = os.path.exists(path)
    if not folder:                 
        os.makedirs(path)
    else:
        if not add_mode:
            print('the floder exist content, please checkout!')
            sys.exit(1)

f = open("get_url.txt","r") 
urls = f.readlines()      # read lines
path = './Computer_Architecture/'
# need set add_mode argument
create_dir(path, add_mode = 0)
for url in urls:
    filename = url[-17:-1]
    filename = filename.replace('/','')
    
    filename = path + filename
    
    urldownload(url,filename)
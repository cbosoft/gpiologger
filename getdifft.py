#!/usr/bin/python

import time
import os
import subprocess as sp

import numpy as np

CWD = os.getcwd()

pr = sp.Popen('./gpiologger', shell=True, cwd=CWD, stdout=sp.PIPE)

try:
    for i in range(10):
        time.sleep(1)
    pr.kill()
except KeyboardInterrupt:
    pr.kill()

data = pr.stdout.readlines()
data = [float(line.decode('utf-8').split(',')[0]) for line in data]
print(np.average(np.diff(data)))

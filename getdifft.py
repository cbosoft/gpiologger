#!/usr/bin/python

import time
import os
import subprocess as sp
from tqdm import tqdm

import numpy as np

CWD = os.getcwd()

pr = sp.Popen('./gpiologger', shell=True, cwd=CWD, stdout=sp.PIPE)

l = 5
g = 2.0

print(f'Running logger for {l}s...')

try:
    for i in tqdm(range(int(l*g))):
        time.sleep(1.0/g)
    pr.kill()
except KeyboardInterrupt:
    pr.kill()
    print('\nCancelled early')

lines = pr.stdout.readlines()
data = [float(line.decode('utf-8').split(',')[0]) for line in lines]
dt = (10E-6)*np.diff(data)

print(f'Average time between samples: {np.average(dt):.3e} (min: {np.min(dt):.3e}, max: {np.max(dt):.3e})')

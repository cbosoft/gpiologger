#!/usr/bin/python

import time
import os
import subprocess as sp
from tqdm import tqdm

import numpy as np

CWD = os.getcwd()

pr = sp.Popen('./gpiologger', cwd=CWD, stdout=sp.PIPE)

l = 60
g = 2.0

print(f'Running logger for {l}s...')

try:
    for i in tqdm(range(int(l*g))):
        time.sleep(1.0/g)
    print('Killing process')
    print(pr.terminate())
except KeyboardInterrupt:
    pr.terminate()
    print('\nCancelled early')
print('Processing result')
lines = pr.stdout.readlines()[:100]

#data = list()
#for line in lines:
#    print(line)
#    line = line.decode('utf-8')
#    cells = line.split(',')
#    time = float(cells[0])
#    data.append(time)

data = [np.float64(line.decode('utf-8').split(',')[0]) for line in lines]
unit = 'ms'
dt = (1e3)*np.diff(data)

print(f'Average time between samples: {np.average(dt):.3f}{unit} (min: {np.min(dt):.3f}{unit}, max: {np.max(dt):.3f}{unit})')

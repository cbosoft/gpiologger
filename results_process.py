import numpy as np

pins = [16, 20, 21]
logfiles = [f'gpio_{pin}.csv' for pin in pins]

dts = list()
for logf in logfiles:
    with open(logf, 'r') as fp:
        lines = fp.readlines()

    cross_times = [float(line) for line in lines]
    part_dt = np.diff(cross_times)

    time_and_dt = list(zip(cross_times, part_dt))
    dts.extend(time_and_dt)

dts = sorted(dts)
times, dts = zip(*dts)

slot_width = np.pi/6.
speed_rads = np.divide(slot_width, dts)

from matplotlib import pyplot as plt

plt.plot(times, speed_rads)
plt.xlabel("Time/t")
plt.ylabel("Speed/$rads^-1$")
plt.show()

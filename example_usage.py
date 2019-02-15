import subprocess as sp
import RPi.GPIO as gpio

pins = [16, 20, 21]

gpio.setmode(gpio.BCM)

for pin in pins:
    gpio.setup(pin, gpio.IN, pull_up_down=gpio.PUD_UP)

logfiles = [f'gpio_pin{}.csv' for pin in pins]

pr = sp.Popen(['./gpiologger', *logfiles])

import time

for i in range(60):
    time.sleep(1)

pr.kill()
gpio.cleanup()

"""
ldr.py
Display analog data from Arduino using Python (matplotlib)
Author: Mahesh Venkitachalam
Website: electronut.in
"""

import sys, serial, argparse
import numpy as np
from time import sleep
from collections import deque

import matplotlib.pyplot as plt 
import matplotlib.animation as animation
import matplotlib.patches as mpatches

import random


class Object(object):
    pass
serial = Object()
class Serial(object):
    def __init__(self, port, baud):
        pass
    def readline(self):
        return " ".join([str(random.random()*1000) for i in range(3)])
serial.Serial = Serial        

# plot class
class AnalogPlot:
    def __init__(self, strPort, maxLen=100, n=1, baud=9600):
        # open serial port
        self.ser = serial.Serial(strPort, baud)
        self.data_deques = [deque([0.0]*maxLen) for i in range(n)] 
        self.maxLen = maxLen
        self.i = 0

    # add to buffer
    def addToBuf(self, buf, val):
        if len(buf) < self.maxLen:
            buf.append(val)
        else:
            '''
            buf[self.i] = val
            self.i = (self.i+1)%self.maxLen
            '''
            buf.popleft()
            buf.append(val)

    # add data
    def add(self, data):
        for i in range(len(self.data_deques)):
            self.addToBuf(self.data_deques[i], data[i])

    # update plot
    def update(self, frameNum, *axes):
        print axes
        try:
            line = self.ser.readline()
            data = [float(val) for val in line.split()]
            print(data)
            self.add(data)
            for i in range(len(axes)):
                axes[i][0].set_data(range(self.maxLen), self.data_deques[i])
        except KeyboardInterrupt:
            print('exiting')

        return axes, 

    # clean up
    def close(self):
        # close serial
        self.ser.flush()
        self.ser.close()    

# main() function
def main():
    # create parser
    parser = argparse.ArgumentParser(description="LDR serial")
    # add expected arguments
    parser.add_argument('--port', help="the full path of the arduino usb", dest='port', required=True, type=str)
    parser.add_argument('--n', help="how many data points are being transmitted from the arduino board", type=int, default=1)

    # parse args
    args = parser.parse_args()

    print('reading from serial port %s...' % args.port)

    # plot parameters
    analogPlot = AnalogPlot(args.port, n = args.n)

    print('plotting data...')

    # set up animation
    fig = plt.figure()
    ax = plt.axes(xlim=(0, 100), ylim=(0, 1023))
    plt.xlabel("time")
    plt.ylabel("reading")
    plt.title("arduino sensors")
    light_patch = mpatches.Patch(color='r', label='light')
    temp_patch = mpatches.Patch(color='b', label='temp')
    soil_patch = mpatches.Patch(color='g', label='soil')
    plt.legend(handles=[light_patch, temp_patch, soil_patch], loc="lower left")

    colors = ["r","b","g"]
    axes = [ax.plot([], [], colors[i]) for i in range(args.n)]
    anim = animation.FuncAnimation(fig, analogPlot.update, 
                                 fargs=axes, 
                                 interval=50)

    # show plot
    plt.show()

    # clean up
    analogPlot.close()

    print('exiting.')
  

# call main
if __name__ == '__main__':
    main()

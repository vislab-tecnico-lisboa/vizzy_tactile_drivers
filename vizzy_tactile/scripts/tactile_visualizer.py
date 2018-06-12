#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright (c) 2018 Institute for Systems and Robotics - Lisboa.
#
# 
# Authors:
#   * Joao Avelino



# ROS Stuff
import rospy
import rospkg
import message_filters
from vizzy_tactile.msg import TactSensor, TactSensorArray
from geometry_msgs.msg import WrenchStamped
import matplotlib.animation as animation
import matplotlib
import imp
try:
    imp.find_module('PyQt4')
    matplotlib.use('QT4Agg')
except:
    matplotlib.use('QT5Agg')

from matplotlib import pyplot as plt

# Scypy and numpy stuff
import numpy as np


class TactileListener:


    def __init__(self):

        rospy.init_node('tactile_viz')
        rospy.Subscriber("tactileForceField", TactSensorArray, self.listenerCallback)

        self.readings = np.array([0]*11)
        print("lol")

    def listenerCallback(self, vizzy_tactsensarray_msg):
        
        readx = []
        ready = []
        readz = []

        magnitude = []

        for x in vizzy_tactsensarray_msg.sensorArray:
            readx.append(x.force.x)
            ready.append(x.force.y)
            readz.append(x.force.z)
            v = np.array([x.force.x, x.force.y, x.force.z])

            magnitude.append(v)

        readx_np = np.array(readx)
        ready_np = np.array(ready)
        readz_np = np.array(readz)

        self.readings = magnitude



class ForcePlotter:
    def __init__(self):

        self.tactlist = TactileListener()

        sensor_numbers = np.array([x for x in xrange(1, 12)])
        readings = np.array([0]*11)
        self.fig, self.ax = plt.subplots()

        self.scat = self.ax.scatter(sensor_numbers, readings)

    def init(self):
        
        self.scat.set_array([])
        return self.scat,

    def animate(self, i):
        self.scat.set_array(self.tactlist.readings)
        return self.scat,


def main():

    plotter = ForcePlotter()

    interval = 1.0/50.0*1000.0

    ani = animation.FuncAnimation(plotter.fig, plotter.animate, frames=300, interval=interval, blit=True, init_func=plotter.init)

    plt.show()


if __name__ == '__main__':
    try:
        main()
    except rospy.ROSInterruptException:
        pass


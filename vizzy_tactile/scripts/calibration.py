#!/usr/bin/env python
# ROS Stuff
import rospy
import message_filters
from vizzy_tactile.msg import TactSensor, TactSensorArray
from geometry_msgs.msg import WrenchStamped

# Scypy stuff
import numpy as np

global numSensors
global calibratetList
global state

def callback(optoforce_msg, vizzy_tactsensarray_msg):

    global numSensors

    if numSensors < 0:
        numSensors = len(vizzy_tactsensarray_msg)
        print "---- Found %d sensors ----" % numSensors

        for x in vizzy_tactsensarray_msg:
            print "Found: %s" % x.frame_id


    #Very interesting stuff
    optox = optoforce_msg.wrench.force.x
    optoy = optoforce_msg.wrench.force.y
    optoz = optoforce_msg.wrench.force.z




    vizzy_x = vizzy_tactsensarray_msg[0].force.x
    vizzy_y = vizzy_tactsensarray_msg[0].force.y
    vizzy_z = vizzy_tactsensarray_msg[0].force.z



    print optox, optoy, optoz


rospy.init_node('tactile_calibrator')
numSensors = -1
state = "init"


print "--- Welcome to the tactile sensors calibrator ---"

opto_sub = message_filters.Subscriber('/optoforce_0', WrenchStamped)
vizzy_sub = message_filters.Subscriber('/tactileForceField', TactSensorArray)

ts = message_filters.TimeSynchronizer([opto_sub, vizzy_sub], 10)
ts.registerCallback(callback)
rospy.spin()
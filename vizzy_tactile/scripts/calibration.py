#!/usr/bin/env python
# ROS Stuff
import rospy
import message_filters
from vizzy_tactile.msg import TacVector, TactSensor, TactSensorArray, Tactile
from geometry_msgs.msg import WrenchStamped

# Scypy stuff
import numpy as np

def callback(optoforce_msg, vizzy_tactsensarray_msg):

    #Very interesting stuff
    optox = optoforce_msg.wrench.force.x
    optoy = optoforce_msg.wrench.force.y
    optoz = optoforce_msg.wrench.force.z


    vizzy_x = vizzy_tactsensarray_msg[0].force.x
    vizzy_y = vizzy_tactsensarray_msg[0].force.y
    vizzy_z = vizzy_tactsensarray_msg[0].force.z



    print optox, optoy, optoz


rospy.init_node('tactile_calibrator')

opto_sub = message_filters.Subscriber('/optoforce_0', WrenchStamped)
#vizzy_sub = message_filters.Subscriber('/tactileForceField', TactSensorArray)



ts = message_filters.TimeSynchronizer([opto_sub, vizzy_sub], 10)
ts.registerCallback(callback)
rospy.spin()
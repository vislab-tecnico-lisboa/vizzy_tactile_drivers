#!/usr/bin/env python
# -*- coding: utf-8 -*-

import rospy
import math
from vizzy_tactile.msg import TactSensor, TactSensorArray
from geometry_msgs.msg import WrenchStamped
from std_msgs.msg import Header
import numpy as np

#optoforce foce values are a function of vizzy sensors

def test():

    rospy.init_node('tactile_calibration_test')

    pubOptoForce = rospy.Publisher('/optoforce_0', WrenchStamped, queue_size=1)
    pubVizzySensor = rospy.Publisher('/calibDisplace', TactSensorArray, queue_size=1)
    
    rate = rospy.Rate(200)

    while not rospy.is_shutdown():
        
        
        vizzy_msgs_array = TactSensorArray()
        opto_msg = WrenchStamped()

        # optox: fit results: a = 1, b = 0.1
        # optoy: fit results: a = 0.1, b = 10
        # optoz: fit results: a = 0.001, b= 0.01, c = 100


        omega = 2*3.14*0.5
        t = rospy.get_time()
        x = math.cos(omega*t)
        z = abs(x)

        optox = x+0.1
        optoy = 0.1*x+10
        optoz = 0.001*z+0.01*math.pow(z, 2)+100

        opto_msg.wrench.force.x = optox
        opto_msg.wrench.force.y = optoy
        opto_msg.wrench.force.z = optoz


        for frameID in range(1, 17):
            fr = 'right_'+str(frameID)+'/tactile_right_0_'+str(frameID)
            
            vizzy_msg = TactSensor()
            vizzy_msg.displacement.x = x
            vizzy_msg.displacement.y = x
            vizzy_msg.displacement.z = z
            vizzy_msg.frame_id = fr
            vizzy_msgs_array.sensorArray.append(vizzy_msg)

        pubVizzySensor.publish(vizzy_msgs_array)
        pubOptoForce.publish(opto_msg)

        rate.sleep()


if __name__ == '__main__':
    try:
        test()
    except rospy.ROSInterruptException:
        pass

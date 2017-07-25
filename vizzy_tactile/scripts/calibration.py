#!/usr/bin/env python
# ROS Stuff
import rospy
import message_filters
from vizzy_tactile.msg import TactSensor, TactSensorArray
from geometry_msgs.msg import WrenchStamped

# Scypy stuff
import numpy as np


#TEMP
from std_msgs.msg import String

global calibratedList
global uncalibratedList
global numSensors
global state
global sensorToCalib
global fullList
global optox, optoy, optoz
global vizzy_x, vizzy_y, vizzy_z


def callback(optoforce_msg, vizzy_tactsensarray_msg):

    global numSensors
    global state
    global fullList
    global optox, optoy, optoz
    global vizzy_x, vizzy_y, vizzy_z

    if numSensors < 0:
        numSensors = len(vizzy_tactsensarray_msg.sensorArray)
        print "---- Found %d sensors ----" % numSensors

        fullList = vizzy_tactsensarray_msg.sensorArray

        for x in vizzy_tactsensarray_msg.sensorArray:
            print "Found: %s" % x.frame_id
            uncalibratedList.append(x)

        state = "chooseSensor"

    if state == "getdata":
        optox.extend(optoforce_msg.wrench.force.x)
        optoy.extend(optoforce_msg.wrench.force.y)
        optoz.extend(optoforce_msg.wrench.force.z)

        vizzy_x.extend(vizzy_tactsensarray_msg.sensorArray[sensorToCalib].force.x)
        vizzy_y.extend(vizzy_tactsensarray_msg.sensorArray[sensorToCalib].force.y)
        vizzy_z.extend(vizzy_tactsensarray_msg.sensorArray[sensorToCalib].force.z)

        print "getting data"


def printAllSensors():
    global fullList

    i = 0
    print "Full sensor list ( [Number on List]: [Sensor ID])"

    for x in fullList:
        print "[%d]: ", x


def printCalibrateSensors():
    for x in calibratedList:
        print "Calibrated sensors in this session"
        print x

def printUncalibratedSensors():
    for x in uncalibratedList:
        print "Uncalibrated sensors in this session"
        print x

def calib():
    global numSensors
    global state
    global sensorToCalib
    global calibratedList
    global uncalibratedList
    global optox, optoy, optoz
    global vizzy_x, vizzy_y, vizzy_z

    sensorToCalib = -1

    calibratedList = []
    uncalibratedList = []


    rospy.init_node('tactile_calibrator')
    numSensors = -1
    state = "init"

    print "--- Welcome to the tactile sensors calibrator ---"

    opto_sub = message_filters.Subscriber('/optoforce_0', WrenchStamped)
    vizzy_sub = message_filters.Subscriber('/calibDisplace', TactSensorArray)

    ts = message_filters.ApproximateTimeSynchronizer([opto_sub, vizzy_sub], 10, 0.01)

    print "Nice to meet you"

    ts.registerCallback(callback)

    rate = rospy.Rate(200)

    while not rospy.is_shutdown():

        if state == "chooseSensor":
            printAllSensors()
            printCalibrateSensors()
            printUncalibratedSensors()

            try:
                sensorToCalib=int(raw_input("Which sensor do you want to calibrate? (Insert the number of sensor on the full list): "))

                if sensorToCalib > len(fullList):
                    raise IndexError

            except ValueError:
                print "lol... that's not a number"

            except IndexError:
                print "The number is not on the list"

            finally:

                optox = []
                optoy = []
                optoz = []

                vizzy_x = []
                vizzy_y = []
                vizzy_z = []

                print "Getting data for sensor [%d]: " % sensorToCalib, fullList[sensorToCalib]
                print "When you think there is enough data press [enter]"
                state = "getdata"


        rate.sleep()

if __name__ == '__main__':
    try:
        calib()
    except rospy.ROSInterruptException:
        pass
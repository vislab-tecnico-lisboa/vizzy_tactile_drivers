#!/usr/bin/env python
# ROS Stuff
import rospy
import message_filters
from vizzy_tactile.msg import TactSensor, TactSensorArray
from geometry_msgs.msg import WrenchStamped
import matplotlib.pyplot as plt
import re

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
global resultsMat

#DEFINE
MAX_ID = 16

def callback(optoforce_msg, vizzy_tactsensarray_msg):

    global numSensors
    global state
    global fullList
    global optox, optoy, optoz
    global vizzy_x, vizzy_y, vizzy_z
    global resultsMat

    if numSensors < 0:
        numSensors = len(vizzy_tactsensarray_msg.sensorArray)

        resultsMat = [[0 for x in range(7)] for y in range(MAX_ID)]

        print " "
        print "---- Found %d sensors ----" % numSensors

        fullList = vizzy_tactsensarray_msg.sensorArray

        for x in vizzy_tactsensarray_msg.sensorArray:
            print "Found: %s" % x.frame_id
            uncalibratedList.append(x)

        state = "chooseSensor"

    if state == "getdata":
        optox.append(optoforce_msg.wrench.force.x)
        optoy.append(optoforce_msg.wrench.force.y)
        optoz.append(optoforce_msg.wrench.force.z)

        vizzy_x.append(vizzy_tactsensarray_msg.sensorArray[sensorToCalib].displacement.x)
        vizzy_y.append(vizzy_tactsensarray_msg.sensorArray[sensorToCalib].displacement.y)
        vizzy_z.append(abs(vizzy_tactsensarray_msg.sensorArray[sensorToCalib].displacement.z))


def printAllSensors():
    global fullList

    i = 0
    print " "
    print "**** Full sensor list ( [Number on List]: [Sensor frame ID]) ****"

    for x in fullList:
        print "[%d]: " % i, x.frame_id
        i = i+1


def printCalibrateSensors():
    print " "
    print " ---- Calibrated sensors in this session ----"
    for x in calibratedList:
        print x.frame_id

def printUncalibratedSensors():
    print " "
    print "---- Uncalibrated sensors in this session ----"
    for x in uncalibratedList:
        print x.frame_id

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

                if sensorToCalib > len(fullList)-1:
                    raise IndexError

            except ValueError:
                print "lol... that's not a number. Try again"
                continue

            except IndexError:
                print "The number is not on the list. Try again"
                continue


            optox = []
            optoy = []
            optoz = []

            vizzy_x = []
            vizzy_y = []
            vizzy_z = []

            print "Getting data for sensor [%d]: " % sensorToCalib, fullList[sensorToCalib].frame_id
            state = "getdata"
            text = raw_input("When you think there is enough data press [enter]")
            if text == "":
                state = "fit_data"
            else:
                print "dafuq are you doing?"

            if state == "fit_data":

                opto_x_arr = np.array(optox)
                opto_y_arr = np.array(optoy)
                opto_z_arr = np.array(optoz)

                vizzy_x_arr = np.array(vizzy_x)
                vizzy_y_arr = np.array(vizzy_y)
                vizzy_z_arr = np.array(vizzy_z)

                x_coefs = np.polyfit(vizzy_x_arr, opto_x_arr, 1)
                y_coefs = np.polyfit(vizzy_y_arr, opto_y_arr, 1)
                z_coefs = np.polyfit(vizzy_z_arr, opto_z_arr, 2)

                px = np.poly1d(x_coefs)
                py = np.poly1d(y_coefs)
                pz = np.poly1d(z_coefs)

                xp = np.linspace(-2, 2, 100)
                yp = np.linspace(-2, 2, 100)
                zp = np.linspace(0, 3, 100)

                f, (ax1, ax2, ax3) = plt.subplots(3)

                ax1.plot(vizzy_x_arr, opto_x_arr, '.', xp, px(xp), '-')
                ax2.plot(vizzy_y_arr, opto_y_arr, '.', yp, py(yp), '-')
                ax3.plot(vizzy_z_arr, opto_z_arr, '.', zp, pz(zp), '-')

                ax1.set_title("x")
                ax2.set_title("y")
                ax3.set_title("z")

                plt.show()

                cmd = raw_input("Is this calibration ok? [Y/n]")

                if cmd == "Y" or cmd == "y":
                    print "\n \n Very well. Let's move on..."
                    calibratedList.append(fullList[sensorToCalib])
                    uncalibratedList.remove(fullList[sensorToCalib])
                    state = "chooseSensor"
                    plt.close(f)

                    idx = int(re.search(r'\d+', fullList[sensorToCalib].frame_id).group())
                    print "idx: ", idx

                    resultsMat[idx-1][0] = x_coefs[0]
                    resultsMat[idx-1][1] = x_coefs[1]
                    resultsMat[idx-1][2] = y_coefs[0]
                    resultsMat[idx-1][3] = y_coefs[1]
                    resultsMat[idx-1][4] = z_coefs[0]
                    resultsMat[idx-1][5] = z_coefs[1]
                    resultsMat[idx-1][6] = z_coefs[2]

                    print resultsMat

                else:
                    raw_input("Ok, let's do it again. Press [enter] when ready to start")
                    plt.close(f)
                    optox = []
                    optoy = []
                    optoz = []

                    vizzy_x = []
                    vizzy_y = []
                    vizzy_z = []

                    print "Getting data for sensor [%d]: " % sensorToCalib, fullList[sensorToCalib].frame_id
                    state = "getdata"
                    text = raw_input("When you think there is enough data press [enter]")
                    if text == "":
                        state = "fit_data"
                    else:
                        print "dafuq are you doing? Press [enter] when there is enough data, don't write random stuff"

        rate.sleep()

    outfile = file("newCalibration.txt", 'w')

    np.savetxt(outfile, resultsMat, fmt='%-7.6f')

if __name__ == '__main__':
    try:
        calib()
    except rospy.ROSInterruptException:
        pass

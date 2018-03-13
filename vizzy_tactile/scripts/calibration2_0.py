#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright (c) 2018 Institute for Systems and Robotics - Lisboa.
#
# 
# Authors:
#   * Joao Avelino
#   * Tiago Paulino 


# ROS Stuff
import rospy
import rospkg
import message_filters
from vizzy_tactile.msg import TactSensor, TactSensorArray
from geometry_msgs.msg import WrenchStamped
import matplotlib
import imp
try:
    imp.find_module('PyQt4')
    matplotlib.use('QT4Agg')
except:
    matplotlib.use('QT5Agg')

from matplotlib import pyplot as plt
import re
import curses


# Scypy and numpy stuff
import numpy as np

# System calls to create folders and stuff
import os
import datetime

class Calibrator():
    def __init__(self, interface):

        #curses
        self.interface = interface

        #Initialize variables
        optoTopic = rospy.get_param('~opto_topic', '/optoforce_0')
        vizzyTactTopic = rospy.get_param('~vizzyTactTopic', '/calibDisplace')
        self.rate = float(rospy.get_param('~rate', '200.0'))
        self.MAX_ID = int(rospy.get_param('~max_sensor_number', '16'))

        self.numSensors = -1
        self.optox = []
        self.optoy = []
        self.optoz = []
        self.vizzy_x = []
        self.vizzy_y= []
        self.vizzy_z= []
        self.calibratedList = []
        self.uncalibratedList = []
        self.fullList = []
        self.resultsMat = []
        self.state = 'init'

        #Get package path
        rospack = rospkg.RosPack()
        packagePath = rospack.get_path('vizzy_tactile')

        calibPath = packagePath+'/calib'
        #if the calib folder doesnt exist create it
        if not os.path.isdir(calibPath):
            os.makedirs(calibPath)

        #create path for this calibration run
        rightnow = datetime.datetime.now()
        self.calibPath = calibPath+"/"+str(rightnow.year)+"_"+str(rightnow.month)+ \
        "_"+str(rightnow.day)+"_"+str(rightnow.hour)+"_"+str(rightnow.minute)+ \
        "_"+str(rightnow.second)

        if not os.path.isdir(self.calibPath):
            os.makedirs(self.calibPath)


        #Subscribers
        optoSub = message_filters.Subscriber(optoTopic, WrenchStamped)
        vizzyTactSub = message_filters.Subscriber(vizzyTactTopic, TactSensorArray)
        self.ts = message_filters.ApproximateTimeSynchronizer([optoSub, vizzyTactSub], 10, 0.01)
        self.ts.registerCallback(self.callback)

        self.sm = StateMachine(interface, self)
    

    
    def callback(self, optoforce_msg, vizzy_tactsensarray_msg):
        if self.numSensors < 0:
            self.numSensors = len(vizzy_tactsensarray_msg.sensorArray)

            self.resultsMat = [[0 for x in range(7)] for y in range(self.MAX_ID)]

            #print (" ")
            #print ("---- Found %d sensors ----" % self.numSensors)

            self.fullList = vizzy_tactsensarray_msg.sensorArray

            for x in vizzy_tactsensarray_msg.sensorArray:
                #print "Found: %s" % x.frame_id
                self.uncalibratedList.append(x)
        

        if self.sm._state == self.sm._GETTING_DATA:
            self.optox.append(optoforce_msg.wrench.force.x)
            self.optoy.append(optoforce_msg.wrench.force.y)
            self.optoz.append(optoforce_msg.wrench.force.z)

            self.vizzy_x.append(vizzy_tactsensarray_msg.sensorArray[self.sm.selectionFromList].displacement.x)
            self.vizzy_y.append(vizzy_tactsensarray_msg.sensorArray[self.sm.selectionFromList].displacement.y)
            self.vizzy_z.append(abs(vizzy_tactsensarray_msg.sensorArray[self.sm.selectionFromList].displacement.z))
        else:
            self.optox = []
            self.optoy = []
            self.optoz = []

            self.vizzy_x = []
            self.vizzy_y = []
            self.vizzy_z = []


    def fitdata(self):
        opto_x_arr = np.array(self.optox)
        opto_x_arr = np.array(self.optox)
        opto_y_arr = np.array(self.optoy)
        opto_z_arr = np.array(self.optoz)

        vizzy_x_arr = np.array(self.vizzy_x)
        vizzy_y_arr = np.array(self.vizzy_y)
        vizzy_z_arr = np.array(self.vizzy_z)

        self.x_coefs = np.polyfit(vizzy_x_arr, opto_x_arr, 1)
        self.y_coefs = np.polyfit(vizzy_y_arr, opto_y_arr, 1)
        self.z_coefs = np.polyfit(vizzy_z_arr, opto_z_arr, 2)

        px = np.poly1d(self.x_coefs)
        py = np.poly1d(self.y_coefs)
        pz = np.poly1d(self.z_coefs)

        xp = np.linspace(-3, 3, 100)
        yp = np.linspace(-3, 3, 100)
        zp = np.linspace(0, 4, 100)

        #print message to check the results
        self.interface.write_line(7, self.interface.CENTER, \
        '### Check the results. Close the graphic window when \n ready to proceed. ###')

        self.interface.beep()
        self.interface.refresh()

        f, (ax1, ax2, ax3) = plt.subplots(3)

        ax1.plot(vizzy_x_arr, opto_x_arr, '.', xp, px(xp), '-')
        ax2.plot(vizzy_y_arr, opto_y_arr, '.', yp, py(yp), '-')
        ax3.plot(vizzy_z_arr, opto_z_arr, '.', zp, pz(zp), '-')

        ax1.set_title("x")
        ax2.set_title("y")
        ax3.set_title("z")
        plt.show()

        self.interface.clear()
    

    def run(self):
        rate = rospy.Rate(self.rate)
        self.running = True
        while (self.running) and (not rospy.is_shutdown()):
            
            #Execute state actions
            self.sm.state_execution()

            if self.sm._state == self.sm._EXIT:
                self.running = False
            rate.sleep()


class StateMachine():
    _INIT = 0
    _CHOOSE_SENSOR = 1
    _PRE_CALIBRATION = 2
    _GETTING_DATA = 3
    _FITTING = 4
    _POST_CALIBRATION = 5
    _EXIT = 6

    

    def __init__(self, interface, calibrator):
        self._state = self._INIT
        self._calibrator = calibrator
        self.interface = interface
        self.savedStatus = ''

    def event_handler(self, event):
        if event == self._CHOOSE_SENSOR:
            self.interface.clear()
            self._state = self._CHOOSE_SENSOR
            self.selectionFromList = 0

        if event == self._PRE_CALIBRATION:
            self.interface.clear()
            self._state = self._PRE_CALIBRATION
        
        if event == self._GETTING_DATA:
            self.interface.clear()
            self._state = self._GETTING_DATA

        if event == self._POST_CALIBRATION:
            self.interface.clear()
            self._state = self._POST_CALIBRATION
            
            #print fitting data warning
            self.interface.write_line(7, self.interface.CENTER, '### Fitting data ###')
            self.interface.refresh()

            #fit data
            self._calibrator.fitdata()




    def state_execution(self):
        #init state
        if self._state == self._INIT:
            self.interface.write_line(5, self.interface.CENTER, '=========================================')
            self.interface.write_line(6, self.interface.CENTER, '||Welcome to Vizzy\'s tactile calibrator||')
            self.interface.write_line(7, self.interface.CENTER, '=========================================')

            self.interface.write_line(self.interface._num_lines-1, 0, 'Press Q to quit or C to calibrate', \
            self.interface.HIGHLIGH, True)

            c = self.interface.read_key()
            if c != None:
                if c == 113 or c == 181:
                    self._state = self._EXIT
                elif c == 99 or c == 67:
                    self.event_handler(self._CHOOSE_SENSOR)
        
        #CHOOSE_SENSOR - show the list of sensors and let the user choose the one to calibrate
        if self._state == self._CHOOSE_SENSOR:
            self.interface.write_line(1, self.interface.CENTER, '#### Select a sensor to calibrate ####', \
            self.interface.HIGHLIGH)

            idx = 0
            for x in self._calibrator.fullList:
                calibrated = ''
                
                for y in self._calibrator.calibratedList:
                    if y == x:
                        calibrated = ' (calibrated)'
                        break

                if self.selectionFromList == idx:
                    self.interface.write_line(idx+2, self.interface.CENTER, '---> '+x.frame_id + calibrated \
                    + ' <---', self.interface.SELECTED)
                else:
                    self.interface.write_line(idx+2, 0, ' ', 0, True)
                    self.interface.write_line(idx+2, self.interface.CENTER, x.frame_id + calibrated)
                idx = idx +1

            
            self.interface.write_line(self.interface._num_lines-2, 0, \
            self.savedStatus, self.interface.HIGHLIGH, False)

            self.interface.write_line(self.interface._num_lines-1, 0, \
            'Press: q - Quit | Enter - Select Sensor | Arrows: Up and Down', self.interface.HIGHLIGH, True)

            c = self.interface.read_key()
            if c != None:
                self.savedStatus = ''
                self.interface.clear()
                if c == 113 or c == 181:
                    self._state = self._EXIT
                elif c == 258:
                    if self.selectionFromList == len(self._calibrator.fullList)-1:
                        self.selectionFromList = 0
                    else:
                        self.selectionFromList += 1
                elif c == 259:
                    if self.selectionFromList == 0:
                        self.selectionFromList = len(self._calibrator.fullList)-1
                    else:
                        self.selectionFromList -= 1
                elif c == 10:
                    self.event_handler(self._PRE_CALIBRATION)

        ## PRE_CALIBRATION SCREEN - Ask the user 
        if self._state == self._PRE_CALIBRATION:
            self.interface.write_line(7, self.interface.CENTER, '### Are you ready to calibrate sensor ' \
             + self._calibrator.fullList[self.selectionFromList].frame_id + '? ###')
            
            self.interface.write_line(5, self.interface.CENTER, \
            "During the calibration process you need to press the Optoforce \n sensor against the desired sensor along x, y and z directions")
             
            self.interface.write_line(self.interface._num_lines-1, 0, \
            'Press: y - Yes | n - No (go to previous menu)', self.interface.HIGHLIGH, True)

            c = self.interface.read_key()
            if c != None:
                if c == 113 or c == 181:
                    self._state = self._EXIT
                elif c == 178 or c == 110:
                    self.event_handler(self._CHOOSE_SENSOR)
                elif c == 121 or c == 89:
                    self.event_handler(self._GETTING_DATA)
        
        ## GETTING_DATA - Get data to process
        if self._state == self._GETTING_DATA:
            self.interface.write_line(2, self.interface.CENTER, '### Getting data ### \n' \
             + 'Gathered %s points...' % len(self._calibrator.vizzy_x))

            if len(self._calibrator.vizzy_x)-1 > 0:
                self.interface.write_line(5, self.interface.CENTER, '### Vizzy sensor reading ### \n' \
                 + 'x: %s \n y: %s \n z: %s ' % (self._calibrator.vizzy_x[len(self._calibrator.vizzy_x)-1], self._calibrator.vizzy_y[len(self._calibrator.vizzy_y)-1], self._calibrator.vizzy_z[len(self._calibrator.vizzy_z)-1]))

              #  self.interface.write_line(9, self.interface.CENTER, '### Optoforce sensor reading ### \n' \
              #   + 'x: %s \n y: %s \n z: %s ' % (self._calibrator.optox[len(self._calibrator.optox)-1], self._calibrator.optoy[len(self._calibrator.optox)-1], self._calibrator.optoz[len(self._calibrator.optox)-1]))
            
            self.interface.write_line(self.interface._num_lines-1, 0, \
            'Press: Enter - Complete Calibration | c - Cancel', \
            self.interface.HIGHLIGH, True)
            
            c = self.interface.read_key()
            if c != None:
                if c == 113 or c == 181:
                    self._state = self._EXIT
                elif c == 10:
                    self.event_handler(self._POST_CALIBRATION)

                elif c == 67 or c == 99:
                    self.event_handler(self._CHOOSE_SENSOR)

        ## POST_CALIBRATION - Decide if we accept this calibration or not
        if self._state == self._POST_CALIBRATION:

            self.interface.write_line(7, self.interface.CENTER, '### Do you like the results? ###')
            self.interface.write_line(self.interface._num_lines-1, 0, \
            'Press: y - Yes, save results | n - No, go to sensor list menu', self.interface.HIGHLIGH, True)
            c = self.interface.read_key()
            if c != None:
                if c == 113 or c == 181:
                    self._state = self._EXIT
                elif c == 121 or c == 189:
                    self._calibrator.calibratedList.append(self._calibrator.fullList[self.selectionFromList])

                    idx = int(re.search(r'\d+', self._calibrator.fullList[self.selectionFromList].frame_id).group())
                    self._calibrator.resultsMat[idx-1][0] = self._calibrator.x_coefs[0]
                    self._calibrator.resultsMat[idx-1][1] = self._calibrator.x_coefs[1]
                    self._calibrator.resultsMat[idx-1][2] = self._calibrator.y_coefs[0]
                    self._calibrator.resultsMat[idx-1][3] = self._calibrator.y_coefs[1]
                    self._calibrator.resultsMat[idx-1][4] = self._calibrator.z_coefs[0]
                    self._calibrator.resultsMat[idx-1][5] = self._calibrator.z_coefs[1]
                    self._calibrator.resultsMat[idx-1][6] = self._calibrator.z_coefs[2]

                    outfile = file(self._calibrator.calibPath+'/'+self._calibrator.fullList[self.selectionFromList].frame_id[0]\
                    +'_hand_'+'fullFile.txt', 'w')
                    np.savetxt(outfile, self._calibrator.resultsMat, fmt='%-7.4f')
                    outfile.close()

                    fullPath = self._calibrator.calibPath+\
                    '/'+self._calibrator.fullList[self.selectionFromList].frame_id[0]+\
                    '_hand_'+'sensor_'+str(idx)+".txt"
                    
                    sensorResult = self._calibrator.resultsMat[idx-1]
                    outSensorFile = file(fullPath, 'w')
                    np.savetxt(outSensorFile, np.column_stack(sensorResult), fmt='%-7.6f')
                    outSensorFile.close()
                    self.savedStatus = "Saved: "+self._calibrator.fullList[self.selectionFromList].frame_id[0]+\
                    '_hand_'+'sensor_'+str(idx)+'.txt and '+ self._calibrator.fullList[self.selectionFromList].frame_id[0]\
                    +'_hand_'+'fullFile.txt'
                    self.event_handler(self._CHOOSE_SENSOR)

                elif c == 178 or c == 110:
                    self.event_handler(self._CHOOSE_SENSOR)
        
        self.interface.refresh()        


def main(stdscr):
    rospy.init_node('tactile_calibrator')
    app = Calibrator(Window(stdscr))
    app.run()


#Curses "window"
class Window():

    CENTER = -1
    HIGHLIGH = 1
    SELECTED = 2
    NOTSELECTED = 3
    
    _screen = None
    _window = None
    _num_lines = None

    def __init__(self, stdscr, lines=20):
        self._screen = stdscr
        self._screen.nodelay(True)
        curses.curs_set(0)

        self._num_lines = lines

    def read_key(self):
        keycode = self._screen.getch()
        return keycode if keycode != -1 else None
    
    def clear(self):
        self._screen.clear()


    def write_line(self, lineno, colno, message, opts = 0, full_line = False):
        if lineno < 0 or lineno >= self._num_lines:
            raise(ValueError, 'lineno out of bounds')

        height, width = self._screen.getmaxyx()
        y = (height / self._num_lines) * lineno

        x = None

        

        for text in message.split('\n'):

            if colno == self.CENTER:
                x = (width-len(text))/2
            else:
                x = colno

            if full_line == True:
                text = text.ljust(width)
            if opts == self.HIGHLIGH:
                self._screen.addstr(y, x, text, curses.A_STANDOUT)
            elif opts == self.SELECTED:
                self._screen.addstr(y, x, text, curses.A_UNDERLINE)
            elif opts == self.NOTSELECTED:
                self._screen.addstr(y, x, text, curses.A_DIM)
            else:
                self._screen.addstr(y, x, text)
            y += 1

    def refresh(self):
        self._screen.refresh()

    def beep(self):
        curses.flash()


if __name__ == '__main__':
    try:
        curses.wrapper(main)
    except rospy.ROSInterruptException:
        pass
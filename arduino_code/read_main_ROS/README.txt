Version of Arduino IDE 1.8.2 min needed!!!!

Main file to read from the mlx90393 sensors placed on Vizzy.

Choose any combination between the 16 sensors (in one hand),
by changing the SensorActive variable in the file. 

Ex: SensorActive[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; -> all sensors active
SensorActive[16] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; -> Only sensor nº 1 active

See "VizzyTactileSensors_Scheme.pdf" for the sensor numbers. 



-----------------

Tiago Paulino

April 2017
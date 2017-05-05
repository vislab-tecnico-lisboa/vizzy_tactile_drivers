#include "ros/ros.h"
#include "std_msgs/String.h"
#include "vizzy_tactile/TacVector.h"
#include "vizzy_tactile/Tactile.h"
#include "vizzy_tactile/TactSensorArray.h"
#include "vizzy_tactile/TactSensor.h"
#include <iostream>
#include <visualization_msgs/Marker.h>



ros::Publisher pub;
ros::Subscriber sub;
ros::Publisher marker_pub;

std::string hand;

void subscriberCallback(const vizzy_tactile::Tactile::ConstPtr& msg)
{


  vizzy_tactile::TactSensorArray outmsg;
  visualization_msgs::Marker marker;




  marker.header.stamp = ros::Time::now();

  stringstream aux;

  aux << "tactile_shapes_" << hand;
  marker.marker.ns = aux.str();



  //For each sensor
  int i=0;
  int x,y,z;                    // Received values
  float Bx,By,Bz;               // Magnetic Field [Oe]
  //float pos_x, pos_y, pos_z;    // Magnet Position Relative to the Sensor [mm]
  //float pos_x0, pos_y0, pos_z0; // Initial magnet positions [mm]
  //float dx, dy, dz;             // Magnet displacements [mm]
  //float Fx, Fy, Fz;             // Force [N]

  for(auto sensor: msg->sensorsArray)
  {

    std::stringstream ss;

    ss << "/tactile_" << hand << "_" << i;
    outmsg.sensorArray[i].frame_id = ss.str();


    //CODIGO PARA CALCULAR FORCA E CAMPO

   // ROS_ERROR_STREAM(sensor.x);
   // ROS_ERROR_STREAM(sensor.y);
   // ROS_ERROR_STREAM(sensor.z);

    Bx = sensor.x*0.161*0.01;
    By = sensor.y*0.161*0.01;
    Bz = sensor.z*0.294*0.01;



    //SUBSTITUIR ZERO PELOS VALORES REAIS
    outmsg.sensorArray[i].force.x = 0;
    outmsg.sensorArray[i].force.y = 0;
    outmsg.sensorArray[i].force.z = 0;


    outmsg.sensorArray[i].field.x = Bx;
    outmsg.sensorArray[i].field.y = By;
    outmsg.sensorArray[i].field.z = Bz;


    i++;


    //Temporary: marker visualization



  }

  pub.publish(outmsg);


}





int main(int argc, char **argv)
{
  ros::init(argc, argv, "tactileComputationalNode");
  ros::NodeHandle nh;
  sub = nh.subscribe("/tactile", 1000, subscriberCallback);
  pub = nh.advertise<vizzy_tactile::TactSensorArray>("tactileForceField", 1000);
  marker_pub = n.advertise<visualization_msgs::Marker>("tactileForceMarker", 1);

  hand = "right";

  ros::spin();

  return 0;
}

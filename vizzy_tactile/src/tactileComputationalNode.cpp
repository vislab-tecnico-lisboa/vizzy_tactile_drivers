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
  for(auto sensor: msg->sensorsArray)
  {

    std::stringstream ss;

    ss << "/tactile_" << hand << "_" << i;
    outmsg.sensorArray[i].frame_id = ss.str();


    //CODIGO PARA CALCULAR FORCA E CAMPO

   // ROS_ERROR_STREAM(sensor.x);
   // ROS_ERROR_STREAM(sensor.y);
   // ROS_ERROR_STREAM(sensor.z);




    //SUBSTITUIR ZERO PELOS VALORES REAIS
    outmsg.sensorArray[i].force.x = 0;
    outmsg.sensorArray[i].force.y = 0;
    outmsg.sensorArray[i].force.z = 0;


    outmsg.sensorArray[i].field.x = 0;
    outmsg.sensorArray[i].field.y = 0;
    outmsg.sensorArray[i].field.z = 0;


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

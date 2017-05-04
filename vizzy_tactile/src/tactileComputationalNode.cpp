#include "ros/ros.h"
#include "std_msgs/String.h"
#include "vizzy_tactile/TacVector.h"
#include "vizzy_tactile/Tactile.h"
#include "vizzy_tactile/TactSensorArray.h"
#include "vizzy_tactile/TactSensor.h"
#include <iostream>



ros::Publisher pub;
ros::Subscriber sub;

void subscriberCallback(const vizzy_tactile::Tactile::ConstPtr& msg)
{


  vizzy_tactile::TactSensorArray outmsg;

  //For each sensor
  int i=0;
  for(auto sensor: msg->sensorsArray)
  {



    //CODIGO PARA CALCULAR FORCA E CAMPO

    ROS_ERROR_STREAM(sensor.x);
    ROS_ERROR_STREAM(sensor.y);
    ROS_ERROR_STREAM(sensor.z);




    std::stringstream ss;
    ss << i;
    outmsg.sensorArray[i].frame_id = ss.str();

    outmsg.sensorArray[i].force.x = 0;
    outmsg.sensorArray[i].force.y = 0;
    outmsg.sensorArray[i].force.z = 0;


    outmsg.sensorArray[i].field.x = 0;
    outmsg.sensorArray[i].field.y = 0;
    outmsg.sensorArray[i].field.z = 0;

    i++;
  }


}





int main(int argc, char **argv)
{
  ros::init(argc, argv, "tactileComputationalNode");
  ros::NodeHandle nh;
  sub = nh.subscribe("/tactile", 1000, subscriberCallback);
  pub = nh.advertise<vizzy_tactile::TactSensorArray>("tactileForceField", 1000);

  ros::spin();

  return 0;
}

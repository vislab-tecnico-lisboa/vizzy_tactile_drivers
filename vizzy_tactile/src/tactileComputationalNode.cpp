#include "ros/ros.h"
#include "std_msgs/String.h"
#include "vizzy_tactile/TacVector.h"
#include "vizzy_tactile/Tactile.h"
#include "vizzy_tactile/TactSensorArray.h"
#include "vizzy_tactile/TactSensor.h"
#include <iostream>
#include <visualization_msgs/Marker.h>
#include <tf/tf.h>



ros::Publisher pub;
ros::Subscriber sub;
ros::Publisher marker_pub;

std::string hand;

void subscriberCallback(const vizzy_tactile::Tactile::ConstPtr& msg)
{


  vizzy_tactile::TactSensorArray outmsg;
  visualization_msgs::Marker marker;


  //Auxiliary to convert to quaternion
  tf::Vector3 up_vector(0.0, 0.0, 1.0);


  marker.header.stamp = ros::Time::now();

  std::stringstream aux;

  aux << "tactile_shapes_" << hand;
  marker.ns = aux.str();


  marker.type = visualization_msgs::Marker::ARROW;

  //For each sensor
  int i=0;
  //int x,y,z;                    // Received values
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

    //Temporary: force marker visualization

    marker.id = i;
    marker.header.frame_id = ss.str();

    marker.action = visualization_msgs::Marker::ADD;


    tf::Vector3 axis_vector(outmsg.sensorArray[i].force.x, outmsg.sensorArray[i].force.y , outmsg.sensorArray[i].force.z);
    tf::Quaternion q;

    if(axis_vector.dot(up_vector)>0.99)
    {
      q=tf::createIdentityQuaternion();
    }
    else
    {
      tf::Vector3 right_vector = axis_vector.cross(up_vector);
      right_vector.normalized();

      q=tf::Quaternion(right_vector, -1.0*acos(axis_vector.dot(up_vector)));
    }

    q.normalize();

    geometry_msgs::Quaternion force_orientation;
    tf::quaternionTFToMsg(q, force_orientation);

    marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.pose.orientation = force_orientation;


    marker.scale.x = 1.0; //Grossura da seta
    marker.scale.y = 1.0; //Isto é a grossura da seta...


    marker.scale.z = 1.0; //Vector magnitude

    marker.pose.orientation.w = 1.0;

    i++;

  }

  pub.publish(outmsg);


}





int main(int argc, char **argv)
{
  ros::init(argc, argv, "tactileComputationalNode");
  ros::NodeHandle nh;
  ros::NodeHandle nPriv("~");

  sub = nh.subscribe("/tactile", 1000, subscriberCallback);
  pub = nh.advertise<vizzy_tactile::TactSensorArray>("tactileForceField", 1000);
  marker_pub = nh.advertise<visualization_msgs::Marker>("tactileForceMarker", 1);

  nPriv.param<std::string>("hand", hand, "right");

  ros::spin();

  return 0;
}

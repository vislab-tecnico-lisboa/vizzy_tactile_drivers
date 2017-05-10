
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
  float pos_x, pos_y, pos_z;    // Magnet Position Relative to the Sensor [mm]
  float pos_x0, pos_y0, pos_z0; // Initial magnet positions [mm]
  float dx, dy, dz;             // Magnet displacements [mm]
  float Fx, Fy, Fz;             // Force [N]
  pos_x0=0; pos_y0=0; pos_z0=4;

  for(auto sensor: msg->sensorsArray)
  {

    std::stringstream ss;

    ss << hand << "_" << i+1 << "/tactile_" << hand << "_0_" << i+1;
    outmsg.sensorArray[i].frame_id = ss.str();


    //CODIGO PARA CALCULAR FORCA E CAMPO

    //Convert to Fields
    Bx = sensor.x*0.161*0.01;
    By = sensor.y*0.161*0.01;
    Bz = sensor.z*0.294*0.01;

    //Convert to Displacements
    pos_x=Bx*0.25;
    pos_y=By*0.25;
    pos_z=-Bz*0.02+4;

    dx = pos_x - pos_x0;
    dy = pos_y - pos_y0;
    dz = pos_z - pos_z0;

    //Convert to Force
    Fx=dx*(3+0.7*dz);
    Fy=dy*(3+0.7*dz);
    Fz=(2.231*dz*dz+3.111*abs(dz))*(1-dy*dy*0.1)*(1-dx*dx*0.1);


    //SUBSTITUIR ZERO PELOS VALORES REAIS
    outmsg.sensorArray[i].force.x = Fx;
    outmsg.sensorArray[i].force.y = Fy;
    outmsg.sensorArray[i].force.z = Fz;


    outmsg.sensorArray[i].field.x = Bx;
    outmsg.sensorArray[i].field.y = By;
    outmsg.sensorArray[i].field.z = Bz;

    //Temporary: force marker visualization

    marker.id = i;
    marker.header.frame_id = ss.str();

    marker.action = visualization_msgs::Marker::ADD;


    tf::Vector3 axis_vector(outmsg.sensorArray[i].force.x, outmsg.sensorArray[i].force.y , outmsg.sensorArray[i].force.z);

    ROS_ERROR_STREAM("AXIS_VECTOR: " << "x: " << axis_vector.getX() << ", y= " << axis_vector.getX() << ", z= " <<  axis_vector.getZ());



    axis_vector.normalize();

    ROS_ERROR_STREAM("AXIS_VECTOR_NORM: " << "x: " << axis_vector.getX() << ", y= " << axis_vector.getX() << ", z= " <<  axis_vector.getZ());

    tf::Quaternion q;

    if(axis_vector.dot(up_vector)>0.999999999999)
    {
      q=tf::createIdentityQuaternion();
    }
    else
    {
      tf::Vector3 right_vector = axis_vector.cross(up_vector);
      right_vector.normalized();

      q=tf::Quaternion(right_vector, -1.0*acos(axis_vector.dot(up_vector)));
      ROS_ERROR_STREAM("Todo la dentro: " << q.getAxis());
    }

    q.normalize();
    ROS_ERROR_STREAM( "lol q:" << q);

    geometry_msgs::Quaternion force_orientation;
    tf::quaternionTFToMsg(q, force_orientation);

    marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.pose.orientation = force_orientation;

    marker.color.a = 1.0; // Don't forget to set the alpha!
    marker.color.r = 0.0;
    marker.color.g = 1.0;
    marker.color.b = 0.0;

    ROS_ERROR_STREAM( "lol nan" << force_orientation);


    marker.scale.x = 1.0; //Grossura da seta
    marker.scale.y = 1.0; //Isto é a grossura da seta...

    //Vector magnitude
    marker.scale.z = sqrt(outmsg.sensorArray[i].force.x*outmsg.sensorArray[i].force.x+outmsg.sensorArray[i].force.y*outmsg.sensorArray[i].force.y+outmsg.sensorArray[i].force.z*outmsg.sensorArray[i].force.z);

    marker_pub.publish(marker);

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

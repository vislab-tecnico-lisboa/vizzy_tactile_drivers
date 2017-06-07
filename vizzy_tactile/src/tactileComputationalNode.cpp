#include "ros/ros.h"
#include "std_msgs/String.h"
#include "vizzy_tactile/TacVector.h"
#include "vizzy_tactile/Tactile.h"
#include "vizzy_tactile/TactSensorArray.h"
#include "vizzy_tactile/TactSensor.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <visualization_msgs/Marker.h>
#include <tf/tf.h>
#include <ros/package.h>
#include "vizzy_tactile/SetNumSensors.h"
#include <vector>

#include <stdlib.h>

ros::Publisher pub;
ros::Subscriber sub;
ros::Publisher marker_pub;

std::string hand;

int countMeasures;



double Bxx[121][121][81]; //BvsD files
double Byy[121][121][81];
double Bzz[121][121][81];
double c[8][16]; //Mudar isto

int offset_z=2;



class Sensor{

public:
  int id;
  float pos_x0 = 0;
  float pos_y0 = 0;
  float pos_z0 = 0;

  float Fx, Fy, Fz;             // Force [N]

  int countMeasures = 0;


  Sensor(int id) : id(id)
  {

  }

  bool computeForce(double x, double y, double z)
  {

    float Bx,By,Bz;               // Magnetic Field [Oe]
    float pos_x, pos_y, pos_z;    // Magnet Position Relative to the Sensor [mm]

    float dx, dy, dz;             // Magnet displacements [mm]

    double errorB_temp, errorB=21.5;
    int k_2,j_2,i_2;
    int k,j,i;
    int le_x = 0, le_y = 0, le_z = 0;         //indice positions

    //Convert to Fields
    Bx = x*0.161*0.01;
    By = y*0.161*0.01;
    Bz = z*0.294*0.01;

    //Convert to Displacements

    // Conditions to use??
    int i_min=0, i_max=121;
    int j_min=0, j_max=121;
    int k_min=0, k_max=81;

    if(Bz>13.5)
      k_max=50;

    if(Bx>1)
      i_max=62;
    else if(Bx<-1)
      i_min=44;

    if(By>1)
      j_min=54;
    else if(By<-1)
      j_max=87;

    i_2=0;j_2=0;k_2=0;
    for(i=i_min;i<i_max;i=i+3){
      for(k=k_min;k<k_max;k=k+3){
        for(j=j_min;j<j_max;j=j+3){
          errorB_temp=pow(Bx-Bxx[i][j][k],2)+pow(By-Byy[i][j][k],2)+pow(Bz-Bzz[i][j][k],2);
          if(errorB_temp<errorB){
            errorB=errorB_temp;
            i_2=i;j_2=j;k_2=k;
          }
        }
      }
    }
    errorB = 20.5;
    int fx=5,fy=5,fz=5;
    if(i_2<5){fx=i_2;}
    if(i_2>115){fx=(i_2-115)+5;}
    if(j_2<5){fy=j_2;}
    if(j_2>115){fy=(j_2-115)+5;}
    if(k_2<5){fz=k_2;}
    if(k_2>75){fz=(k_2-75)+5;}

    for(i=0;i<11;i++){
      for(k=0;k<11;k++){
        for(j=0;j<11;j++){
          errorB_temp = pow(Bx-Bxx[i_2+i-fx][j_2+j-fy][k_2+k-fz],2)
              + pow(By-Byy[i_2+i-fx][j_2+j-fy][k_2+k-fz],2)
              + pow(Bz-Bzz[i_2+i-fx][j_2+j-fy][k_2+k-fz],2);

          if(errorB_temp<errorB){
            errorB=errorB_temp;
            le_x=i_2+i-fx; le_y=j_2+j-fy; le_z=k_2+k-fz;
          }
        }
      }
    }
    pos_x = (double)le_x*0.05-3; pos_y = (float)le_y*0.05-3; pos_z = (float)le_z*0.05;


    // Last step to position
    double factorx, factory, factorz;
    // -- X
    if (fabs(Bxx[le_x+1][le_y][le_z]-Bx)< fabs(Bxx[le_x-1][le_y][le_z]-Bx)){
      factorx = fabs(Bx-Bxx[le_x][le_y][le_z])/fabs(Bxx[le_x+1][le_y][le_z]-Bxx[le_x][le_y][le_z]);
      pos_x = pos_x + factorx*0.05;
    }
    else{
      factorx = fabs(Bx-Bxx[le_x][le_y][le_z])/fabs(Bxx[le_x-1][le_y][le_z]-Bxx[le_x][le_y][le_z]);
      pos_x = pos_x - factorx*0.05;
    }
    // -- Y
    if (fabs(Byy[le_x][le_y+1][le_z]-By)< fabs(Byy[le_x][le_y-1][le_z]-By)){
      factory = fabs(By-Byy[le_x][le_y][le_z])/fabs(Byy[le_x][le_y+1][le_z]-Byy[le_x][le_y][le_z]);
      pos_y = pos_y + factory*0.05;
    }
    else{
      factory = fabs(By-Byy[le_x][le_y][le_z])/fabs(Byy[le_x][le_y-1][le_z]-Byy[le_x][le_y][le_z]);
      pos_y = pos_y - factory*0.05;
    }
    // -- Z
    if (fabs(Bzz[le_x][le_y][le_z+1]-Bz)< fabs(Bzz[le_x][le_y][le_z-1]-Bz)){
      factorz = fabs(Bz-Bzz[le_x][le_y][le_z])/fabs(Bzz[le_x][le_y][le_z+1]-Bzz[le_x][le_y][le_z]);
      pos_z = pos_z + factorz*0.05 + offset_z;
    }
    else{
      factorz = fabs(Bz-Bzz[le_x][le_y][le_z])/fabs(Bzz[le_x][le_y][le_z-1]-Bzz[le_x][le_y][le_z]);
      pos_z = pos_z - factorz*0.05 + offset_z;
    }



    if(countMeasures <= 1)
    {
      ROS_ERROR_STREAM("FIRST MEASURE: " << id);
      countMeasures++;
      return false;
    }
    if(countMeasures < 11 && countMeasures > 1)
    {
      ROS_ERROR_STREAM("MORE THAN FIRST MEASURE: " << id);
      pos_x0 += pos_x;
      pos_y0 += pos_y;
      pos_z0 += pos_z;
      countMeasures++;
      return false;
    }else if(countMeasures == 11)
    {
      ROS_ERROR_STREAM("LAST MEASURE: " << id);
      pos_x0 /= 9;
      pos_y0 /= 9;
      pos_z0 /= 9;
      countMeasures++;
    }

    ROS_ERROR_STREAM("GOING TO RETURN TRUE: " << id);

    dx = pos_x - pos_x0;
    dy = pos_y - pos_y0;
    dz = pos_z - pos_z0;

    //Convert to Force - different for each sensor.

    Fx=dx*(c[0][id]+c[1][id]*dz);
    Fy=dy*(c[2][id]+c[3][id]*dz);
    Fz=(c[4][id]*dz*dz+c[5][id]*abs(dz))*(1-dy*dy*c[6][id])*(1-dx*dx*c[7][id]);

    return true;
  }



};


std::vector<Sensor> sensorList;


std::stringstream basepath;


void ReadCalibFiles(){



  std::stringstream ss;
  ss << basepath.str() << "/calib_files/vqx05.txt";

  int i=0, k=0, j=0;
  float num=2.1;
  FILE *fpx = fopen(ss.str().c_str(), "r");
  if (fpx == NULL) //checks for the file
  { //printf("\n Can’t open %s\n","vqx05.txt");
    // exit;
  }
  for(i=0;i<121;i++){
    for(k=0;k<81;k++){
      for(j=0;j<121;j++){
        if (fscanf(fpx, "%f", &num) != 1)
          exit(-1);
        Bxx[i][j][k] = num;
      }
    }
  }
  fclose(fpx);
  // -- y
  i=0; k=0; j=0;

  std::stringstream ssy;
  ssy << basepath.str() << "/calib_files/vqy05.txt";

  FILE *fpy = fopen(ssy.str().c_str(), "r");
  if (fpy == NULL) //checks for the file
  {
    // exit;
  }
  for(i=0;i<121;i++){
    for(k=0;k<81;k++){
      for(j=0;j<121;j++){
        if(fscanf(fpy, "%f", &num) != 1)
          exit(-1);
        Byy[i][j][k] = num;
      }
    }
  }
  fclose(fpy);
  //-- z
  i=0; k=0; j=0;
  std::stringstream ssz;
  ssz << basepath.str() << "/calib_files/vqz05.txt";
  FILE *fpz = fopen(ssz.str().c_str(), "r");
  if (fpz == NULL) //checks for the file
  { //printf("\n Can’t open %s\n","vqz05.txt");
    //  exit;
  }
  for(i=0;i<121;i++){
    for(k=0;k<81;k++){
      for(j=0;j<121;j++){
        if(fscanf(fpz, "%f", &num) != 1)
          exit(-1);
        Bzz[i][j][k] = num;
      }
    }
  }
  fclose(fpz);
  // -- force
  std::stringstream ssc;
  ssc << basepath.str() << "/calib_files/cc.txt";
  FILE *fpc = fopen(ssc.str().c_str(), "r");
  if (fpc == NULL) //checks for the file
  {
    // exit;
  }
  for(i=0;i<8;i++){
    for(j=0;j<16;j++){
      if(fscanf(fpc, "%f", &num) != 1)
        exit(-1);
      c[i][j] = num;
    }
  }
  fclose(fpc);
}


void subscriberCallback(const vizzy_tactile::Tactile::ConstPtr& msg)
{

  vizzy_tactile::TactSensorArray outmsg;

  std::stringstream aux;

  aux << "tactile_shapes_" << hand;



  for(auto sensor: msg->sensorsArray)
  {

    double Fx, Fy, Fz;

    //Check if we have that sensor id in the sensorList, if not create it

    bool exists = false;
    bool preCalibrationMade = false;


    for(auto sensItem : sensorList)
    {
      if(sensItem.id == sensor.id)
      {

        preCalibrationMade = sensItem.computeForce(sensor.x, sensor.y, sensor.z);
        Fx = sensItem.Fx;
        Fy = sensItem.Fy;
        Fz = sensItem.Fz;

        ROS_ERROR_STREAM("ENCONTREI SENSOR NA LISTA: " << sensor.id);

        exists = true;
        break;
      }
    }

    if (!exists)
    {
      Sensor novoSensor(sensor.id);
      preCalibrationMade = novoSensor.computeForce(sensor.x, sensor.y, sensor.z);

      ROS_ERROR_STREAM("NOVO SENSOR: " << sensor.id);

      Fx = novoSensor.Fx;
      Fy = novoSensor.Fy;
      Fz = novoSensor.Fz;
      sensorList.push_back(novoSensor);
    }




    if(!preCalibrationMade)
      continue;


    visualization_msgs::Marker marker;
    marker.ns = aux.str();
    marker.header.stamp = ros::Time::now();

    marker.type = visualization_msgs::Marker::ARROW;

    std::stringstream ss;

    ss << hand << "_" << sensor.id << "/tactile_" << hand << "_0_" << sensor.id;


    vizzy_tactile::TactSensor sensorMSG;



    sensorMSG.frame_id = ss.str();
    sensorMSG.force.x = Fx;
    sensorMSG.force.y = Fy;
    sensorMSG.force.z = Fz;

    ROS_ERROR_STREAM("frame_id: " << ss.str());

    outmsg.sensorArray.push_back(sensorMSG);
    //outmsg.sensorArray[i].frame_id = ss.str();


    //-----------------------CODIGO PARA CALCULAR DISPLACEMENT E FORCA O.O  ----------------------



    //SUBSTITUIR ZERO PELOS VALORES REAIS
    //outmsg.sensorArray[i].force.x = Fx;
    //outmsg.sensorArray[i].force.y = Fy;
    //outmsg.sensorArray[i].force.z = Fz;



    //Temporary: force marker visualization

    marker.id = sensor.id;
    marker.header.frame_id = ss.str();

    marker.action = visualization_msgs::Marker::ADD;

    geometry_msgs::Point p;
    p.x = 0;
    p.y = 0;
    p.z = 0;
    marker.points.push_back(p);

    p.x = Fx*0.1;
    p.y = Fy*0.1;
    p.z = Fz*0.1;

    marker.points.push_back(p);

    marker.color.a = 1.0; // Don't forget to set the alpha!
    marker.color.r = 1.0;
    marker.color.g = 0.0;
    marker.color.b = 0.0;

    marker.scale.x = 0.005; //Grossura da seta
    marker.scale.y = 0.01; //Isto é a grossura da seta...
    //marker.scale.z = 0;
    //Vector magnitude

    //marker.scale.z = sqrt(outmsg.sensorArray[i].force.x*outmsg.sensorArray[i].force.x+outmsg.sensorArray[i].force.y*outmsg.sensorArray[i].force.y+outmsg.sensorArray[i].force.z*outmsg.sensorArray[i].force.z);

    marker_pub.publish(marker);
  }


    pub.publish(outmsg);
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "tactileComputationalNode");
  ros::NodeHandle nh;
  ros::NodeHandle nPriv("~");

  basepath << ros::package::getPath("vizzy_tactile");

  //ros::ServiceServer service = n.advertiseService("setNumberOfSensors", add);

  sub = nh.subscribe("/tactile", 1000, subscriberCallback);
  pub = nh.advertise<vizzy_tactile::TactSensorArray>("tactileForceField", 1000);
  marker_pub = nh.advertise<visualization_msgs::Marker>("tactileForceMarker", 1000);

  ReadCalibFiles();

  nPriv.param<std::string>("hand", hand, "right");


  ros::spin();

  return 0;
}

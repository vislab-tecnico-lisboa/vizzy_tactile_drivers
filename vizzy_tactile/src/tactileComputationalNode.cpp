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
ros::Publisher pubCalibration;
ros::Subscriber sub;
ros::Publisher marker_pub;

std::string hand;
bool calib;

double Bxx[121][121][81]; //BvsD files
double Byy[121][121][81];
double Bzz[121][121][81];
double c[16][8]; //Mudar isto

int offset_z=2;



class Sensor{

public:
  int id;
  float pos_x0;
  float pos_y0;
  float pos_z0;

  float dx, dy, dz;    // Position [mm] // Magnet displacements [mm]

  float Fx, Fy, Fz;             // Force [N]

  int countMeasures;


  Sensor(int id) : id(id), pos_x0(0), pos_y0(0), pos_z0(0), countMeasures(0)
  {

  }

  bool computeForce(double x, double y, double z)
  {

    float Bx,By,Bz;               // Magnetic Field [Oe]
    float pos_x, pos_y, pos_z;    // Magnet Position Relative to the Sensor [mm]        

    double errorB_temp, errorB=21.5;
    int k_2,j_2,i_2;
    int k,j,i;
    int le_x = 0, le_y = 0, le_z = 0;         //indice positions

    //Convert to Fields
    Bx = x*0.161*0.01;
    By = y*0.161*0.01;
    Bz = fabs(z*0.294*0.01);


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
    if(le_x<=0) le_x=1;
    if(le_x>=120) le_x=120-1;
    if(le_y<=0) le_y=1;
    if(le_y>=120) le_y=120-1;
    if(le_z<=0) le_z=1;
    if(le_z>=80) le_z=80-1;
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


    if(countMeasures < 2)
    {
      countMeasures++;
      return false;
    }
    if(countMeasures < 11 && countMeasures > 1)
    {
      pos_x0 += pos_x;
      pos_y0 += pos_y;
      pos_z0 += pos_z;
      countMeasures++;
      return false;
    }else if(countMeasures == 11)
    {
      pos_x0 /= 9;
      pos_y0 /= 9;
      pos_z0 /= 9;
      countMeasures++;
    }

    dx = pos_x - pos_x0;
    dy = pos_y - pos_y0;
    dz = pos_z - pos_z0;

    //Convert to Force - different for each sensor.

    Fx=dx*c[id-1][0]+c[id-1][1]*dz;
    Fy=dy*c[id-1][2]+c[id-1][3]*dz;
    Fz=(c[id-1][4]*dz*dz+c[id-1][5]*fabs(dz))*(1-dy*dy*c[id-1][6])*(1-dx*dx*c[id-1][7]);

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
  for(i=0;i<16;i++){
    for(j=0;j<8;j++){
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
  vizzy_tactile::TactSensorArray calibmsg;

  std::stringstream aux;

  aux << "tactile_shapes_" << hand;



  for(auto &sensor: msg->sensorsArray)
  {

    double Fx, Fy, Fz;
    double dx, dy, dz;

    //Check if we have that sensor id in the sensorList, if not create it

    bool exists = false;
    bool preCalibrationMade = false;


    for(auto &sensItem : sensorList)
    {
      if(sensItem.id == sensor.id)
      {

        preCalibrationMade = sensItem.computeForce(sensor.x, sensor.y, sensor.z);
        Fx = sensItem.Fx;
        Fy = sensItem.Fy;
        Fz = sensItem.Fz;

        dx = sensItem.dx;
        dy = sensItem.dy;
        dz = sensItem.dz;

        exists = true;
        break;
      }
    }

    if (!exists && sensor.z != -1)
    {
      Sensor novoSensor(sensor.id);
      preCalibrationMade = novoSensor.computeForce(sensor.x, sensor.y, sensor.z);

      Fx = novoSensor.Fx;
      Fy = novoSensor.Fy;
      Fz = novoSensor.Fz;

      dx = novoSensor.dx;
      dy = novoSensor.dy;
      dz = novoSensor.dz;
      sensorList.push_back(novoSensor);
    }




    if(!preCalibrationMade)
      continue;


    visualization_msgs::Marker marker;
    marker.ns = aux.str();
    marker.header.stamp = ros::Time::now();

    if(calib)
      calibmsg.header.stamp = marker.header.stamp;
    else
      outmsg.header.stamp = marker.header.stamp;

    marker.type = visualization_msgs::Marker::ARROW;

    std::stringstream ss;

    ss << hand << "_" << sensor.id << "/tactile_" << hand << "_0_" << sensor.id;


    vizzy_tactile::TactSensor sensorMSG;

    if(calib)
    {
      sensorMSG.frame_id = ss.str();
      sensorMSG.force.x = -1;
      sensorMSG.force.y = -1;
      sensorMSG.force.z = -1;
      sensorMSG.displacement.x = dx;
      sensorMSG.displacement.y = dy;
      sensorMSG.displacement.z = dz;

      calibmsg.sensorArray.push_back(sensorMSG);
    }else
    {
      sensorMSG.frame_id = ss.str();
      sensorMSG.force.x = Fx;
      sensorMSG.force.y = Fy;
      sensorMSG.force.z = Fz;
      outmsg.sensorArray.push_back(sensorMSG);
    }



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
    if(!calib)
      marker_pub.publish(marker);
  }

    if(calib)
      pubCalibration.publish(calibmsg);
    else
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

  marker_pub = nh.advertise<visualization_msgs::Marker>("tactileForceMarker", 1000);

  ROS_INFO_STREAM("Going to read files");
  ReadCalibFiles();
  ROS_INFO_STREAM("Files read");

  nPriv.param<std::string>("hand", hand, "right");
  nPriv.param<bool>("calib", calib, false);

  if(calib)
    pubCalibration = nh.advertise<vizzy_tactile::TactSensorArray>("calibDisplace", 1000);
  else
    pub = nh.advertise<vizzy_tactile::TactSensorArray>("tactileForceField", 1000);



  ros::spin();

  return 0;
}

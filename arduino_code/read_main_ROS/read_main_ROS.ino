#include <Wire.h>
#include "MLX90393.h"
#define TCAADDR 0x70  //Address of the I2C multiplexer
#include <ros.h>
#include  <vizzy_tactile/Tactile.h>
#include  <vizzy_tactile/TacVector.h>
//#include  <vizzy_tactile/SetNumSensors.h>

//int SensorActive[16] = {0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0}; //Sensors to read - CHANGE HERE
//int SensorActive[16] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int SensorActive[16] = {0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0};  // INDEX FINGER
//int SensorActive[16] = {0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0}; //  MID FINGER
//int SensorActive[16] = {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0}; // Only Sensor nº 3
//int SensorActive[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; // All 16
//int SensorActive[16];

ros::NodeHandle_<ArduinoHardware,2,2,80,200>  nh;

vizzy_tactile::Tactile message;
vizzy_tactile::TacVector *mess;
//vizzy_tactile::TacVector mess[1];

ros::Publisher chatter("/tactile", &message);


// Global Variables
struct MLX90393 mlx[16]; // define a variable for each mlx90393 chip. 
int i=0,j=0, le=0;
int nDevices;
unsigned long previousMillis = 0;

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

void ActiveSensors(){ // Check what sensors are connected (without spam)
  nDevices=0;
  byte error, address;
  for (int i=0; i<32; i++){
    SensorActive[i]=0;
  }
  for(int i =0; i<8; i++){
    tcaselect(i);   
    for(address = 12; address < 16; address++ )  {  
      Wire.beginTransmission(address);  // 0xC-0xF = 12 - 15
      error = Wire.endTransmission();   
      if (error == 0){
        SensorActive[i*4+(address-12)]=1;
        //Serial.println(i*4+(address-12));
        nDevices++;
      }
      else if (error==4){
        // Serial.print("Unknow error at address 0x");
      }    
    }  
  }
}

//ros::ServiceClient client = n.serviceClient<vizzy_tactile::SetNumSensors>("NumSensors");

 
void setup() {
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(chatter);

  
  Wire.begin();               // join i2c bus
  Wire.setClock(400000);     //Wire.setClock() must be called after Wire.begin()
                              // Cant use this with Arduino Leonardo...
  //Serial.begin(115200);

  for(j=0;j<4;j++){
    tcaselect(j);
    
    for(i=0;i<4;i++){
      mlx[i+4*j]= MLX_DEFAULT2;        // Set default values
      mlx[i+4*j].i2cAddress = 0x0C+i;
      //mlxEX(mlx[i].i2cAddress, &(mlx[0].statusByte));
      mlxInit(&mlx[i+4*j]);
      mlxSB(mlx[i+4*j].i2cAddress, mlx[i+4*j].zyxt,&(mlx[i+4*j].statusByte));
      delay(20);
    }
  }
  delay(100);
  
  //Serial.println(F("Start"));
  //ActiveSensors();
  nDevices=11;
  //Serial.println(nDevices);
  
  message.sensorsArray_length = nDevices;
  

  mess = new vizzy_tactile::TacVector[nDevices];
  //message.sensorsArray[nDevices];
  

//   vizzy_tactile::SetNumSensors srv;
//   
//   srv.request.numSensors = nDevices;
//    
//   if (client.call(srv)){
//      ROS_INFO("Number: %d", nDevices);
//     }
//   else {
//      ROS_ERROR("Failed to call service");
//      return 1;
//     }  
  delay(100);   
}

void loop() {
   
  message.header.stamp = nh.now();
  message.header.frame_id = "/right_tactile";

 le=0;
 for(j=0;j<4;j++){
 // sprintf(buffer,"/tactileright_%d",j+1);
  
  tcaselect(j);
    
    for(i=0;i<4;i++){

      if(SensorActive[i+4*j]==1){

      mlxRM(mlx[i+4*j].i2cAddress, mlx[i+4*j].zyxt, &(mlx[i+4*j].rawZ), &(mlx[i+4*j].rawY), &(mlx[i+4*j].rawX), &(mlx[i+4*j].rawTemp), &(mlx[i+4*j].statusByte)); 
 
      int16_t X = to2SComplement(mlx[i+4*j].rawX);
      int16_t Y = to2SComplement(mlx[i+4*j].rawY);
      int16_t Z = to2SComplement(mlx[i+4*j].rawZ); 

      mess[le].id=i+4*j+1;
      mess[le].x=X;
      mess[le].y=Y;
      mess[le].z=Z;

      
      //message.sensorsArray.id = i+4*j+1;
      //message.sensorsArray.x = X;
      //message.sensorsArray.y = Y;
      //message.sensorsArray.z = Z;

     // message.sensorsArray.push_back(mess);
      le++;
      //delay(5);
        }    
     } 
  } 

  //Serial.println(mess[le-1].z);
  message.sensorsArray=mess;
  //Serial.println(message.sensorsArray[le-1].z);
  //Serial.println("Estou a publicar");
  chatter.publish(&message);

  //Serial.println("Estou a publicar depois");  
  nh.spinOnce();
//  delay(1);
}

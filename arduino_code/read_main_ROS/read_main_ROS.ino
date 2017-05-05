#include <Wire.h>
#include "MLX90393.h"
#define TCAADDR 0x70  //Address of the I2C multiplexer
#include <ros.h>
#include  <vizzy_tactile/Tactile.h>
#include  <vizzy_tactile/TacVector.h>


//int SensorActive[16] = {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0}; //Sensors to read - CHANGE HERE

//int SensorActive[16] = {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0}; // Only Sensor nº 3
int SensorActive[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; // All 16

ros::NodeHandle_<ArduinoHardware,2,2,60,125>  nh;

vizzy_tactile::Tactile message;
ros::Publisher chatter("/tactile", &message);


// Global Variables
struct MLX90393 mlx[16]; // define a variable for each mlx90393 chip. 
int i=0,j=0;
unsigned long previousMillis = 0;

void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}
 
void setup() {
  nh.getHardware()->setBaud(115200);
  nh.initNode();
  nh.advertise(chatter);
  
  
  Wire.begin();               // join i2c bus
  Wire.setClock(400000);     //Wire.setClock() must be called after Wire.begin()
                              // Cant use this with Arduino Leonardo...
  //Serial.begin(115000);

  for(j=0;j<4;j++){
    tcaselect(j);
    
    for(i=0;i<4;i++){
      mlx[i+4*j]= MLX_DEFAULT2;        // Set default values
      mlx[i+4*j].i2cAddress = 0x0C+i;
      //mlxEX(mlx[i].i2cAddress, &(mlx[0].statusByte));
      mlxInit(&mlx[i+4*j]);
      mlxSB(mlx[i+4*j].i2cAddress, mlx[i+4*j].zyxt,&(mlx[i+4*j].statusByte));
      delay(10);
    }
  }
  delay(50);
}

void loop() {

    //unsigned long currentMillis = millis();
    //Serial.println(currentMillis-previousMillis);
   // previousMillis = currentMillis;
   
  message.header.stamp = nh.now();
  message.header.frame_id = "/right_tactile";

  
 for(j=0;j<4;j++){
 // sprintf(buffer,"/tactileright_%d",j+1);
  
  tcaselect(j);
    
    for(i=0;i<4;i++){

      if(SensorActive[i+4*j]==1){

      mlxRM(mlx[i+4*j].i2cAddress, mlx[i+4*j].zyxt, &(mlx[i+4*j].rawZ), &(mlx[i+4*j].rawY), &(mlx[i+4*j].rawX), &(mlx[i+4*j].rawTemp), &(mlx[i+4*j].statusByte)); 
 
      int16_t X = to2SComplement(mlx[i+4*j].rawX);
      int16_t Y = to2SComplement(mlx[i+4*j].rawY);
      int16_t Z = to2SComplement(mlx[i+4*j].rawZ);

     // data += String(i+4*j+1) + ", "; // print Status Byte in Binary format // why ERROR bit is always 1
     // data += String(X) + ", ";
     // data += String(Y) + ", ";
     // data += String(Z);

   //   sprintf(buffer,"/tactileright_%d",i+4*j+1);
      
 

      message.sensorsArray[i+4*j].x = X;
      message.sensorsArray[i+4*j].y = Y;
      message.sensorsArray[i+4*j].z = Z;

      
     
      //delay(5);
        }    
     } 
  } 
  chatter.publish(&message);
  nh.spinOnce();
//  delay(1);
}

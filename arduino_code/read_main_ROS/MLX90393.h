/*
  Modified by Tiago Paulino (tiago.paulino@tecnico.ulisboa.pt)
  April 2017
  -------------------------------------
  File:   MLX90393.h
  Author: Sophon Somlor
  Email:  sophonsomlor@gmail.com
  Date:   10 November 2016
  Version: 1
  Purpose: This library is for Melexis MLX90393 chip: It is modified from the library provided by Melexis for mbeb (https://www.melexis.com/en/documents/tools/tools-mlx90393-library-header-file-h, and https://www.melexis.com/en/documents/tools/tools-mlx90393-source-code-file-cpp).
         **use together with MLX90393_MEM_CMD.h
*/
#include "MLX90393_MEM_CMD.h"
#include <Wire.h>

///////////////////////////////////////
// I2C address CONSTANT : 01 means A1 = 0, A0 = 1
///////////////////////////////////////
#define I2C_ADD_00 0x0C
#define I2C_ADD_01 0x0D
#define I2C_ADD_10 0x0E
#define I2C_ADD_11 0x0F

///////////////////////////////////////
// OFFSET CONSTANT
///////////////////////////////////////
#define MIDDLE_16BIT          32768
#define OFFSET_X_BASE         MIDDLE_16BIT
#define OFFSET_Y_BASE         MIDDLE_16BIT
#define OFFSET_Z_BASE         MIDDLE_16BIT // should be set more or less than the middle value because Z value only goes in one direction
#define OFFSET_SAMPLING_NUM   25

//////////////
// Structure of MLX90393
//////////////
struct MLX90393 {
  uint16_t gain;
  uint16_t tcmpEn;
  uint16_t digFilt;
  uint16_t res;
  uint16_t measurement_mode;
  
  uint8_t zyxt;
  
  uint8_t i2cAddress;
  uint8_t statusByte; // maybe not necessary but good to have ?
  
  uint16_t rawX;
  uint16_t rawY;
  uint16_t rawZ;
  uint16_t rawTemp;
};

const struct MLX90393 MLX_DEFAULT = {GAINSEL_DEF, TCMP_EN_DEF, DIG_FILT_DEF, RES_XYZ_DEF, SB_XYZ, B1110, I2C_ADD_00, 0, 0,0,0,0};
const struct MLX90393 MLX_DEFAULT2 = {GAINSEL_7, TCMP_EN_OFF, DIG_FILT_5, RES_XYZ_ALL_0, SB_XYZ, B1110, I2C_ADD_00, 0, 0,0,0,0};
///////////////////////
// Global variables
///////////////////////
uint8_t write_buffer[10]; // to collect what to write via I2C before sending to mlxSendI2C
uint8_t read_buffer[10]; // to collect what to read via I2C before sending to mlxSendI2C
uint8_t recieve_buffer0[3];
uint8_t recieve_buffer1[3];
uint8_t recieve_buffer2[3];
///////////////////////
// function prototype
///////////////////////
void mlxInit(MLX90393 *mlx); // to combine all the configuration bit and initialize the chip
void mlxInitCalibration(MLX90393 *mlx); // to start the calibration by calculing offset of X, Y, & Z
void mlxWriteADD0(MLX90393 *mlx); // to write address 0 of the chip's memory
void mlxWriteADD1(MLX90393 *mlx); // to write address 0 of the chip's memory
void mlxWriteADD2(MLX90393 *mlx); // to write address 0 of the chip's memory
void mlxSM(uint8_t i2c_address, uint8_t zyxt, uint8_t *stByte); // SM
void mlxSB(uint8_t i2c_address, uint8_t zyxt, uint8_t *stByte); // SB
void mlxSetMode(uint8_t i2c_address, uint8_t measurement_mode, uint8_t *stByte); // SM, SB, SWOC
void mlxRM(uint8_t i2c_address, uint8_t zyxt, uint16_t *z, uint16_t *y, uint16_t *x, uint16_t *t, uint8_t *st); // RM
void mlxWR(uint16_t address, uint16_t data, uint8_t i2c_address, uint8_t *stByte); // WR via I2C
void mlxRR(uint16_t address, uint8_t i2c_address, uint8_t *recieve_buffer);         // RR via I2C
void mlxEX(uint8_t i2c_address, uint8_t *stByte); // EX
// a function to HR
// a function to HS
void mlxSendI2C(uint8_t i2c_address, uint8_t *send_buffer, uint8_t send_data_length, uint8_t *recieve_buffer, uint8_t recieve_data_length);
uint8_t count_set_bits(uint8_t number);
int16_t to2SComplement(uint16_t before);

void mlxReadParameters(uint8_t address);

/////////////
// function
/////////////

void mlxReadParameters(uint8_t address)
{
   mlxRR(MEM_ADD_0, address, recieve_buffer0); // example of using a command, Read Register in this case, to read an address in the chip
   mlxRR(MEM_ADD_1, address, recieve_buffer1);
   mlxRR(MEM_ADD_2, address, recieve_buffer2);

   uint8_t GAIN_SEL = (recieve_buffer0[2] >>3 ) & 7;
   uint8_t DIG_FILT = (recieve_buffer2[2] >> 2) & 7;
   uint8_t OSR = recieve_buffer2[2] & 3;
   uint8_t RESX = (recieve_buffer2[2] >> 5) & 3;
   uint8_t RESY = ((recieve_buffer2[1] & 1) << 1) | ((recieve_buffer2[2] >> 7)&1);
   uint8_t RESZ = (recieve_buffer2[1] >> 1) & 3;
   
   
   Serial.print("PARAMETERS OF MLX: ");
   Serial.println(address,HEX);
   Serial.print("DIG_FILT: ");
   Serial.println(DIG_FILT);
   Serial.print("GAIN_SEL: ");
   Serial.println(GAIN_SEL);
   Serial.print("OSR: ");
   Serial.println(OSR);
   Serial.print("RESX: ");
   Serial.println(RESX);
   Serial.print("RESY: ");
   Serial.println(RESY);
   Serial.print("RESZ: ");
   Serial.println(RESZ);
}

void mlxInit(MLX90393 *mlx)
{
  // set necessary memory map including...
  // address 0 // set gain
  mlxWriteADD0(mlx);
  // address 1 // enable TCMP
  mlxWriteADD1(mlx);
  // address 2 // set RES and DIG_FILT
  mlxWriteADD2(mlx);
  
  mlx->rawX = 0;
  mlx->rawY = 0;
  mlx->rawZ = 0;
  mlx->rawTemp = 0;
}

void mlxWriteADD0(MLX90393 *mlx)
{
  uint16_t data;
  
  data = Z_SERIES_DEF | mlx->gain | HALLCONF_DEF;
//  Serial.print("ADD0:");
//  Serial.println(data, BIN);
  mlxWR(MEM_ADD_0, data, mlx->i2cAddress, &(mlx->statusByte));
}

void mlxWriteADD1(MLX90393 *mlx)
{
  uint16_t data;
  
  data = TRIG_INT_SEL_DEF | COMM_MODE_DEF | WOC_DIFF_DEF | EXT_TRIG_DEF | mlx->tcmpEn | BURST_SEL_DEF | BURST_DATA_RATE_DEF;
//  Serial.print("data to ADD1:");
//  Serial.println(data, BIN);
  mlxWR(MEM_ADD_1, data, mlx->i2cAddress, &(mlx->statusByte));
}

void mlxWriteADD2(MLX90393 *mlx)
{
  uint16_t data;
  
  data = OSR2_DEF | mlx->res | mlx->digFilt | OSR_DEF;
//  Serial.print("ADD2:");
//  Serial.println(data, BIN);
  mlxWR(MEM_ADD_2, data, mlx->i2cAddress, &(mlx->statusByte));
}

void mlxInitCalibration(MLX90393 *mlx)
{
  int32_t offset_x = 0; // to collect the summation of the reading for setting up the average reading to set as an offset
  int32_t offset_y = 0; 
  int32_t offset_z = 0; 
  
  uint8_t delaytime = 20; // delay at each iteration of measurement averaging loop; put sufficient time here so that the chip measurement occur correctly
  // calculating offset
//  Serial.println("reading and summing measurements");
  // 1. read magnetic
  // 1.1 change into SB
  mlxSB(mlx->i2cAddress, mlx->zyxt, &(mlx->statusByte));
  // 1.2 looping
  // 1.2.1 RM
  // 1.2.2 sum up the reading of each axis
  for (int i = 0; i < OFFSET_SAMPLING_NUM; i++) {
    mlxRM(mlx->i2cAddress, mlx->zyxt, &(mlx->rawZ), &(mlx->rawY), &(mlx->rawX), &(mlx->rawTemp), &(mlx->statusByte));
    offset_x += mlx->rawX;
    offset_y += mlx->rawY;
    offset_z += mlx->rawZ;
    delay(delaytime);
  }
  mlxEX(mlx->i2cAddress, &(mlx->statusByte)); // exit the burst mode, make the chip idle
  
  // 1.3 averaging the summed reading as baseline
  offset_x = round((float)(offset_x) / (float)(OFFSET_SAMPLING_NUM));
  offset_y = round((float)(offset_y) / (float)(OFFSET_SAMPLING_NUM));
  offset_z = round((float)(offset_z) / (float)(OFFSET_SAMPLING_NUM));
  
  Serial.println("calculating offsets");
//  Serial.print("average offset_x: ");
//  Serial.println(offset_x);
//  Serial.print("average offset_y: ");
//  Serial.println(offset_y);
//  Serial.print("average offset_z: ");
//  Serial.println(offset_z);
  // 2. substract the averaged reading with the offset baseline
  offset_x -= OFFSET_X_BASE;
  offset_y -= OFFSET_Y_BASE;
  offset_z -= OFFSET_Z_BASE;
  
  Serial.print("offset_x: ");
  Serial.println(offset_x);
  Serial.print("offset_y: ");
  Serial.println(offset_y);
  Serial.print("offset_z: ");
  Serial.println(offset_z);
  // 3. write offset
  uint8_t recieve_buffer[9];
  mlxWR(MEM_ADD_OFFSET_X, (uint16_t)(offset_x), mlx->i2cAddress, &(mlx->statusByte));
  mlxWR(MEM_ADD_OFFSET_Y, (uint16_t)(offset_y), mlx->i2cAddress, &(mlx->statusByte));
  mlxWR(MEM_ADD_OFFSET_Z, (uint16_t)(offset_z), mlx->i2cAddress, &(mlx->statusByte));
  // checking the writing
//  Serial.println("Read memory to check writen offset");
//  mlxRR(MEM_ADD_OFFSET_X, mlx->i2cAddress, recieve_buffer);
//  mlxRR(MEM_ADD_OFFSET_Y, mlx->i2cAddress, recieve_buffer);
//  mlxRR(MEM_ADD_OFFSET_Z, mlx->i2cAddress, recieve_buffer);
  // read register (necesary??)
  
}

void mlxSM(uint8_t i2c_address, uint8_t zyxt, uint8_t *stByte)
{
  write_buffer[0] = (SM)|(zyxt);
  mlxSendI2C(i2c_address, write_buffer, 1, stByte, 1);
}

void mlxSB(uint8_t i2c_address, uint8_t zyxt, uint8_t *stByte)
{
  write_buffer[0] = (SB)|(zyxt);
  mlxSendI2C(i2c_address, write_buffer, 1, stByte, 1);
}

void mlxSetMode(uint8_t i2c_address, uint8_t measurement_mode, uint8_t *stByte) 
{
  write_buffer[0] = measurement_mode;
  mlxSendI2C(i2c_address, write_buffer, 1, stByte, 1);
}

void mlxRM(uint8_t i2c_address, uint8_t zyxt, uint16_t *z, uint16_t *y, uint16_t *x, uint16_t *t, uint8_t *st)
{
//  uint8_t byteNum;
//  byteNum = 1+2*count_set_bits(zyxt);
//  uint8_t bufferIndex = 0;
  // check conversion flag, DRDY, which seems to be avaiable only on INT pin
  // readout (using RM)
  write_buffer[0] = (RM)|(zyxt);
  mlxSendI2C(i2c_address, write_buffer, 1, read_buffer, 1+2*count_set_bits(zyxt)); // 1 (status byte) + 2*(zyxt)
  //In read buffer: 1 (status byte) + 2*[T+X+Y+Z] (data; high and low bytes)
  // 1. get a pair high & low bytes
  // 2. read the setup to see which measurement the pair belongs to
  // 3. Do 2's Complement (IF TCMP_EN = 0 & RES = 0 or 1) <-- TCMP_EN is always 1 anyway because we use OFFSET
  // 4. Store result into variable (raw)
  *st = read_buffer[0];
    
  if (zyxt & B0001) { // if t is 1
    *t = (read_buffer[1]<<8) | (read_buffer[2]);  
    *x = (read_buffer[3]<<8) | (read_buffer[4]);
    *y = (read_buffer[5]<<8) | (read_buffer[6]);
    *z = (read_buffer[7]<<8) | (read_buffer[8]);      
  } 
  else { // if t is 0, measure the rest. We measure all three axis all the time anyway
    *x = (read_buffer[1]<<8) | (read_buffer[2]);
    *y = (read_buffer[3]<<8) | (read_buffer[4]);
    *z = (read_buffer[5]<<8) | (read_buffer[6]);  
  }
}

void mlxWR(uint16_t address, uint16_t data, uint8_t i2c_address, uint8_t *stByte)
{
//  Serial.print("mlxWR: ");
  write_buffer[0] = WR;
//  Serial.print(write_buffer[0], BIN);
  write_buffer[1] = (data&0xFF00)>>8;
//  Serial.print(",");
//  Serial.print(write_buffer[1], BIN);
  write_buffer[2] = data&0x00FF;
//  Serial.print(",");
//  Serial.print(write_buffer[2], BIN);
  write_buffer[3] = address << 2;
//  Serial.print(",");
//  Serial.println(write_buffer[3], BIN);
  mlxSendI2C(i2c_address, write_buffer, 4, stByte, 1);
}

void mlxRR(uint16_t address, uint8_t i2c_address, uint8_t *recieve_buffer)
{
  write_buffer[0] = RR;
  write_buffer[1] = address << 2;
  mlxSendI2C(i2c_address, write_buffer, 2, recieve_buffer, 3);
}

void mlxEX(uint8_t i2c_address, uint8_t *stByte)
{
  write_buffer[0] = EX;
  mlxSendI2C(i2c_address, write_buffer, 1, stByte, 1);
}

void mlxSendI2C(uint8_t i2c_address, uint8_t *send_buffer, uint8_t send_data_length, uint8_t *recieve_buffer, uint8_t recieve_data_length)
{
  uint8_t i;
//  Serial.println("mlxSendI2C: data: ");
//    Serial.println("sending data");
  Wire.beginTransmission(i2c_address);
  for (i = 0; i < send_data_length; i++) {
    Wire.write(send_buffer[i]);
//    Serial.println(send_buffer[i], BIN);
  }
  Wire.endTransmission();
  delay(1); // 1ms delay here is a must
  i = 0;
  Wire.requestFrom(i2c_address, recieve_data_length);
//  Serial.println("recieving data");
  while (Wire.available()) {
    recieve_buffer[i] = Wire.read();
//  Serial.println(recieve_buffer[i], BIN);
    i++;
  }
//  Serial.println(recieve_buffer[0], BIN);
  delay(1); // 1ms delay here is a must
}

uint8_t count_set_bits(uint8_t number)
{
  uint8_t count = 0;
  while(number) {
    count++;
      number = number & (number-1);
  }
  return count;
}

int16_t to2SComplement(uint16_t before)
{
  const int negative = (before & (1 << 15)) != 0;
  
  if (negative){
    return before | ~((1 << 16) - 1);
  }
  else
    return before;
}

void NumberToAddress (int number, uint8_t *muxCH, uint8_t *address)
{
  if (number>0 && number <5){
  *muxCH = 0;}
  else if (number>4 && number <9){
  *muxCH = 1;}
  else if (number>8 && number <13){
  *muxCH = 2;}
  else if (number>12 && number <17){
  *muxCH = 3;}
  
  if(number==1 || number==5 || number==9 || number==13){
    *address = 0x0C;
  }
  else if(number==2 || number==6 || number==10 || number==14){
    *address = 0x0D;
  }
  else if(number==3 || number==7 || number==11 || number==15){
    *address = 0x0E;
  }
  else if(number==4 || number==8 || number==12 || number==16){
    *address = 0x0F;
  }
}

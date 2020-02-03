#include <Wire.h>
#include "mympu6050.h"


MyMPU6050::MyMPU6050(uint8_t i2cAddr)
{
  devAddr = i2cAddr;
}

void MyMPU6050::initialize(void)
{
/*  reset_mpu6050(imuAddr);
  setClockSource(imuAddr, MPU6050_CLOCK_PLL_XGYRO);
  setFullScaleGyroRange(imuAddr, MPU6050_GYRO_FS_250);
  setFullScaleAccelRange(imuAddr, MPU6050_ACCEL_FS_2G);
  setSleepEnabled(imuAddr, (uint8_t)false);
 */ /*
  Wire.beginTransmission(imuAddr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  */
}

/* WHO_AM_I register stores the upper 6 bits of MPU-60X0's
 *  7-bit I2C address. The least significant bit is determined
 *  by the vaue of the AD0 pin, which is not reflected in this
 *  register.
 *  
 * Returns address stored in WHO_AM_I register
 * bits 0 and 7 are hard coded to 0 
 */
uint8_t MyMPU6050::testConnection(void)
{
  return readByte((uint8_t)MPU6050_RA_WHO_AM_I);
}


uint8_t MyMPU6050::getDeviceAddress()const
{
  return devAddr;
}

uint8_t MyMPU6050::getConfigState(void)
{
  return readByte((uint8_t)MPU6050_RA_CONFIG); 
}

uint8_t MyMPU6050::getAccelConfigState(void)
{
  return readByte((uint8_t)MPU6050_RA_ACCEL_CONFIG); 
}

uint8_t MyMPU6050::getGyroConfigState(void)
{
  return readByte((uint8_t)MPU6050_RA_GYRO_CONFIG); 
}

uint8_t MyMPU6050::getPowerManagement1State(void)
{
  return readByte(MPU6050_RA_PWR_MGMT_1);
}


void MyMPU6050::writeByte(uint8_t regAddr, uint8_t data)
{
  Wire.beginTransmission(devAddr);     
  Wire.write(regAddr);              
  Wire.write(data);
  Wire.endTransmission(true);       // transmits bytes that were queued by write
                                    // sends stop message after transmission, releases i2c bus
}


uint8_t MyMPU6050::readByte(uint8_t regAddr)
{
  uint8_t data;
  Wire.beginTransmission(devAddr);
  Wire.write(regAddr);
  Wire.endTransmission(false);            // send TX buffer, send restart to keep connection alive
  Wire.requestFrom(devAddr, (uint8_t)1);  // request 1 byte, default true sends stop message after request,
                                          // releasing i2c bus
  data = Wire.read();
  return data;
}

// returns number of bytes read
uint8_t MyMPU6050::readBytes(uint8_t regAddr, uint8_t *buf, uint8_t count)
{
  uint8_t i = 0;
  Wire.beginTransmission(devAddr);
  Wire.write(regAddr);
  Wire.endTransmission(false);      // send TX buffer, send restart to keep connection alive
  Wire.requestFrom(devAddr, count);
  while(Wire.available() && i < count)
  {
    buf[i] = Wire.read();
  }
  return i;
}

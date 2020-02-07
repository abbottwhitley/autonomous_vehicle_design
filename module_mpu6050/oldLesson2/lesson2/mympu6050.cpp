#include <Arduino.h>    // Serial
#include <Wire.h>
#include "mympu6050.h"

#define SERIAL_DEBUG

MyMPU6050::MyMPU6050(uint8_t i2cAddr)
{
  devAddr = i2cAddr;
}

/*
 * Sets DEVICE_RESET bit to 1
 * All internal registers are reset to their default
 * values.
 * 
 * DEVICE_RESET bit automatically clears to 0 once 
 * the reset is complete.
 */
void MyMPU6050::reset(void)
{
  // bit 7 high is reset
  writeByte(MPU6050_RA_PWR_MGMT_1, 0x80);
}


void MyMPU6050::setClockSource(uint8_t source)
{
  // clock select is bits 2:0
  writeBits(MPU6050_RA_PWR_MGMT_1, 2, 3, source);
  
  #ifdef SERIAL_DEBUG
    uint8_t b;
    b = readByte(MPU6050_RA_PWR_MGMT_1);

    Serial.println(F("\nfunction: setClockSource"));
    
    if ( (b & 0x07) == source)
    {
      Serial.println(F("success updating source"));
    }
    else
    {
      Serial.print(F("error setting clock source, expected: "));
      Serial.print(source);
      Serial.print(F(", regVal: "));
      Serial.println(b,HEX);
    }

  #endif
}


void MyMPU6050::setFullScaleGyroRange(uint8_t scale)
{
  // full scale is bits 4:3
  writeBits(MPU6050_RA_GYRO_CONFIG, 4, 2, scale);
  
  #ifdef SERIAL_DEBUG
    uint8_t b;
    b = readByte(MPU6050_RA_GYRO_CONFIG);

    // full scale is bits 4:3
    uint8_t mask = 0x18;   // b0001 1000
    
    Serial.println(F("\nfunction setFullScaleGyroRange"));
   
    if( (b & mask)>>3 == scale)
    {
      Serial.print(F("Success setting gyro scale to "));
      Serial.println(scale, HEX); 
    }
    else
    {
      Serial.print(F("error setting gyro scale, expected: "));
      Serial.print(scale);
      Serial.print(F(", regVal: "));
      Serial.println(b,HEX);
    }
  #endif 

}

void MyMPU6050::setFullScaleAccelRange(uint8_t scale)
{
  // full scale is bits 4:3
  writeBits(MPU6050_RA_ACCEL_CONFIG, 4, 2, scale);
  
  #ifdef SERIAL_DEBUG
    uint8_t b;
    b = readByte(MPU6050_RA_ACCEL_CONFIG);

    // full scale is bits 4:3
    uint8_t mask = 0x18;   // b0001 1000
    
    Serial.println(F("\nfunction:setFullScaleAccelRange"));
   
    if( (b & mask)>>3 == scale)
    {
      Serial.print(F("Success setting accel scale to "));
      Serial.println(scale, HEX); 
    }
    else
    {
      Serial.print(F("error setting accel scale, expected: "));
      Serial.print(scale);
      Serial.print(F(", regVal: "));
      Serial.println(b,HEX);
    }
  #endif 

}

/*
 * Register: Power Management 1
 * Bit 6: sleep bit 
 *         1 - device is in low power sleep mode
 *         0 - device is not in sleep mode
 */
void MyMPU6050::setSleepEnabled(bool enabled)
{
  // sleep bit is 6
  writeBits(MPU6050_RA_PWR_MGMT_1, 6, 1, (uint8_t)enabled);

  #ifdef SERIAL_DEBUG
    uint8_t b;
    b = readByte(MPU6050_RA_PWR_MGMT_1);

    // sleep bit is 6
    uint8_t mask = 0x40;   // b0100 0000

    Serial.println(F("\nfunction: setSleepEnabled"));
    
    if( (b & mask)>>6 == enabled)
    {
      Serial.print(F("Success setting sleep to "));
      Serial.println(enabled, HEX); 
    }
    else
    {
      Serial.print(F("error setting sleep bit, expected: "));
      Serial.print(enabled);
      Serial.print(F(", regVal: "));
      Serial.println(b,HEX);
    }
  #endif 
}


/*
 * Section 4.28, Register 107 "Upon power up, the MPU-60X0 clock source 
 * defaults to the internal oscillator. However, it is highly
 * recommended that the device be configured to use one of the 
 * gyroscopes (or an external clock source) as the clock reference 
 * for improved stability."
 */
void MyMPU6050::initialize(void)
{
  setClockSource(MPU6050_CLOCK_PLL_XGYRO);
  setFullScaleGyroRange(MPU6050_GYRO_FS_250);
  setFullScaleAccelRange(MPU6050_ACCEL_FS_2G);
  setSleepEnabled(false); // wake up device
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

uint8_t MyMPU6050::getConfigState(void)const
{
  return readByte((uint8_t)MPU6050_RA_CONFIG); 
}

uint8_t MyMPU6050::getAccelConfigState(void)const
{
  return readByte((uint8_t)MPU6050_RA_ACCEL_CONFIG); 
}

uint8_t MyMPU6050::getGyroConfigState(void)const
{
  return readByte((uint8_t)MPU6050_RA_GYRO_CONFIG); 
}

uint8_t MyMPU6050::getPowerManagement1State(void)const
{
  return readByte(MPU6050_RA_PWR_MGMT_1);
}


/* Write multiple bits to an 8-bit device register
*
* regAddr - register address
* leftBit - leftmost bit to write (7-0)
* numBits - number of bits to write
* data - right-aligned value to write
*/
void MyMPU6050::writeBits(uint8_t regAddr, uint8_t leftBit, uint8_t numBits, uint8_t data)
{
  // 
  // 76543210 bit positions
  //      xx  arguments: leftBit = 4, length = 2
  // 00000110 bit mask 

  uint8_t regVal, mask;

  // get current register values
  regVal = readByte(regAddr);
  
  
  // shifts 1 to bit position length value
  // subtracting 1 ensures all bits to the right are 1's
  // and all other bits are 0's 
  // Example: length = 4
  // 1 << numBits produces 0001 0000 
  // (1 << numBits) - 1 produces 0000 1111 
  mask =  (1 << numBits) - 1;
  
  // shift the 1's to the left and zero fill
  // Example: leftBit is 5
  // 5 - 4 + 1 = 2, 0000 1111 << 2 becomes 0011 1100
  // Now have a bit mask of length 4 with leftmost bit position 5 
  mask = mask << (leftBit - numBits + 1);

  // shift data to correct position
  // example: data is 3, 0000 0011
  // shifting 5-4+1 = 2 to the left produces 0000 1100
  data = data << (leftBit - numBits + 1);

  // zero bits of interest in existing register value 
  regVal &= ~(mask); 
  // update register bits with data value 
  regVal |= data;

  writeByte(regAddr, regVal);

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

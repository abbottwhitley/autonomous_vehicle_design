#include <Wire.h>
#include "mympu6050.h"

// Serial Debug
#define SERIAL_DEBUG


MyMPU6050 mpu(MPU6050_ADDRESS_AD0_LOW);

struct SensorData
{
  int16_t accelX;
  int16_t accelY;
  int16_t accelZ;
  int16_t temperature;
  int16_t gyroX;
  int16_t gyroY;
  int16_t gyroZ;
};


/**  Global Variables **/
uint8_t imuAddr = MPU6050_ADDRESS_AD0_LOW;

/* Write multiple bits to an 8-bit device register
*
* devAddr - I2C slave device address
* regAddr - register address
* leftBit - leftmost bit to write (7-0)
* length - number of bits to write
* data - right-aligned value to write
*/
void writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t leftBit, 
  uint8_t length, uint8_t data)
{
  // 
  // 76543210 bit positions
  //      xx  arguments: leftBit = 4, length = 2
  // 00000110 bit mask 

  uint8_t regVal, mask;
  // assumes read works, can be improved by validating read success 
  read_i2c(devAddr, regAddr, &regVal, 1);
  
  // shifts 1 to bit position length value
  // subtracting 1 ensures all bits to the right are 1's
  // and all other bits are 0's 
  // Example: length = 4
  // 1 << length produces 0001 0000 
  // (1 << length) - 1 produces 0000 1111 
  mask =  (1 << length) - 1;
  
  // shift the 1's to the left and zero fill
  // Example: leftBit is 5
  // 5 - 4 + 1 = 2, 0000 1111 << 2 becomes 0011 1100
  // Now have a bit mask of length 4 with leftmost bit position 5 
  mask = mask << (leftBit - length + 1);

  // shift data to correct position
  // example: data is 3, 0000 0011
  // shifting 5-4+1 = 2 to the left produces 0000 1100
  data = data << (leftBit - length + 1);

  // zero bits of interest in existing register value 
  regVal &= ~(mask); 
  // update register bits with data value 
  regVal |= data;

  write_i2c(devAddr, regAddr, regVal);

}

/* Read bytes from device register
*
* devAddr - I2C slave device address
* regAddr - register address
* data - buffer to store bytes 
* nBytes - number of bytes to read
* 
* returns number of bytes read and stored in data buffers
*/
int read_i2c(uint8_t devAddr, uint8_t reg, uint8_t *data, uint8_t nBytes)
{
  Wire.beginTransmission(devAddr);          // start i2c communication
  Wire.write(reg);                          // specify the register to read
  Wire.endTransmission(false);              // keep the connection open
  Wire.requestFrom(devAddr, nBytes, (uint8_t)true); // read size nBytes from the reg
                                            // true means close communication when read ends
  int i = 0;
  while(Wire.available() && i < nBytes)
  {
    data[i] = Wire.read();
    ++i;
  }
  return i;
}

/* Write byte to device register
*
* devAddr - I2C slave device address
* regAddr - register address
* regByte - byte written to register 
* 
* Note: no error checking to ensure data is transmitted
*/
void write_i2c(uint8_t devAddr, uint8_t reg, uint8_t regByte)
{
  Wire.beginTransmission(devAddr);
  Wire.write(reg);
  Wire.write(regByte);
  Wire.endTransmission(devAddr);
}


/** MPU6050 functions **/
void reset_mpu6050(uint8_t devAddr)
{
  uint8_t devReset = 0x80;
  uint8_t regVal, bytesRead;
  write_i2c(devAddr, MPU6050_RA_PWR_MGMT_1, devReset);
  delay(100);
  bytesRead = read_i2c(MPU6050_ADDRESS_AD0_LOW, MPU6050_RA_PWR_MGMT_1, &regVal, 1);
  #ifdef SERIAL_DEBUG
    if(bytesRead == 1)
    {
      Serial.print("power reg after device reset: ");
      Serial.println(regVal,HEX);
      if( (regVal & 0x40) == 0x40)
      {
        Serial.println("sleep mode enabled");
      }
    }
    else
    {
      Serial.print("error,  bytes read after power reset command: ");
      Serial.println(bytesRead);
    }
  #endif
}

void setClockSource(uint8_t devAddr, uint8_t clockSource)
{
  // clock select is bits 2:0
  writeBits(devAddr, MPU6050_RA_PWR_MGMT_1, 2, 3, clockSource);

  #ifdef SERIAL_DEBUG
    uint8_t b;
    read_i2c(devAddr, MPU6050_RA_PWR_MGMT_1, &b, 1);

    // clock select is bits 2:0
    uint8_t mask = 0x07;   // b0000 0111

    Serial.println("setClockSource results");
    
    if( (b & mask) == clockSource)
    {
      Serial.print("Success setting clock source to ");
      Serial.println(clockSource, HEX); 
    }
    else
    {
      Serial.print("error setting clock source, expected: ");
      Serial.print(clockSource);
      Serial.print(", regVal: ");
      Serial.println(b,HEX);
    }
  #endif 
}


void setFullScaleGyroRange(uint8_t devAddr, uint8_t scale)
{
  writeBits(devAddr, MPU6050_RA_GYRO_CONFIG, 4, 2, scale);
  
  #ifdef SERIAL_DEBUG
    uint8_t b;
    read_i2c(devAddr, MPU6050_RA_GYRO_CONFIG, &b, 1);

    // full scale is bits 4:3
    uint8_t mask = 0x18;   // b0001 1000
    
    Serial.println("set full scale gyro range results");
   
    if( (b & mask)>>3 == scale)
    {
      Serial.print("Success setting gyro scale to ");
      Serial.println(scale, HEX); 
    }
    else
    {
      Serial.print("error setting gyro scale, expected: ");
      Serial.print(scale);
      Serial.print(", regVal: ");
      Serial.println(b,HEX);
    }
  #endif 

}

void setFullScaleAccelRange(uint8_t devAddr, uint8_t scale)
{
  writeBits(devAddr, MPU6050_RA_ACCEL_CONFIG, 4, 2, scale);
  
  #ifdef SERIAL_DEBUG
    uint8_t b;
    read_i2c(devAddr, MPU6050_RA_ACCEL_CONFIG, &b, 1);

    // full scale is bits 4:3
    uint8_t mask = 0x18;   // b0001 1000
    
    Serial.println("set full scale accel range results");
   
    if( (b & mask)>>3 == scale)
    {
      Serial.print("Success setting accel scale to ");
      Serial.println(scale, HEX); 
    }
    else
    {
      Serial.print("error setting accel scale, expected: ");
      Serial.print(scale);
      Serial.print(", regVal: ");
      Serial.println(b,HEX);
    }
  #endif 

}


void setSleepEnabled(uint8_t devAddr, uint8_t enabled)
{
  // sleep bit is 6
  writeBits(devAddr, MPU6050_RA_PWR_MGMT_1, 6, 1, enabled);

  #ifdef SERIAL_DEBUG
    uint8_t b;
    read_i2c(devAddr, MPU6050_RA_PWR_MGMT_1, &b, 1);

    // sleep bit is 6
    uint8_t mask = 0x40;   // b0100 0000

    Serial.println("setSleepEnabled results");
    
    if( (b & mask)>>6 == enabled)
    {
      Serial.print("Success setting sleep to ");
      Serial.println(enabled, HEX); 
    }
    else
    {
      Serial.print("error setting sleep bit, expected: ");
      Serial.print(enabled);
      Serial.print(", regVal: ");
      Serial.println(b,HEX);
    }
  #endif 
}




int readAllData_mpu6050(uint8_t devAddr, struct SensorData* sd)
{
  uint8_t buf[14];
  int bytesRead;
  bytesRead = read_i2c(devAddr, MPU6050_RA_ACCEL_XOUT_H, buf, (uint8_t)14);
  if(bytesRead == 14)
  {
    // first byte read from high order register, second byte from low
    // form 16 bit value from 8 bit values
    sd->accelX = (((int16_t)buf[0]) << 8) | buf[1];
    sd->accelY = (((int16_t)buf[2]) << 8) | buf[3];
    sd->accelZ = (((int16_t)buf[4]) << 8) | buf[5];
    sd->temperature = (((int16_t)buf[6]) << 8) | buf[7];
    sd->gyroX = (((int16_t)buf[8]) << 8) | buf[9];
    sd->gyroY = (((int16_t)buf[10]) << 8) | buf[11];
    sd->gyroZ = (((int16_t)buf[12]) << 8) | buf[13];
  }

  return bytesRead;

}

void printRawData(const SensorData *sd)
{
    Serial.print("a/g:\t");
    Serial.print(sd->accelX); Serial.print("\t");
    Serial.print(sd->accelY); Serial.print("\t");
    Serial.print(sd->accelZ); Serial.print("\t");
    Serial.print(sd->gyroX); Serial.print("\t");
    Serial.print(sd->gyroY); Serial.print("\t");
    Serial.println(sd->gyroZ); 
}




void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  delay(100);
  initialize_mpu6050();
  #ifdef SERIAL_DEBUG
    Serial.println("\nsetup complete");
  #endif
  delay(2000);

}

void loop() {
  //static unsigned long startTime = millis();
  //if( (millis() - startTime) > 500)
  {
    SensorData sd;
    int bytesRead;
    bytesRead = readAllData_mpu6050(imuAddr, &sd);
    if(bytesRead == 14)
    {
      printRawData(&sd);
    }
    else
    {
      Serial.print("\nError reading sensor data, bytesRead: ");
      Serial.print(bytesRead);
      Serial.println(", expected: 14\n");
    }

    //startTime = millis();
    
  }

}

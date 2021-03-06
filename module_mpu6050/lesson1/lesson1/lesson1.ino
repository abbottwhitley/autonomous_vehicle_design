#include <Arduino.h>
#include <Wire.h>

// MPU 6050 I2C address
#define MPU6050_ADDRESS_AD0_LOW     0x68   // i2c address pin low (GND), default
                                           // Decimal value of 104

// MPU 6050 register addresses
#define MPU6050_RA_PWR_MGMT_1   0x6B  // Register 107
#define MPU6050_RA_WHO_AM_I     0x75  // Register 117


bool testCommunication(uint8_t devAddr)
{
  uint8_t state;
  // Read byte from the WHO_AM_I register on device 0x68
  // Who am I register should contain a value of 0x68
  state = readByte(devAddr, MPU6050_RA_WHO_AM_I);
  // Verify that the device we're reading from is device 0x68
  if(state == 0x68){
    Serial.println("success, testCommunication\n");
    return true;
  }
  else{
    Serial.print("error, testCommunication, expected: 0x68, regVal: ");
    Serial.println(state,HEX);
    return false;
  }
}

void reportPowerState(uint8_t devAddr)
{
  uint8_t state;
  state = readByte(devAddr, MPU6050_RA_PWR_MGMT_1);
  Serial.print("** Power Management Register 1, ");
  Serial.println(state,HEX);
  Serial.print("Bit 7, Device Reset: ");
  Serial.println(state >> 8, HEX);
  Serial.print("Bit 6, Sleep:        ");
  Serial.println( (state & 0x40) >> 6, HEX);
  if( (state & 0x40) >> 6 == 1)
  {
    Serial.println("\t** Device is in sleep mode **\n");
  }
  Serial.print("Bit 5, Cycle:        ");
  Serial.println( (state & 0x20) >> 5, HEX);
  Serial.print("Bit 3, Temp_Dis      ");
  Serial.println( (state & 0x08) >> 3, HEX);
  Serial.print("Bits 2:0, CLKSEL     ");
  Serial.println( (state &0x07), HEX);
  Serial.println("");
  
}

// read a byte from device number 0x68 (address of the "device")
// Input:
//    uint8_t devAddr :: 8 bit unsigned integer value of the device's address (device to read from)
//    unit8_t regAddr :: 8 bit unsigned integer value of the register on the device to read
uint8_t readByte(uint8_t devAddr, uint8_t regAddr)
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

int main(void)
{
  init();
  Serial.begin(38400);
  Wire.begin();                 // Initiate Wire library, join I2C bus as master
  delay(100);

  if(testCommunication(MPU6050_ADDRESS_AD0_LOW) == true)
  {
    reportPowerState(MPU6050_ADDRESS_AD0_LOW);
  }
  Serial.println("test");

  while(1);
  return 0;
}

#include <Wire.h>
#include "mympu6050.h"

//#define SERIAL_DEBUG

//#ifdef SERIAL_DEBUG
  #include "report.h"
//#endif 


/**  Global Variables **/
MyMPU6050 mpu(MPU6050_ADDRESS_AD0_LOW);


void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  
  
  Serial.begin(38400);
  Wire.begin();             // Initiate Wire library, join I2C bus as master
  delay(100);
  
  // test communication by reading who am i register
  uint8_t byteRead;
  byteRead = mpu.testConnection();
  if(byteRead == 0x68)
  {
    Serial.println("Success communicating with MPU 6050");
  }
  else
  {
    Serial.println("Error communicating with MPU 6050");
    Serial.print("who am i value: ");
    Serial.println(byteRead, HEX);
    Serial.print("using device address: ");
    Serial.println(mpu.getDeviceAddress(), HEX);
    Serial.println("enter infinite loop state");
    while(1)
    {
      delay(1000);
    }
  }

  mpu.reset();
  delay(30);          // how much time is needed to reset?
  mpu.initialize();

  #ifdef SERIAL_DEBUG
    reportPowerState(mpu);
    reportConfigState(mpu);
    reportAccelConfigState(mpu);
    reportGyroConfigState(mpu);
  #endif

  Serial.println("**setup complete**");
  delay(2000);

}

void loop() {
  SensorData sd;
  mpu.readAllData(&sd);
  printAllData(&sd);
  //printScaledData(&sd);
  delay(1000);
}

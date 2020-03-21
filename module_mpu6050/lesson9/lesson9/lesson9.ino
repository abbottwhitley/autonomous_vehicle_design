/*  
 *  MPU-6050 Setup
 *    default configuration of 
 *    i2c clock frequency 400000 
 *    default configuration of
 *  calibrates accel
 * 
 */
#include <Arduino.h>
#include <Wire.h>
#include "mpu6050.h"
#include "helper.h"


//#define DEBUG

#define SAMPLE_INTERVAL_MS  50           // milliseconds


// Initiaize Serial, I2C, and mpu6050
void setup(void)
{
  Wire.begin();
  Wire.setClock(400000L);
  Serial.begin(115200);
  delay(100);
  setupMPU6050();
  
  #ifdef DEGUG
    Serial.println("setup complete");
  #endif
}



int main(void)
{
  SensorData offset, accel;
  unsigned long startTime;

  double roll, pitch;               // roll rotation about y, pitch rotation about x 
  double rollF = 0.0;  
  
  
  init();                           // Arduino function to initialize timers, pwm, other hardware
  setup();
  
  #ifdef DEGUG
    Serial.println(F("\n\nready to calibrate\n"));
  #endif
 
  calibrateAccelerometer(&offset, 10);

  #ifdef DEBUG
    Serial.println("\ncalibration complete\n");
    printOffsetValues(&offset);
    delay(3000);
  #endif
  
  startTime = millis();
  while(1)
  {
    if( (millis() - startTime) >= SAMPLE_INTERVAL_MS)
    {
      readAccelerometer(&accel);
      startTime = millis();         
      
      accel.x += offset.x;          // apply offset
      accel.y += offset.y;
      accel.z += offset.z;

      roll = atan(accel.y / sqrt(pow(accel.x,2) + pow(accel.z,2))) * 180.0/PI;
      pitch = atan(accel.x / sqrt(pow(accel.x,2) + pow(accel.z,2))) * 180.0/PI;

      #ifdef DEBUG
        printAngles(roll, pitch);
      #endif

      rollF = 0.94 * rollF + 0.06 * roll;

      Serial.print(roll);
      Serial.print(",");
      Serial.println(rollF);
      
    }
  }
    
   
  return 0;
  
}

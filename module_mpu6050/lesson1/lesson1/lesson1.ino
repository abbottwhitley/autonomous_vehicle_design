#include <Wire.h>
#include "mympu6050.h"

/**  Global Variables **/
MyMPU6050 mpu(MPU6050_ADDRESS_AD0_LOW);


void reportStartState()
{
  reportPowerState();
  reportConfigState();
  reportGyroConfigState();
  reportAccelConfigState();
}

void reportPowerState(void)
{
  uint8_t state;
  state = mpu.getPowerManagement1State();
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

void reportConfigState(void)
{
  uint8_t state;
  state = mpu.getConfigState();
  
  Serial.println("\n*** Configuration ***");
  if( ((state & 0x38) >> 3) == 0)
  {
    Serial.println("External Frame Synchronization Disabled as expected");
  }
  else
  {
    Serial.print("Warning: external frame synchronization enabled, setting: ");
    Serial.println((state & 0x38) >> 3, HEX);
  }

  Serial.println("\nDigital Low Pass Filter Configuration");
  Serial.println("  Accelerometer              Gyroscope");
  Serial.println("   (Fs = 1 kHz)");
  Serial.println("Bandwidth  Delay   Bandwidth  Delay  Fs(kHz)");
  Serial.println("(Hz)       (ms)    (Hz)       (ms)");
  Serial.println("============================================");
  switch(state&0x07)
  {
    case 0:
      Serial.println("    260    0       256        0.98      8");
    break;
    case 1:
      Serial.println("    184    2.0     188        1.9       1");
    break;
    case 2:
      Serial.println("     94    3.0      98        2.8       1");
    break;
    case 3:
      Serial.println("     44    4.9      42        4.8       1");
    break;
    case 4:
      Serial.println("     21    8.5      20        8.3       1");
    break;
    case 5:
      Serial.println("     10   13.8      10       13.4       1");
    break;
    case 6:
      Serial.println("      5   19.0       5       18.6       1");
    break;
    default:
      Serial.print("unknown, value: "); Serial.println(state&0x07, HEX);
  }

  Serial.println("");
}

void reportAccelConfigState(void)
{
  uint8_t state;
  state = mpu.getAccelConfigState();
  Serial.print("\n*** Accel Config, ");
  Serial.println(state, HEX);
  if( (state & 0xE0) == 0)
  {
    Serial.println("self-test disabled");
  }
  else
  {
    Serial.print("self-test enabled, bits 7:5: ");
    Serial.println((state & 0xE0) >> 5, HEX);
  }

  Serial.print("full scale range, +-");
  switch( (state & 0x18) >> 3)
  {
    case MPU6050_ACCEL_FS_2G:
      Serial.print(2);
    break;
    case MPU6050_ACCEL_FS_4G:
      Serial.print(4);
    break;
    case MPU6050_ACCEL_FS_8G:
      Serial.print(8);
    break;
    case MPU6050_ACCEL_FS_16G:
      Serial.print(16);
    break;
  } 

  Serial.println(" g");
}

void reportGyroConfigState(void)
{
  uint8_t state;
  state = mpu.getGyroConfigState();
  Serial.print("\n*** Gyro Config, ");
  Serial.println(state, HEX);
  if( (state & 0xE0) == 0)
  {
    Serial.println("self-test disabled");
  }
  else
  {
    Serial.print("self-test enabled, bits 7:5: ");
    Serial.println((state & 0xE0) >> 5, HEX);
  }

  Serial.print("full scale range, +-");
  switch( (state & 0x18) >> 3)
  {
    case MPU6050_GYRO_FS_250:
      Serial.print(250);
    break;
    case MPU6050_GYRO_FS_500:
      Serial.print(500);
    break;
    case MPU6050_GYRO_FS_1000:
      Serial.print(1000);
    break;
    case MPU6050_GYRO_FS_2000:
      Serial.print(2000);
    break;
  } 

  Serial.println(" deg/s");
  
}



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
    Serial.println("Success communicating with MPU 6050\n");
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

  reportStartState();

  Serial.println("setup complete");
  delay(2000);

}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(2000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(2000);
}

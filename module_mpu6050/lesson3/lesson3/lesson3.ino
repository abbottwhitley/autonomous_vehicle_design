#include <Arduino.h>
#include <Wire.h>

#define MPU6050_ADDRESS_AD0_LOW 0x68      // i2c address AD0 pin low (GND), default

#define ACCEL_XOUT_H 0x3B


void mysetup(void)
{
  Serial.begin(38400);
  Wire.begin();
  delay(100);
  Wire.beginTransmission(MPU6050_ADDRESS_AD0_LOW);
  Wire.write(0x6B);                       // power management 1 register
  Wire.write(0);                          // setting bit 6 to zero, wakes up device
                                          // setting other bits to zero turns off reset
                                          // and uses internal oscillator as clock
  Wire.endTransmission(true);
  Serial.println("setup complete");
}

int main(void)
{
  int16_t ax, ay, az, temp, gx, gy, gz;
  
  init();

  mysetup();

  while(1)
  {
    // read data from registers
    Wire.beginTransmission(MPU6050_ADDRESS_AD0_LOW);
    Wire.write(0x3B);                     // start reading register 0x3B (ACCEL_XOUT_H)
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050_ADDRESS_AD0_LOW, 14);  // request reading 14 bytes
    ax = Wire.read() << 8 | Wire.read();    // reads 0X3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
    ay = Wire.read() << 8 | Wire.read(); 
    az = Wire.read() << 8 | Wire.read(); 
    temp = Wire.read() << 8 | Wire.read(); 
    gx = Wire.read() << 8 | Wire.read(); 
    gy = Wire.read() << 8 | Wire.read(); 
    gz = Wire.read() << 8 | Wire.read(); 

    
    Serial.print("ax: \t");   Serial.print(float(ax) / float(16384));
    Serial.print("\tay: \t"); Serial.print(float(ay) / float(16384));
    Serial.print("\taz: \t"); Serial.print(float(az) / float(16384));
    Serial.print("\ttemp: \t"); Serial.print(float(temp) / float(340) + 36.53);
    Serial.print("\tgx: \t");   Serial.print(float(gx) / float(131));
    Serial.print("\tgy: \t"); Serial.print(float(gy) / float(131));
    Serial.print("\tgz: \t"); Serial.println(float(gz) / float(131));
    delay(1000);
  }

  return 0;
  
}

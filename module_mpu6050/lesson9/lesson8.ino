/* Calculate the x and y tilt angles using the arctangent.
 * 
 */

#include <Wire.h>
#include <math.h> 

const int MPUADDRESS = 0x68;

const unsigned long SAMPLE_INTERVAL = 20;     // milliseconds
unsigned long startTime;



void setup() {
  Wire.begin();                   // Wire library initialization
  Wire.beginTransmission(MPUADDRESS);   // Begin transmission to MPU, default I2C address
  Wire.write(0x6B);               // PWR_MGMT_1 register
  Wire.write(0);                  // MPU-6050 to start mode
  Wire.endTransmission(true);
  Serial.begin(9600);
  startTime = millis();
}


void readAccel(int16_t& x, int16_t& y, int16_t& z)
{
  Wire.beginTransmission(MPUADDRESS);     // Start transfer
  Wire.write(0x3B);                       // register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);            // Maintain connection
  Wire.requestFrom(MPUADDRESS, 6, true);         
  
  x = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
  y = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  z = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
}


void loop() {

  static int16_t x, y, z;
  static double theta, phi;
  if( (millis() - startTime) >= SAMPLE_INTERVAL)
  {
    readAccel(x, y, z);
    theta = atan2(x,sqrt(y*y + z*z))*180.0/PI;    // convert radians to degrees
    phi = atan2(y,sqrt(y*y + z*z)) * 180.0/PI;
    Serial.print("x tilt angle: ");
    Serial.print(theta,2);
    
    Serial.print(" deg");
    Serial.print(", y tilt angle: ");
    Serial.print(phi,2);
    Serial.println(" deg");
    startTime = millis();
  }
}

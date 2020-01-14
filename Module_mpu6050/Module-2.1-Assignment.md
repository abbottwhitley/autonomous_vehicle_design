# Module 2.1 Assignment

In this assignment you will read the raw accelerometer and gyroscope values from the MPU6050. You will be use the Arduino MPU6050 library by Electronic Cats.


## Hardware Required
- Arduino Uno, Nano, or Mega
- MPU-6050 
- Jumper Wires

## Circuit Schematic

- Arduino Uno & Nano use pins A4 and A5 for I2C
   - A4 - SDA
   - A5 - SCL 


## Install Arduino MPU6050 library

From the Arduino Tools menu, choose Manage Libraries to open the Library Manager window.
Type 6050 in the Library Manager search window.
Install MPU6050 by ELectronic Cats

![Arduino Library Manager MPU6050](./images/arduino_library_manager_mpu6050.png "Arduino Library Manager")


## Arduino Source Code

1. Open the MPU6050_raw example sketch
   a. The library may consist of C-style functions or a C++ class. 
   b. An Arduino library requires at least two files:
      i.  header file  (.h)
      ii. source file (.cpp)
   c. Refer to [ElectronicCats/mpu6050 repository](https://github.com/ElectronicCats/mpu6050)

2. 
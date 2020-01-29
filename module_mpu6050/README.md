## MPU-6050 Six-Axis (Gyro + Accelerometer) MEMS MotionTracking Device

"The MPU-6050 devices combine a 3-axis gyroscope and a 3-axis accelerometer on the same silicon die, together with an onboard Digital Motion Processor™ (DMP™), which processes complex 6-axis MotionFusion algorithms. The device can access external magnetometers or other sensors through an auxiliary master I²C bus, allowing the devices to gather a full set of sensor data without intervention from the system processor" [1]

[1]: https://www.invensense.com/products/motion-tracking/6-axis/mpu-6050/

![MPU-6000 Family Block Design](./images/mpu-6000-family-diagram.png "MPU-6000 Family Block Diagram")

"For precision tracking of both fast and slow motions, the parts feature a user-programmable gyro full-scale range of ±250, ±500, ±1000, and ±2000 °/sec (dps), and a user-programmable accelerometer full-scale range of ±2g, ±4g, ±8g, and ±16g. Additional features include an embedded temperature sensor and an on-chip oscillator with ±1% variation over the operating temperature range." [1]

### MPU6050 used to measure
- Acceleration
- Velocity
- Orientation
- Displacement


### MPU6050 Features
- MEMS 3-axis accelerometer and 3-axis gyroscope
- Power supply: 3 - 5 V
- Communication: I2C protocol
- 16-bit ADC provides high accuracy
- Digital Motion Processor (DMP) provides high computational power
- Can be used to interface with other I2C devices
- Configurable I2C address
- Built-in temperature sensor

### MPU-6050 Pinout

![MPU-6050 Pinout](./images/mpu6050-pinout.png "MPU-6050 Pinout")


### MPU-6050 Pin Configuration

| Pin Number | Pin Name | Description |
| ------ | ----- | ---------- |
| 1      | Vcc  | Powers module, may be +3V to +5V |
| 2 | Ground | Connect to system ground |
| 3 | Serial Clock (SCL) | I2C communication clock pulse |
| 4 | Serial Data (SDA) | I2C communication data transfer |
| 5 | Auxiliary Serial Data (XDA) | Used to interface other I2C modules with MPU6050, optional |
| 6 | Auxiliary Serial Clock (XCL) | Used to interface other I2C modules with MPU6050, optional |
| 7 | AD0 | Used to vary I2C address |
| 8 | Interrupt (INT) | Interrupt pin to indicate data is available to read |
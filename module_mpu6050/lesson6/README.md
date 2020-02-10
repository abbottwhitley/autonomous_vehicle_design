# Lesson 5 - Calculating Sensor Bias Offset

When an inertial sensor is at rest, there is often a small offset difference from the expected zero measurement values. This offset is known as sensor bias. The image below shows measurements from a gyroscope at rest, illustrating this device's sensor bias.

![Sensor Bias](./images/sensorbias.png "sensor bias")

## Sensor Bias 

The bias of a rate gyro is the average output when the device is sitting still. When the gryo is not moving, we expect its output to be zero. However, there is often a small offset in the average signal output, which is known as sensor bias. 

Sensor bias is caused by changes in physical properties over time. The physical property of each sensor is different, so they must each be individually calibrated to correct for the bias. Because the bias changes over time, sensors must be regularly calibrated.

You can find the constant bias (offset) error of a gyro by taking the average of the output over a long period of time while the device is not rotating. Once you know the constant bias you can subtract it from subsequent measurements to eliminate this form of error.

The accelerometer bias is calculated by placing the device on a flat surface, where it measures 0g on the X and Y axis and +1g on the Z axis. The offset is calculated in the same manner, by taking the average of the output over a long period of time while the device is not moving.

## MPU Hardware Offset Registers Application Note

The [MPU Hardware Offset Registers Application Note](invensense-hardware-offset-registers.pdf) provides some information about finding the offset biases for the accelerometer and gyroscope, as well as the gyro and accelerometer offset registers. Section 3 indicates the hardware offset registers can be used for offset cancellation when not using the DMP (Digital Motion Processor) algorithms. Note: We are not using the DMP.

When using the offset registers, all data from the MEMS sensors will have the stored offset values applied before outputting to the data registers for users to read. All data in the FIFO, output registers and used in the DMP will already have these offsets included.

## Calculating the Offset Biases

Place the sensor on flat surface in a level position. With the Z-axis pointing into the flat surface, the expected accelerometer measurement is 16384 (1g). The expected accelerometer X and Y axis measurements are zero. The device must be stationary so that the expected gyro output of each axis will be zero. 

Sampling measurements from each axis, we will be able to determine the average offset from the ideal values and use those average values as the offset biases.

## Acceptable Error

How many samples do we need to determine the offset bias? Suppose we choose 1000 samples and calculate average offset values. What is the error of these offset values?  Are these errors acceptable? What is our acceptable error level? 

Let's assume the accelerometer and gyroscope are set to their most sensitive configuration of +-2g (16384 LSB/g) and +-250 &deg;/sec (131 LSB/&deg;/sec). For the gyro, is 1 &deg;/sec acceptable? Integrating angular rotation for one axis, with an error of 1 &deg;/sec might result in an error of 60 degrees. Is 0.1 &deg;/sec acceptable? Over 60 seconds, that's a much smaller error of 6 degrees, but that error only continues to grow over time.

Realistically, we cannot reduce the bias error to zero, but let's see how small a value we can achieve. We will use the calibration process Luis Rodenas implemented in his [MPU6050_calibration.ino] (https://github.com/ezgode/Arduino_MPU6050/blob/master/Ardu_Sketches/MPU6050_calibration/MPU6050_calibration.ino) program. This example is widely referenced as a working calibration method.



It is a common practice to read and throw away several measurements, such as the first 100, to allow the device to stabilize. Why 100? Internet forum & blog posts advise this. In terms of credible advice, the MPU-6050 has been on the market for several years and widely used, making it a good starting point. 

Is there anything in the device data sheets or register descriptions that supports this?

```
int acel_deadzone=8;     // Acelerometer error allowed, make it lower to get more
                         // precision, but sketch may not converge  (default:8)

int giro_deadzone=1;     // Giro error allowed, make it lower to get more precision, 
                         // but sketch may not converge  (default:1)
```

The errors are based on sampling measurements with the accel and gyro configured at their most sensitive configurations of +-2g (16384 LSB/g) and +-250 &deg;/sec (131 LSB/&deg;/sec), respectively.<br>
- 8/16384 is approximately 0.00049 g
- 1/131 is approximately 0.0076 &deg;/sec<br><br>

## Calibration Algorithm

The image below illustrates the calibration process. The accelerometer and gyro offsets are set to zero. Sample 1000 measurements and calculate the average value for each offset. Use these as the new offset values, sample another 1000 measurements, calculate the mean value, comparing these new offset values to the required offset tolerance. Continue this process until the offset values converge to the desired tolerance.<br>

![Calibration Algorithm](./images/calibration_algo.jpeg "calibration algorithm")[2]

[2] http://mjwhite8119.github.io/Robots/assets/images/Control-Theory-Slides.025.jpeg 
<br>
<br>

## Calculating Mean Zero Offset


1. Read 100 measurements and disregard them
2. Read 1000 measurements and calculate their sum. Don't forget to wait between readings to ensure you are not reading the same value multiple times. The delay is based on the sensor's sample rate configuration.
3. Find the mean value of the sample by dividing the sum by 1000.


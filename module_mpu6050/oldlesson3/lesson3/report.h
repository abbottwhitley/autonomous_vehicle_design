#ifndef REPORT_H_INCLUDED
#define REPORT_H_INCLUDED

#include "mympu6050.h"

/*
 * Uses serial library to print power management 1
 * register value.
 */
void reportPowerState(MyMPU6050& mpu);

/*
 * Uses serial library to print configuration
 * register value.
 */
void reportConfigState(MyMPU6050& mpu);

/*
 * Uses serial library to print accelerometer
 * configuration register value.
 */
void reportAccelConfigState(MyMPU6050& mpu);

/*
 * Uses serial library to print gyroscope
 * configuration register value.
 */
void reportGyroConfigState(MyMPU6050& mpu);

/*
 * Prints all data in the structure
 */
void printAllData(const SensorData *sd);

/*
 * sd contains raw, unscaled data measurements
 * scales the data by the default scale 
 * prints the scaled values
 */
void printScaledData(const SensorData *sd);


#endif 

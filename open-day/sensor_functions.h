/*
 * sensor_functions.h
 *
 * This file contains #define's and function prototypes for voltage and current sensing
 *
 */

#ifndef SENSOR_FUNCTIONS.H
#define SENSOR_FUNCTIONS.H

/******************************
 *          Constants         *
 ******************************/
#define R_V1 5
#define R_V2 8
#define R_I1 5
#define R_I2 3

#define ANALOG_READ_MAX 1023.0

/******************************
 *     Function Prototypes    *
 ******************************/
// initialisation function
void sensor_initialise();

// get values
float getVoltage();
float getCurrent();
float getPower();

#endif

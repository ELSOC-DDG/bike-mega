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

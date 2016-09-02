/*
 * sensor_functions.cpp
 * 
 * This file contains function definitions for voltage and current sensing
 *
 */

#include "Arduino.h"
#include "bike.h"

// sensor_initialise()
//      initialises sensor pins as input pins

void sensor_initialise() {
    #ifdef DEBUG_HIGH_LEVEL
    Serial.println('Entering sensor_initialise()'); 
    #endif //DEBUG_HIGH_LEVEL

    pinMode(voltage_pin, INPUT);
    pinMode(current_pin, INPUT);

    #ifdef DEBUG_LOW_LEVEL
    Serial.println('Exiting sensor_initialise()');
    #endif
}

// getVoltage()
//      reads voltage at voltage_pin and returns voltage from 
//      generator as float 
float getVoltage() {
   return analogRead(voltage_pin)*(R_V1 * (R_V1 + R_V2) / ANALOG_READ_MAX);
}

// getCurrent()
//      reads current at current_pin and returns current from 
//      generator as float 
float getCurrent() {
    return analogRead(current_pin)*(R_I1 * (R_I1 + R_I2) / ANALOG_READ_MAX); 
}

// getPower()
//      returns power from generator as float
float getPower() {
    return getVolts()*getCurrent();
}

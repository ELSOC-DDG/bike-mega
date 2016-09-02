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

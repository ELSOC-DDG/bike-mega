#ifndef LOADREGULATOR_H
#define LOADREGULATOR_H

#include "PID_v1a.h"
#include "Arduino.h"


void loadregulator_Initialize(double setpoint,double kp, double ki, double kd);
void loadregulator_Shutdown();
#endif

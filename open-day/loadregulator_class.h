#ifndef LOADREGULATOR_CLASS_H
#define LOADREGULATOR_CLASS_H

#include "Arduino.h"

typedef struct loadregulator_data_{
struct loadregulator_data_ *prev;
struct loadregulator_data_ *next;

double ITerm;
double lastInput;
double kp, ki, kd;
double outMin,outMax;

int d;
}loadregulator_data;

class loadregulator{
  private:
  loadregulator_data *pdata;
  public:

  
  
   loadregulator(int frequency,float target_voltage);
  void handler(void);
  ~loadregulator();
};

typedef void (loadregulator::*loadregulator_handler)(void);


#endif

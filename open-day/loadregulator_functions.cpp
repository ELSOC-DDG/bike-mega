#include "bike.h"

// Use globals for now
PID *myPid;
double pid_input, pid_output, set_point;

void loadregulator_Shutdown(void){

  noInterrupts();
  TIMSK1 &= ~(1 << OCIE1A);  // disable timer compare inte
  interrupts();             // enable all interrupts 
  
  delete myPid;
}
void loadregulator_Initialize(double setpoint,double kp, double ki, double kd){

  // Initialize controller settings
  pid_input = 0;
  pid_output = 0;
  set_point = setpoint;
  
  // Create the PID controller object
  myPid = new PID(&pid_input, &pid_output, &set_point, kp, ki,kd, DIRECT);
  
  // Set controller mode
  myPid->SetMode(AUTOMATIC);

  // Initialise interrupt
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  OCR1A = 625;              // Preload output compare register for 100Hz
  TCCR1B |= (1 << WGM12);   // CTC mode
  TCCR1B |= (1 << CS12);    // 256 prescaler, Frequency is 16MHz/256
  TIMSK1 |= (1 << OCIE1A);  // enable timer compare inte
  interrupts();             // enable all interrupts 
}


ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{ 
    float myvolts;

    // Disable Interrupts
    noInterrupts();

    // Read in input
    myvolts = getVolts(); // input in generator voltage
    pid_input = myvolts;    

    // Compute PID function
    myPid->Compute();

    // Write output
    if(pid_output > 100)
      pid_output = 100;
    analogWrite(topLightPWM,255 - map(pid_output,0,100,0,255));    

    // Enable interrupts
    interrupts();             // enable all interrupts  
}


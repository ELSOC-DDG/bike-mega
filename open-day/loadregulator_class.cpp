#include "loadregulator_class.h"
//#include "bike.h"

static loadregulator_data *loadregulator_list = NULL;

// Timer ISR responsible for control loop
/*
ISR(TIMER1_COMPA_vect)          // timer compare interrupt service routine
{
  loadregulator_data *p;
  float u,e,y;
  float setpoint = 11;

  if(loadregulator_list != NULL)
  {
  

  p = loadregulator_list;

  // read in the measured variable
  u = (analogRead(1) / 1023.0) * 5;

  // generate error
  e = u - 11;

  // calculate proportional
  // calculate integral

  y = e;

  // output to backlighting
  //int brightness = map(floor(v), 0, 20, 0, 255);
  analogWrite(topLightPWM, y);
 
  
  // display the voltage data
  //sevenSeg_set((int)(u * 10));
  
  }

  
  
}
*/

// The constructor function which initialises the interrupt, etc...
loadregulator::loadregulator(int frequency, float target_voltage){

  // disable interrupts
  noInterrupts();

  // if not the first time
  if(loadregulator_list != NULL){
  }
  // if the first time
  else{
    // set up the interrupt
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1  = 0;

    OCR1A = 31250;            // compare match register 16MHz/256/2Hz
    TCCR1B |= (1 << WGM12);   // CTC mode
    TCCR1B |= (1 << CS12);    // 256 prescaler 
    TIMSK1 |= (1 << OCIE1A);  // enable timer compare inte
  }

  // add new data structure to list
  pdata = new loadregulator_data;


  pdata->ITerm = 0;
  pdata->lastInput = 0;
  
  pdata->kp;
  pdata->ki;
  pdata->kd;
  pdata->outMin;
  pdata->outMax;

  pdata->next = loadregulator_list;
  pdata->prev = NULL;

  if(loadregulator_list){
    loadregulator_list->prev = pdata;  
  }

  loadregulator_list = pdata;

  interrupts();             // enable all interrupts  
}


// The destructor function which cleans up
loadregulator::~loadregulator(){
  // cleanup list
  // if next in list, link it to previous
  if(pdata->next)
    pdata->next->prev = pdata->prev;
  // if previous in list, link it to next
  if(pdata->prev)
    pdata->prev->next = pdata->next;
  // if no previous, must be first
  else
    // make next the first
    loadregulator_list = pdata->next;

  delete pdata;
    
}


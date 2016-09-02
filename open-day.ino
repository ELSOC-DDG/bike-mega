/*
    open-day.ino

    Arduino sketch to control EDDG's bike project on open day 03/09/16
*/

#include "bike.h" // contains all required header files

// define how long rider rides in competition mode (seconds)
#define RUNTIME 10

// TODO: remove these if possible
// creat global variables
long average = 0;
int score_array[ARRAY_LENGTH] = {0};
int highScore = 0;
int score = 0;
int rank = 999;
long start_time = 0;
int analogSample = 0;
volatile bool startBtnPressed = 0;
volatile bool modeBtnPressed = 0;

void setup() {
    
  #ifdef DEBUG_HIGH_LEVEL
  Serial.begin(9600);
  #endif // DEBUG_HIGH_LEVEL
  
  // initialise the LED ring
  LEDring_initialise();
  
  // initialise the seven segment display
  sevenSeg_initialise(); 

  // initialise the voltage and current sensors
  sensor_initialise();

  #ifdef WAIT_FOR_ENTER
  readyPrompt();
  #endif // WAIT_FOR_ENTER
  
}


void readyPrompt(){
  Serial.println("Press enter to continue...");
  while(!Serial.available()){
  }
  char t = Serial.read();
}

// trend() - Sends data to serial port for trending on PC
void trend(float output){
     if(!Serial){
        Serial.begin(9600);
     }
     // output the system data to the serial port
     Serial.print(millis());
     Serial.print(",");
     Serial.print((int)floor(getVolts()*100));
     Serial.print(",");
     Serial.print((int)floor(getCurrent()*100));
     Serial.print(",");
     Serial.print((int)floor(1*100));
     Serial.println("");
}


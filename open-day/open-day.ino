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
  
  // TODO: initialise PWM output
  pinMode(topLightPWM, OUTPUT);

  #ifdef WAIT_FOR_ENTER
  readyPrompt();
  #endif // WAIT_FOR_ENTER
  
}

void loop() {
  // TODO: why is start interrupt rising? 
  // setup the start button pin as an interrupt
  attachInterrupt(startBtnInt, startInterrupt, RISING);

  // reset start button state variable
  startBtnPressed = 0;

  // enter idle mode until start btn pressed
  idleMode();
  
  // start btn has been pressed

  // stop start btn from triggering until after competition
  detachInterrupt(startBtnInt);


  #ifdef WAIT_FOR_ENTER
  readyPrompt();
  #endif // WAIT_FOR_ENTER
  
  startSequence();

  #ifdef WAIT_FOR_ENTER
  readyPrompt();
  #endif // WAIT_FOR_ENTER


  #ifdef DEBUG_HIGH_LEVEL
  Serial.println("Competition mode");
  #endif // DEBUG_HIGH_LEVEL  
    
  // start timing the user
  start_time = millis();

  loadregulator_Initialize(25,15,0,0);

  // competition mode
  // sample every 100ms for RUNTIME seconds (and update the led ring)
  while(millis() - start_time <= RUNTIME*1000) {
    float myvolts = getVoltage();
    float myamps  = getCurrent();
    float mypower = (int)floor(getPower());
    trend(1);

    average += mypower;

    LEDring_set(map(myvolts,0,50,0,200)); // TODO: change this
    sevenSeg_set(RUNTIME - ((millis() - start_time))/1000);
      
    delay(100);
  }

  loadregulator_Shutdown();

  #ifdef WAIT_FOR_ENTER
  readyPrompt();
  #endif // WAIT_FOR_ENTER
    
  // clear the led ring
  LEDring_set(0);

  // store score
  score = average/(RUNTIME*10);
    
  #ifdef DEBUG_LOW_LEVEL
  Serial.print("Score: ");
  Serial.println(score);
  #endif // DEBUG_LOW_LEVE

  rank = updateHighScoreTable(score, score_array);

  // update the highscore if it has been broken
  if(score > highScore) {
    highScore = score;
  }
    
  displayFinalScore(score, rank);

  // reset average, score and rank
  average = 0;
  score = 0;
  rank = 999; // TODO: negative num better?

  #ifdef WAIT_FOR_ENTER
  readyPrompt();
  #endif // WAIT_FOR_ENTER
}


/***********************************
 *        Other Functions          *
 ***********************************/

void startInterrupt() {
  
  // set the start button flag
  #ifdef DEBUG_HIGH_LEVEL
  Serial.println("");
  Serial.println("Start button pressed");
  Serial.println("");
  #endif // DEBUG_HIGH_LEVEL
  //startBtnPressed = 1;

  if(modeBtnPressed)
    sevenSeg_set(21);
  else
    sevenSeg_set(20);
    delay(2000);
    sevenSeg_set(882);
  
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
     Serial.print((int)floor(getVoltage()*100));
     Serial.print(",");
     Serial.print((int)floor(getCurrent()*100));
     Serial.print(",");
     Serial.print((int)floor(1*100));
     Serial.println("");
}


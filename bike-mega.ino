// include all necessary local header files
#include "bike.h"
#include "mode_functions.h"
#include "pin_definitions.h"
#include "LEDring_functions.h"
#include "sevenSeg_functions.h"


// define how long the rider needs to ride for (seconds)
#define runtime 15

// create variables for use in the program
long average = 0;
int score_array[ARRAY_LENGTH] = {0};
int highScore = 0;
int score = 0;
int rank = 999;
long start_time = 0;
int analogSample = 0;
volatile bool startBtnPressed = 0;
volatile bool modeBtnPressed = 0;
volatile long modeBtnTime = 0;

void setup() {

  //#ifdef DEBUG_HIGH_LEVEL
  Serial.begin(9600);
  //#endif // DEBUG_HIGH_LEVEL
  
  // initialise the LED ring
  LEDring_initialise();
  
  #ifdef WAIT_FOR_ENTER
  readyPrompt();
  #endif // WAIT_FOR_ENTER

  // initialise the seven segment display
  sevenSeg_initialise(); 

  #ifdef WAIT_FOR_ENTER
  readyPrompt();
  #endif // WAIT_FOR_ENTER

  // set the voltage and current pins as analog inputs
  //pinMode(sensorPin, INPUT);
  pinMode(voltagePin, INPUT);
  pinMode(currentPin, INPUT);
  // set pwm pin as output, motorout as analog input
  pinMode(topLightPWM, OUTPUT);
  pinMode(voltageMotor, INPUT);
}

float volt_buffer[10] = {0,0,0,0,0,0,0,0,0,0};

// trend() - Sends data to serial port for trending on PC
void trend(float myvolts, float myamps, float output){
     // output the system data to the serial port
     Serial.print(millis());
     Serial.print(",");
     Serial.print((int)floor(myvolts*100));
     Serial.print(",");
     Serial.print((int)floor(myamps*100));
     Serial.print(",");
     Serial.print((int)floor(1*100));
     Serial.println("");
}

void debug_loop(void){
  float myvolts;
  float myamps;
  float mypower;

  loadregulator_Initialize(20,20,0,0);
  // Display loop
  while(1){
    // display the quantity
    myvolts = analogRead(1) * (5.0 * 8.0 / 1023.0);
    myamps = analogRead(0) * (5.0 * 3.0 / 1023.0);
    mypower = (int)floor(myamps*myvolts);
    
    
    
    trend(myvolts,myamps,1);

      
    sevenSeg_set((int)floor(mypower));
    if(mypower > 300)
      mypower = 300;
    LEDring_set(map(myvolts,0,50,0,200));
    delay(100);
  }
  
}


void loop() { 
  float myvolts;
  float myamps;
  float mypower;
  //LEDring_set(1024);
  //LEDring_set(0);
    
  //loadregulator loadreg(100, 11);
  
  //while(1){
  //  sevenSeg_blankAll();
  //  LEDring_set(199);
  //}
  char buffer[1000];


  // debug_loop();
  // while(1){}
  
  // turn on all ring segments
  //LEDring_set(1024);
  // turn off all ring segments
  //LEDring_set(1024);

  // Display current loop values to 7seg  
  //while(1){

  // Advance the queue
  //for(int i=0;i<9;i++)
  //  volt_buffer[i+1] = volt_buffer[i];

  //analogSample = analogRead(0);
  //analogWrite(topLightPWM, 255);

  // Add to the queue
  //volt_buffer[0] = (analogSample / 1023.0) * 5.0;

  // Average the queque
  //volts_in = volt_buffer[9];
  //for(int i=0;i<9;i++)
  //  volts_in += volt_buffer[i];
  //volts_in = volts_in / 10.0;
  
  // Update isplay with voltage measurement
  //sevenSeg_set((int)(volts_in * 100));
  //delay(200);
    
  //}

  // reset the start button being pressed
  startBtnPressed = 0;
  
  // setup the start button pin as an interrupt
  attachInterrupt(startBtnInt, startInterrupt, FALLING);
  
  // setup the mode button pin as an interrupt
  // attachInterrupt(modeBtnInt, modeInterrupt, RISING);
  
  // enter idle mode until the start button is pressed
  idleMode();

  detachInterrupt(startBtnInt);
  // detachInterrupt(modeBtnInt);
  
  #ifdef WAIT_FOR_ENTER
  readyPrompt();
  #endif // WAIT_FOR_ENTER

  #ifdef WAIT_FOR_ENTER
  readyPrompt();
  #endif // WAIT_FOR_ENTER

  // select modes
  //if(startBtnPressed == 1) {
    // competition mode
    startSequence();
    
    #ifdef DEBUG_HIGH_LEVEL
    Serial.println("Competition mode");
    #endif // DEBUG_HIGH_LEVEL  
    
    // start timing the user
    start_time = millis();

    loadregulator_Initialize(25,15,0,0);

    // competition mode
    // sample every 100ms for runtime seconds (and update the led ring)
    while(millis() - start_time <= runtime*1000) {
      //analogSample = analogRead(sensorPin);
      //LEDring_set(analogSample);
      //average += analogSample;

      myvolts = analogRead(1) * (5.0 * 8.0 / 1023.0);
      myamps  = analogRead(0) * (5.0 * 3.0 / 1023.0);
      mypower = (int)floor(myamps*myvolts);
      trend(myvolts,myamps,1);

      average += mypower;

      LEDring_set(map(myvolts,0,50,0,200));
      sevenSeg_set(runtime - ((millis() - start_time))/1000);
      
      delay(100);
    }

    loadregulator_Shutdown();

    #ifdef WAIT_FOR_ENTER
    readyPrompt();
    #endif // WAIT_FOR_ENTER
    
    // clear the led ring
    LEDring_set(0);

    // store score
    score = average/(runtime*10);
    
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
    rank = 999;

    #ifdef WAIT_FOR_ENTER
    readyPrompt();
    #endif // WAIT_FOR_ENTER
    
  //}
  
}


int VoltsToInt(float volts){
  return floor((1024.0/5.0) * volts);
}
float IntToVolts(int value){
  return 5.0/1024 * value;
}

float int_error = 0;

void varyTopBrightness() {
  float ScalingFactor = 2.9/102.9;
  int brightness;
  float v = IntToVolts(analogRead(voltageMotor) / ScalingFactor);
  float setpoint = 14;
  float e = v - setpoint; // e is the error
  

  int_error += e;

  // must be possitive
  if(e>0){
    
  brightness =  v*10;            // proportional gain 
  brightness += int_error * 0.2; // integral gain 
  }
  else{
  brightness = 0;
  }

  // saturation
  if(brightness>255)
  brightness=255;

  
  /*
  Serial.begin(9600);
  Serial.print("brightness = ");
  Serial.print(brightness);
  Serial.println(" ");

  Serial.print("e = ");
  Serial.print(e);
  Serial.println(" ");
  */
  
 
  //int brightness = map(floor(v), 0, 20, 0, 255);
  analogWrite(topLightPWM, brightness);

  
  
  
}

void startInterrupt() {
  
  // set the start button flag
  #ifdef DEBUG_HIGH_LEVEL
  Serial.println("");
  Serial.println("Start button pressed");
  Serial.println("");
  #endif // DEBUG_HIGH_LEVEL
  startBtnPressed = 1;
  
}

void modeInterrupt() {
  noInterrupts();
  if((modeBtnTime+100) < millis()){
    // set the mode button flag
    modeBtnPressed = !modeBtnPressed;
    modeBtnTime = millis();
    if(modeBtnPressed)
      sevenSeg_set(11);
    else
      sevenSeg_set(10);
    //delay(2000000);
    //sevenSeg_set(881);
  }  
  interrupts();
}

void readyPrompt(){
  Serial.println("Press enter to continue...");
  while(!Serial.available()){
  }
  char t = Serial.read();
}


// v_gen = v_pin * 8
// i_gen = v_pin * 3

//have not defined it above yet
/*void pid_magic(){
  
  input = analogread(pinIn) * (8.0 / 1023.0); // input in generator voltage
  analogwrite(pinOut);
  setpoint = 100; 
  
  
  PID myPid(&input, &output, &setpoint, kp, ki,kd, DIRECT);
  myPid.set_mode(AUTOMATIC);
  
  mypid.compute();
  
  
  
}*/


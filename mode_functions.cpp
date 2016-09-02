/*  mode_functions.cpp
 *   
 *   This file contains all function prototypes and constant definitions for the different modes.
 *   
 *   Change Log: 
 *      28th December 2015 (JSS)
 *          - added debug prints
 *          
 *      28th August 2015 (JL)
 *          - clean up
 *          - added idleMode
 *          - created extern variables
 *          
 *      25th August 2015 (JSS)
 *          - created file
 */

// include all necessary header files
#include "Arduino.h"
#include "mode_functions.h"
#include "LEDring_patterns.h"
#include "LEDring_functions.h"
#include "sevenSeg_functions.h"

// startSequence()
//     this function runs the start sequence animation to 
//     countdown to when the rider should start pedalling
void startSequence() {
  #ifdef DEBUG_HIGH_LEVEL
  Serial.println("\nEntering startSequence()");
  #endif // DEBUG_HIGH_LEVEL
  
  // blank the seven segment display out
  sevenSeg_blankAll();
  
  // flash LED ring as recognition of start button press
  for(int numOfFlashes = 0; numOfFlashes < 2; numOfFlashes++) {
    
    #ifdef DEBUG_LOW_LEVEL
    Serial.println("LEDring: all on");
    #endif // DEBUG_LOW_LEVEL
    
    //LEDring_set(1024);
    LEDring_singleSet(0xFFFF);
    delay(250);
    
    #ifdef DEBUG_LOW_LEVEL
    Serial.println("LEDring: all off");
    #endif // DEBUG_LOW_LEVEL
    
    //LEDring_set(0);
    LEDring_singleSet(0x0000);
    // digitalWrite(ring_masterClear, LOW); // alternative, not tested 28/12/2015 is clear asynchronous?
    delay(250);
  }

  // provide a small delay before starting the countdown
  delay(350);
  
  // display a countdown on the seven segment display and flash the led ring
  #ifdef DEBUG_LOW_LEVEL
  Serial.println("Starting countdown:");
  #endif // DEBGU_LOW_LEVEL
  for(int i = 3; i > 0; i--) {
    sevenSeg_set(i);
    #ifdef DEBUG_LOW_LEVEL
    Serial.print(i);
    Serial.println("...");
    #endif // DEBUG_LOW_LEVEL
    //LEDring_set(1024);
    LEDring_singleSet(0xFFFF);
    delay(500);
    //LEDring_set(0);
    LEDring_singleSet(0x0000);
    // digitalWrite(ring_masterClear, LOW); // alternative, not tested 28/12/2015
    delay(500);
  }
  
  // clear the sign
  #ifdef DEBUG_LOW_LEVEL
  Serial.println("clearing sign...");
  #endif // DEBUG_LOW_LEVEL
  sevenSeg_blankAll();
  LEDring_set(0);
  #ifdef DEBUG_LOW_LEVEL
  Serial.println("Exiting startSequence()\n");
  #endif // DEBUG_LOW_LEVEL
}



// idleMode()
//     this function runs a series of animations whilst
//     there is nothing else happening
void idleMode() {
  float myvolts;
  float myamps;
  float mypower;
  
  #ifdef DEBUG_HIGH_LEVEL
  Serial.println("\nEntering idleMode()");
  #endif // DEBUG_HIGH_LEVEL
  
  // create variables for use in the function
  int i = 0;
  int loops = 0;
  bool change = 0;
  
  // display high score on the seven segment display
  sevenSeg_set(highScore);
  
  #ifdef DEBUG_LOW_LEVEL
  Serial.print("Displaying high score: ");
  Serial.println(highScore);
  #endif // DEBUG_LOW_LEVEL
  
  // display cool patterns on the led ring
  #ifdef DEBUG_LOW_LEVEL
  Serial.println("Displaying patterns");
  #endif // DEBUG_LOW_LEVEL
  
  while(!startBtnPressed) {  
    // if the end of the pattern is reached, increment the loop counter and reset i
    if(i == numOfSegments) {
      i = 0;
      loops++;//; can I remove this extra semicolon?
    }
    
    myvolts = analogRead(1) * (5.0 * 8.0 / 1023.0);
    myamps  = analogRead(0) * (5.0 * 3.0 / 1023.0);
    mypower = (int)floor(myamps*myvolts);
    // trend(myvolts,myamps,1);

    sevenSeg_set(mypower);
   
    // choose which pattern to display
    if(change == 1) {
      LEDring_singleSet(pattern_harry[i]);
      
      #ifdef DEBUG_LOW_LEVEL
      Serial.print("Displaying pattern_onebyone[");
      Serial.print(i);
      Serial.println("]");
      #endif // DEBUG_LOW_LEVEL
    }
    else {
      LEDring_singleSet(pattern_tom[i]);
      
      #ifdef DEBUG_LOW_LEVEL
      Serial.print("Displying pattern_two[");
      Serial.print(i);
      Serial.println("]");
      #endif // DEBUG_LOW_LEVEL
    }
    
    i++;
    delay(100);
    
    // check if the pattern needs to be changed or not (5 loops each pattern)
    if(loops >= 5) {
      change = !change;
      loops = 0;
      
      #ifdef DEBUG_LOW_LEVEL
      Serial.println("Changing patterns");
      #endif // DEBUG_LOW_LEVEL
    }
  }
  
  #ifdef DEBUG_LOW_LEVEL
  Serial.println("Exiting idleMode() Exit\n");
  #endif // DEBUG_LOW_LEVEL
  
  return;
}

void displayFinalScore(int score, int rank){
  #ifdef DEBUG_HIGH_LEVEL
  Serial.println("\nEntering displayFinalScore...");
  #endif // DEBUG_HIGH_LEVEL
  
  // flash the average score on the seven segment display (five times)
  int k = 0;
  for(k = 0; k < 4; k++){
    sevenSeg_set(score);
    delay(1000);
    sevenSeg_blankAll();
    delay(1000);
  }

  // Display rider position in leaderboard
  
  for(k = 0; k < 1025; k+=64){
    LEDring_set(k);
    delay(30);
  }
  
  #ifdef DEBUG_LOW_LEVEL
  Serial.print("Position: ");
  Serial.println(rank);
  #endif // DEBUG_LOW_LEVEL
  
  //sevenSeg_set(rank);  // everyone who doesn't make the leaderboard gets 10?
  //delay(5000);
  // write rank to middle digit
  sevenSeg_set(rank*10);
  sevenSeg_blankPin(BLpin0);

  delay(4000);

  sevenSeg_blankAll();

  for(k = 0; k < 16; k++){
    LEDring_singleSet(0xFFFF >> k);
    delay(30);
  }

  delay(100);

  LEDring_set(0);
  
  #ifdef DEBUG_LOW_LEVEL
  Serial.println("Exiting displayFinalScore...\n");
  #endif // DEBUG_LOW_LEVEL
}

// Inserts score into correct position in score_array and returns the scores rank
int updateHighScoreTable(int score, int score_array[]){
  
  #ifdef DEBUG_HIGH_LEVEL
  Serial.println("\nEntering updateHighScoreTable...");
  #endif // DEBUG_HIGH_LEVEL

  // create index variables
  int i = 0;
  int j = 0;
  
  // store current score into array
  while((i < (ARRAY_LENGTH - 1)) && (score_array[i] > score)) {
    i++;
  }

  if(i < ARRAY_LENGTH) {
    for(int j = (ARRAY_LENGTH - 1); j >= i; j--) {
      score_array[j] = score_array[j - 1];
    }
    score_array[i] = score;
  }

  #ifdef DEBUG_LOW_LEVEL
  Serial.println("Exiting updateHighScoreTable...\n");
  #endif // DEBUG_LOW_LEVEL
  
  return i+1;
}


/*  sevenSeg_functions.cpp
 *   
 *   This file contains all functions for the seven segment display
 *   
 *   Change Log: 
 *      28th August 2015 (JL)
 *          - clean up
 *          - added initialisation function
 *      
 *      23th August 2015 (JSS) 
 *          - constants moved from .cpp file to .h file
 *          
 *      21st August 2015 (JL & JSS)
 *          - added blanking functions
 *          
 *      16th August 2015 (JSS)
 *          - created file with initial definitions
 */

// include all necessary local header files
#include "Arduino.h"
#include "bike.h"

// sevenSeg_initialise()
//     this function intialises the seven segment display by
//     setting all the necessary pins to the correct pin modes
void sevenSeg_initialise() {
  #ifdef DEBUG_HIGH_LEVEL
  Serial.println("\nEntering sevenSeg_initialise()");
  #endif // DEBUG_HIGH_LEVEL
  pinMode(BLpin0, OUTPUT);
  pinMode(BLpin1, OUTPUT);
  pinMode(BLpin2, OUTPUT);
  pinMode(ABCDpin0, OUTPUT);
  pinMode(ABCDpin1, OUTPUT);
  pinMode(ABCDpin2, OUTPUT);
  pinMode(ABCDpin3, OUTPUT);
  pinMode(LDpin0, OUTPUT);
  pinMode(LDpin1, OUTPUT);
  pinMode(LDpin2, OUTPUT);

  #ifdef DEBUG_LOW_LEVEL
  Serial.println("Exiting sevenSeg_initialise()\n");
  #endif // DEBUG_LOW_LEVEL
}

// sevenSeg_blankPin()
//     this function sets a specific pin on the seven segment
//     display to blank out the digit
void sevenSeg_blankPin( int pin ) {
  digitalWrite( pin, !PH );
}

// sevenSeg_blankAll()
//     this function sets all the pins on the seven segment
//     display to blank out all the digits
void sevenSeg_blankAll() {
  digitalWrite( BLpin0, !PH );
  digitalWrite( BLpin1, !PH );
  digitalWrite( BLpin2, !PH );
}

// sevenSeg_unblankPin()
//     this function clears a specific pin on the seven segment
//     display to unblank the digit
void sevenSeg_unblankPin( int pin ) {
  digitalWrite( pin, PH );
}

// sevenSeg_unblankAll()
//     this function clears all the pins on the seven segment
//     display to unblank all the digits
void sevenSeg_unblankAll() {
  digitalWrite( BLpin0, PH ); // enable blanking
  digitalWrite( BLpin1, PH );
  digitalWrite( BLpin2, PH );
}

// sevenSeg_set()
//     this function writes a number to the seven segment
//     display, and returns true if the number is 0
bool sevenSeg_set( int num ) {
  #ifdef DEBUG_LOW_LEVEL
  Serial.println("\nEntering sevenSeg_set()");
  Serial.print("Setting sevenSeg to ");
  Serial.println(num);
  #endif // DEBUG_LOW_LEVEL
  int LDpins[3] = {LDpin0, LDpin1, LDpin2};
  int ABCDpins[4] = {ABCDpin0, ABCDpin1, ABCDpin2, ABCDpin3};

  int digits[3] = {0, 0, 0};
  int ABCD[4] = {0, 0, 0, 0};

  // clear all the latches on the ICs
  for(int i = 0; i < numOfDigits; i++) {
    digitalWrite(LDpins[i], LOW);
  }

  // split the numbers into each digit
  int tempNum = num;
  for(int i = 0; i < numOfDigits; i++) {
    digits[i] = (tempNum%(int)pow(10, i+1))/(int)pow(10, i);
    tempNum = tempNum - digits[i]*(int)pow(10, i);
  }

  // print each digit to seven segment display
  for(int i = 0; i < numOfDigits; i++) {
    for(int j = 0; j < 4; j++) {
      digitalWrite(ABCDpins[j], bitRead(digits[i], j));
    }

    // toggle the latches to finish writing the number
    digitalWrite( LDpins[i], HIGH );
    digitalWrite( LDpins[i], LOW );
  }

  // unblank all the digits
  sevenSeg_unblankAll();

  // check if there are any leading zeros to blank out
  if(digits[2] == 0) {
    sevenSeg_blankPin(BLpin2);
    if(digits[1] == 0) {
        sevenSeg_blankPin(BLpin1);
    }
  }

  // return true if the number is 0
  if( num == 0 ) {
		return true;
	}

  // otherwise return false
	else {
		return false;
	}
  #ifdef DEBUG_LOW_LEVEL
  Serial.println("Exiting sevenSeg_set()\n");
  #endif // DEBUG_LOW_LEVEL
}

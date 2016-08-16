/*  LEDring_functions.cpp
 *   
 *   This file contains all function definitions for the led ring
 *   
 *   Change Log: 
 *      28th December 2015
 *          - added debug prints
 *          
 *      28th August 2015 (JL)
 *          - clean up
 *          - added initialisation function
 *          - removed unused function prototypes
 *          - converted binary patterns to hexadecimal notation and expanded to 16 bits
 *          - added minAnalogInput and maxAnalogInput constants to make expanding easier
 *          
 *      27th August 2015 (JL & JSS)
 *          - fixed bug (inverted output of patterns)
 *          
 *      25th August 2015 (JSS)
 *          - clean up
 *          - fixed bug (variable and definition conflict of "numberOfSegments")
 *          
 *      23rd August 2015 (JSS) 
 *          - added "numberOfSegments" constant definition
 *          
 *      21st August 2015 (JSS)
 *          - fixed bug (missing semi-colon)
 *          
 *      16th August 2015 (JSS)
 *          - created file with initial definitions
 */

// include all necessary header files
#include "Arduino.h"
#include "pin_definitions.h"
#include "LEDring_functions.h"

void pulsePin(int pinNum){
  digitalWrite(pinNum, HIGH);
  digitalWrite(pinNum, LOW);
}

// LEDring_initialise()
//     this function intialises the led ring display by
//     setting all the necessary pins to the correct pin modes
void LEDring_initialise() {
  #ifdef DEBUG_HIGH_LEVEL
  Serial.println("\nEntering LEDring_initialise()");
  #endif // DEBUG_HIGH_LEVEL
  pinMode(ring_dataPin, OUTPUT);
  pinMode(ring_clkPin, OUTPUT);
  pinMode(ring_latchPin, OUTPUT); 
  pinMode(ring_masterClear, OUTPUT);
  pinMode(ring_outputEnable, OUTPUT);

  digitalWrite(ring_dataPin, LOW);
  digitalWrite(ring_clkPin, LOW);
  digitalWrite(ring_latchPin, LOW);
  
  #ifdef DEBUG_LOW_LEVEL
  Serial.println("Disabling output");
  #endif // DEBUG_LOW_LEVEL
  digitalWrite(ring_outputEnable, HIGH); // disable output (blank all LED's)
  
  #ifdef DEBUG_LOW_LEVEL
  Serial.println("Clearing registers");
  #endif // DEBUG_LOW_LEVEL
  digitalWrite(ring_masterClear, LOW); // clear shift registers

  pulsePin(ring_latchPin);  // move cleared registers to outputs (outputs still blanked because OE is HIGH)

  #ifdef DEBUG_LOW_LEVEL
  Serial.println("Disabling clear");
  #endif // DEBUG_LOW_LEVEL
  digitalWrite(ring_masterClear, HIGH); // turn off clear
  //delay(10);

  #ifdef DEBUG_LOW_LEVEL
  Serial.println("Enabling output");
  #endif // DEBUG_LOW_LEVEL
  digitalWrite(ring_outputEnable, LOW); // enable output
  //delay(10);
  
  // all lights should be off
  #ifdef DEBUG_LOW_LEVEL
  Serial.println("Exiting LEDring_initialise()\n");
  #endif // DEBUG_LOW_LEVEL
}

// LEDring_set(int score)
//     this function lights the corresponding number of segments in the led
//     ring depending on the score passed as an argument
void LEDring_set(int score) {
    #ifdef DEBUG_LOW_LEVEL
    Serial.println("\nEntering LEDring_set()");
    #endif // DEBUG_LOW_LEVEL
    #ifdef DEBUG_LOW_LEVEL
    Serial.print("Score: ");
    Serial.println(score);
    #endif // DEBUG_LOW_LEVEL
    // map measured value [0, 1024] to number of segments to light up [0, numOfSegments]
    int numSegments = 0;
    numSegments = map(score, minAnalogInput, maxAnalogInput, 0, numOfSegments);
    #ifdef DEBUG_LOW_LEVEL
    Serial.print("Number of segments to be lit up: ");
    Serial.println(numSegments);
    #endif // DEBUG_LOW_LEVEL

    // map number of segments to light up to short data
    // byte data = 0x00; this was used on 28/12/15
    short data = 0x0000;

    // determine the output pattern based on the mapped score
    switch(numSegments) {
      case 0:  data = 0x0000; break;
      case 1:  data = 0x0001; break;
      case 2:  data = 0x0003; break;
      case 3:  data = 0x0007; break;
      case 4:  data = 0x000F; break;
      case 5:  data = 0x001F; break;
      case 6:  data = 0x003F; break;
      case 7:  data = 0x007F; break;
      case 8:  data = 0x00FF; break;
      case 9:  data = 0x01FF; break;
      case 10: data = 0x03FF; break;
      case 11: data = 0x07FF; break;
      case 12: data = 0x0FFF; break;
      case 13: data = 0x1FFF; break;
      case 14: data = 0x3FFF; break;
      case 15: data = 0x7FFF; break;
      case 16: data = 0xFFFF; break;
      default: data = 0x0000; break;
    }

    // write the pattern to the led ring
    #ifdef DEBUG_LOW_LEVEL
    Serial.print("Calling LEDring_singleSet() with data = ");
    Serial.println(data, BIN);
    #endif // DEBUG_LOW_LEVEL
    LEDring_singleSet(data);
    #ifdef DEBUG_LOW_LEVEL
    Serial.println("Exiting LEDring_set()\n");
    #endif // DEBUG_LOW_LEVEL
}

// LEDring_singleSet(short pattern)
//     this function lights the corresponding segments of the led ring depending 
//     on the specific pattern passed as an argument
void LEDring_singleSet( short pattern ) {
    #ifdef DEBUG_LOW_LEVEL
    Serial.println("\nEntering LEDring_singleSet()");
    #endif // DEBUG_HIGH_LEVEL

    #ifdef DEBUG_LOW_LEVEL
    Serial.print("pattern = ");
    Serial.println(pattern, BIN);
    #endif // DEBUG_LOW_LEVEL
    
    // XOR the pattern with 1's to invert the pattern (since it is common anode), ***not required because transistor array inverts signal***
    //pattern = 0xFFFF^pattern;
  
    // write the data to the led ring by shifting the data out
    #ifdef DEBUG_LOW_LEVEL
    Serial.println("Shifting out pattern");
    #endif // DEBUG_LOW_LEVEL
    
    digitalWrite(ring_latchPin, LOW); // disable latching, values stored in shift registers will not be displayed until latchPin written HIGH
    int i = 0;
    for(int i = (numOfSegments-1); i >= 0; i--){
      //Serial.println("Entered for loop");
      #ifdef DEBUG_LOW_LEVEL
      Serial.print("R");
      Serial.print(15-i);
      Serial.print(": ");
      Serial.println(bitRead(pattern, i));
      Serial.println("");
      #endif // DEBUG_LOW_LEVEL
      
      digitalWrite(ring_dataPin, bitRead(pattern, i));
      pulsePin(ring_clkPin);
    }

    digitalWrite(ring_latchPin, HIGH); // move values in storage registers to outputs

    #ifdef DEBUG_LOW_LEVEL
    Serial.println("Exiting LEDing_singleSet()\n");
    #endif // DEBUG_LOW_LEVEL
}

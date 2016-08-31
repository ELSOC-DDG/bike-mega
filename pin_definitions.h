/*  Pin_Definitions.h
 *   
 *   This file contains all pin definitions for the ELSOC Design and Development Group Bike. 
 *   
 *   Change Log: 
 *      17th September (JL)
 *          - added 'modeBtnInterrupt'
 *
 *      27th August 2015 (JL) 
 *          - clean up
 *          
 *      21st August 2015 (JSS)
 *          - clean up
 *          - add 'sensorPin' for testing purposes
 *          
 *      16th August 2015 (JSS)
 *          - created file with initial definitions
 */

#ifndef PIN_DEFINTIONS_H
#define PIN_DEFINITIONS_H

#define DEBUG_HIGH_LEVEL
#ifdef DEBUG_HIGH_LEVEL
  //#define DEBUG_LOW_LEVEL
  #define WAIT_FOR_ENTER // comment out if you want the program to run through without stopping to wait for you to press enter
#endif // DEBUG_HIGH_LEVEL


/***********************************
 *   LED Ring - Shift Registers    *
 ***********************************/
#define ring_masterClear 22    // SRCLR (active low)
#define ring_clkPin     23      // SRCLK
#define ring_latchPin   24       // RCLK
#define ring_outputEnable 25   // OE (active low)
#define ring_dataPin    26      // SER

/***********************************
 *      Seven Segment Display      *
 ***********************************/

// blanking pins
#define BLpin0          43
#define BLpin1          44
#define BLpin2          45

// 
#define ABCDpin0        42
#define ABCDpin1        40
#define ABCDpin2        39
#define ABCDpin3        41


#define LDpin0          36
#define LDpin1          38
#define LDpin2          37

/***********************************
 *             Sensor              *
 ***********************************/
//#define sensorPin       A0
#define voltagePin      A1
#define currentPin      A0

/***********************************
 *              Button             *
 ***********************************/
#define startBtnInt     1 // pin 3
#define modeBtnInt      0 // pin 2

/***********************************
 *              PWM                *
 ***********************************/
#define topLightPWM 5
#define voltageMotor A7

#endif

/*  sevenSeg_functions.h
 *   
 *   This file contains all definitions and function prototypes for the seven segment display
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

#ifndef SEVENSEG_FUNCTIONS_H
#define SEVENSEG_FUNCTIONS_H

// include all necessary local header files
#include "pin_definitions.h"

/***********************************
 *            Constants            *
 ***********************************/
#define PH              0
#define numOfDigits     3

/***********************************
 *       Function Prototypes       *
 ***********************************/
// initialisation functions
void sevenSeg_initialise();

// setting functions
bool sevenSeg_set(int num);

// blanking functions
void sevenSeg_blankPin(int pin);
void sevenSeg_blankAll();
void sevenSeg_unblankAll();
void sevenSeg_unblankPin(int pin);

#endif

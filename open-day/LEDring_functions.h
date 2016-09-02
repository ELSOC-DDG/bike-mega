/*  LEDring_functions.h
 *   
 *   This file contains all definitions and function prototypes for the led ring
 *   
 *   Change Log: 
 *      28th December 2015
 *          - changed numOfSegments to 16
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

#ifndef LEDRING_FUNCTIONS_H
#define LEDRING_FUNCTIONS_H

// include all necessary local header files
#include "bike.h"

/***********************************
 *            Constants            *
 ***********************************/
#define numOfSegments     16
#define minAnalogInput    0
#define maxAnalogInput    200

/***********************************
 *       Function Prototypes       *
 ***********************************/
// initialisation functions
void LEDring_initialise();

// setting functions
void LEDring_set(int score);
void LEDring_singleSet(short pattern);

#endif

/*  mode_functions.h
 *   
 *   This file contains all function prototypes and constant definitions for the different modes.
 *   
 *   Change Log: 
 *
 *      28th August 2015 (JL)
 *          - clean up
 *          - added idleMode
 *          - created extern variables
 *          
 *      25th August 2015 (JSS)
 *          - created file
 */

#ifndef MODE_FUNCTIONS_H
#define MODE_FUNCTIONS_H

// include all necessary local header files
#include "bike.h"

/***********************************
 *            Constants            *
 ***********************************/
#define ARRAY_LENGTH  10

/***********************************
 *            Variables            *
 ***********************************/
extern int highScore;
volatile extern bool startBtnPressed;

/***********************************
 *       Function Prototypes       *
 ***********************************/
void startSequence();
void idleMode();
void displayFinalScore(int score, int rank);
int updateHighScoreTable(int score, int score_array[]);

#endif

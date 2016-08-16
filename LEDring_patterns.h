/*  LEDring_patterns.h
 *   
 *   This file contains all pattern definitions for the LED ring. All patterns are stored in a short array.
 *   
 *   Change Log: 
 *      28th 
 *      28th August 2015 (JL)
 *          - clean up
 *          - changed binary values to hexadecimal notation
 *          
 *      27th August 2015 (JL)
 *          - added onebyone pattern
 *          - added twobytwo pattern
 *          
 *      16th August 2015 (JSS)
 *          - created file
 */

#ifndef LEDRING_PATTERNS_H
#define LEDRING_PATTERNS_H

// include all necessary header files
#include <Arduino.h>
#include "LEDring_functions.h"

// define the patterns in an array of shorts (hexadecimal notation)

short pattern_onebyone[numOfSegments] = {0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000};
short pattern_twobytwo[numOfSegments] = {0x0003, 0x0006, 0x000C, 0x0018, 0x0030, 0x0060, 0x00C0, 0x0180, 0x0300, 0x0600, 0x0C00, 0x1800, 0x3000, 0x6000, 0xC000, 0x8001};
short pattern_mike[numOfSegments] =     {0x8080, 0x8888, 0xC8C8, 0xC9C9, 0xE9E9, 0xEBEB, 0xFBFB, 0xFFFF, 0x8080, 0x8888, 0xC8C8, 0xC9C9, 0xE9E9, 0xEBEB, 0xFBFB, 0xFFFF};
short pattern_george[numOfSegments] =   {0x8001, 0xC003, 0xE007, 0xF00F, 0xF81F, 0xFC3F, 0xFE7F, 0xFFFF, 0xFE7F, 0xFC3F, 0xF81F, 0xF00F, 0xE007, 0xC003, 0x8001, 0x0000};
short pattern_fred[numOfSegments] =     {0x0808, 0x0C0C, 0x0E0E, 0x0F0F, 0x8F8F, 0xCFCF, 0xEFEF, 0xFFFF, 0xF7F7, 0xF3F3, 0xF1F1, 0xF0F0, 0x7070, 0x3030, 0x1010, 0x0000};
short pattern_harry[numOfSegments] =    {0x4242, 0x8484, 0x0909, 0x1212, 0x2424, 0x4848, 0x9090, 0x2121, 0x4242, 0x8484, 0x0909, 0x1212, 0x2424, 0x4848, 0x9090, 0x2121};
short pattern_paul[numOfSegments] =     {0x8181, 0xC3C3, 0xE7E7, 0xFFFF, 0xE7E7, 0xC3C3, 0x8181, 0x0000, 0x8181, 0xC3C3, 0xE7E7, 0xFFFF, 0xE7E7, 0xC3C3, 0x8181, 0x0000};
short pattern_peter[numOfSegments] =    {0x0FF0, 0x0FF0, 0x0FF0, 0x0FF0, 0xF00F, 0xF00F, 0xF00F, 0xF00F, 0xFF00, 0xFF00, 0xFF00, 0xFF00, 0x00FF, 0x00FF, 0x00FF, 0x00FF};
short pattern_tom[numOfSegments] =      {0x0400, 0x0080, 0x4000, 0x0020, 0x0004, 0x0002, 0x0200, 0x8000, 0x0010, 0x0008, 0x1000, 0x0100, 0x0800, 0x2000, 0x0040, 0x0001};
short pattern_pacMan[numOfSegments] =   {0xFFFF, 0xE7FF, 0xC3FF, 0xE7FF, 0xFFFF, 0xE7FF, 0xC3FF, 0xE7FF, 0xFFFF, 0xE7FF, 0xC3FF, 0xE7FF, 0xFFFF, 0xE7FF, 0xC3FF, 0xE7FF};
#endif

#ifndef TicTacToe_h
#define TicTacToe_h
//###############################################################################
//# TicTacToe                                                                   #
//###############################################################################
//#    Copyright 2017 Dirk Heisswolf                                            #
//#    This file is part of the TicTacToe project.                              #
//#                                                                             #
//#    TicTacToe is free software: you can redistribute it and/or modify        #
//#    it under the terms of the GNU General Public License as published by     #
//#    the Free Software Foundation, either version 3 of the License, or        #
//#    (at your option) any later version.                                      #
//#                                                                             #
//#    TicTacToe is distributed in the hope that it will be useful,             #
//#    but WITHOUT ANY WARRANTY; without even the implied warranty of           #
//#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            #
//#    GNU General Public License for more details.                             #
//#                                                                             #
//#    You should have received a copy of the GNU General Public License        #
//#    along with TicTacToe.  If not, see <http://www.gnu.org/licenses/>.       #
//###############################################################################
//# Version History:                                                            #
//#    March 30, 2017                                                           #
//#      - Initial release                                                      #
//###############################################################################

// Target Check
//==============
#if defined(ARDUINO_AVR_UNO)
#else
#error Unsupported hardware
#endif

// Constants
//===========
#define FRAMERATE  120              //refresh rate [fps]

#define COMPUTERDELAY  500          //computer thinking break

// Type definitions
//==================
// A|B|C     15     8 7      0
// -+-+-    +--------+--------+ 
// D|E|F => |-------I|HGFEDCBA| 
// -+-+-    +--------+--------+ 
// G|H|I
typedef unsigned int fields;

typedef enum {greenTurn, redTurn} turn;

// Variables                                
//===========                                
//Display control
fields  red        = 0; //red fields on the board 
fields  green      = 0; //green fields on the board
fields  scanRed    = 0; //red fields, highligted as selectable 
fields  scanGreen  = 0; //green fields, highligted as selectable
fields  blinkRed   = 0; //red fields, highligted as winning move
fields  blinkGreen = 0; //green fields, highligted as winning move
//Custom animation routine
void (*dispAnimator)(fields *red, fields *green) = NULL;//function pointer
//Game settings
bool greenIsHuman  = true;
bool redIsHuman    = false;

// Inline assembler
//==================
//Wait for any interrupt
#define WAIT_FOR_INTERRUPT()                     \
do {                                             \
  __asm__ __volatile__ ( "sei" "\n\t" :: );      \
  __asm__ __volatile__ ( "sleep" "\n\t" :: );    \
} while(0)

#define NOP()                                    \
do {                                             \
  __asm__ __volatile__ ( "nop" "\n\t" :: );      \
  __asm__ __volatile__ ( "nop" "\n\t" :: );      \
} while(0)

#endif

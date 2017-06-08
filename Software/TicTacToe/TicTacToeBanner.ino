//###############################################################################
//# TicTacToe - Animation Routines                                              #
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
//#    March 24, 2017                                                           #
//#      - Initial release                                                      #
//###############################################################################

#include <Arduino.h>
#include <avr/pgmspace.h>
#include "TicTacToe.h"

// Constants
//===========
//.@@.@.@.@@@.@@@..@@.@@@....@...@..@@@.@@@....-------+
//@...@@@.@.@.@.@..@..@@....@...@@@.@@@.@@.....----+  |
//.@@.@.@.@@@.@@@.@@..@@@....@@.@.@.@.@.@@@....-+  |  |
//                                              V  V  V 
const byte banner[] PROGMEM =               {0b00001000,//.@.
				             0b01000001,//@.@
				             0b01000001,//@.@
				             0b00000000,//...
				             0b01001001,//@@@
				             0b00001000,//.@.
				             0b01001001,//@@@
				             0b00000000,//...
				             0b01001001,//@@@
				             0b01000001,//@.@
				             0b01001001,//@@@
				             0b00000000,//...
				             0b01001001,//@@@
				             0b01000001,//@.@
				             0b01001001,//@@@
				             0b00000000,//...
				             0b01000000,//@..
				             0b01001001,//@@@
				             0b00000001,//..@
				             0b00000000,//...
				             0b01001001,//@@@
				             0b01001001,//@@@
				             0b01000001,//@.@
				             0b00000000,//...
				             0b00000000,//...
				             0b00000000,//...
				             0b00001000,//.@.
				             0b01000001,//@.@
				             0b01000000,//@..
				             0b00000000,//...
				             0b01001000,//@@.
				             0b00001001,//.@@
				             0b01001000,//@@.
				             0b00000000,//...
				             0b01001001,//@@@
				             0b00001001,//.@@
				             0b01001001,//@@@
				             0b00000000,//...
				             0b01001001,//@@@
				             0b01001001,//@@@
				             0b01000001,//@.@
				             0b00000000,//...
				             0b00000000,//...
				             0b00000000,//...
				             0b10000000};  


//@@@.@..@@.@.@....@...@..@@@.@@@.....----------------+
//@@@.@.@...@@....@...@@@.@@@.@@......-------------+  |
//@...@..@@.@.@....@@.@.@.@.@.@@@.....----------+  |  |
//                                              V  V  V 
//const byte banner[] PROGMEM =               {0b01001001,//@@@
//				               0b00001001,//.@@
//				               0b00001001,//.@@
//				               0b00000000,//...
//				               0b01001001,//@@@
//				               0b00000000,//...
//				               0b00001000,//.@.
//				               0b01000001,//@.@
//				               0b01000001,//@.@
//				               0b00000000,//...
//				               0b01001001,//@@@
//				               0b00001000,//.@.
//				               0b01000001,//@.@
//				               0b00000000,//...
//				               0b00000000,//...
//				               0b00000000,//...
//				               0b00001000,//.@.
//				               0b01000001,//@.@
//				               0b01000000,//@..
//				               0b00000000,//...
//				               0b01001000,//@@.
//				               0b00001001,//.@@
//				               0b01001000,//@@.
//				               0b00000000,//...
//				               0b01001001,//@@@
//				               0b00001001,//.@@
//				               0b01001001,//@@@
//				               0b00000000,//...
//				               0b01001001,//@@@
//				               0b01001001,//@@@
//				               0b01000001,//@.@
//		                               0b00000000,//...
//				               0b00000000,//...
//				               0b00000000,//...
//				               0b10000000};  
					     
// Variables                                
//===========
byte bannerFrameCount = 0;
byte bannerIndex      = 0;

// Banner control
//================
//Start showing banner
// args:   none
// result: nons
void bannerStart() {
  bannerFrameCount = FRAMERATE/4;
  bannerIndex      = 0;
  dispAnimator     = bannerAnimator; 
}

//Stop showing banner
// args:   none
// result: nons
void bannerStop() {
  dispAnimator = NULL;
}

// Animator
//==========
void bannerAnimator(fields *redBuf, fields *greenBuf) {
  byte newColumn;
  
  if (!--bannerFrameCount) {                                   //execute every 0.25sec
    bannerFrameCount = FRAMERATE/4;                            //reset frame counter
    						               
    newColumn = pgm_read_byte(&banner[bannerIndex++]);         //read banner content
    if (newColumn & 0x80) {                                    //end of banner reached                              
       bannerIndex = 0;
       newColumn    &= 0x7F;
    }

    *redBuf   = ((*redBuf   & 0x01B6) >> 1) | (newColumn <<2); //update red buffer
    *greenBuf = ((*greenBuf & 0x01B6) >> 1) | (newColumn <<2); //update green buffer
  }
}


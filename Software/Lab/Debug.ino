//###############################################################################
//# TicTacToe - Hardware Test                                                   #
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
//# This sketch is a basic hardware test for the TicTacToe shield. Coming out   #
//# of reset, all red LEDs are lit. The green ones are cleared. Presseng a      #
//# button will toggle the associated the associated LEDs.                      #
//#                                                                             #
//###############################################################################
//# Version History:                                                            #
//#    June 8, 2017                                                             #
//#      - Initial release                                                      #
//###############################################################################

#include "TicTacToe.h"

// Variables
//===========

// Input functions
//=================
void debugModifyInput() {
  fields input;
  
  input = getKey();                                //get keypad input
  if        (!(red & input) && !(green & input)) { //empty field selected
    red   |=  input;
  } else if ( (red & input) && !(green & input)) { //red field selected
    red   &= ~input;
    green |=  input;
  } else if (!(red & input) &&  (green & input)) { //green field selected
    green &= ~input;
  } else {                                         //clear field if double selected
    red   &= ~input;
    green &= ~input;
  }
}

// Output functions
//==================
//Print vertival line
void debugVl() {
  Serial.print("|");
} 

//Print horizontal line
void debugHl() {
  Serial.print("-+-+-");
} 

//Print seperator
void debugSep() {
  Serial.print("    ");
} 

//Print arrow
void debugArrow() {
  Serial.print(" => ");
} 

//Print input fields
void debugRb(fields sel) {
  if        (!(red & sel) && !(green & sel)) {
    Serial.print(" ");
  } else if ( (red & sel) && !(green & sel)) {
    Serial.print("R");
  } else if (!(red & sel) &&  (green & sel)) {
    Serial.print("G");
  } else {
    Serial.print("?");
  }
}

//Print output fields
void debugRes(fields sel) {
  if (result & sel) {
    Serial.print("*");
  } else {
    Serial.print(" ");
  }
}

//Print result
void debugPrintResult() {
  //Debug output
  debugRb(0b000000001);  //first row
  debugVl();		 //
  debugRb(0b000000010);	 //
  debugVl();		 //
  debugRb(0b000000100);	 //
  debugSep();		 //
  debugRes(0b000000001); //
  debugVl();		 //
  debugRes(0b000000010); //
  debugVl();		 //
  debugRes(0b000000100); //
  Serial.println();      //
  debugHl;		 //horizontal lines
  debugSep();		 //
  debugHl();		 //
  Serial.println();	 //
  debugRb(0b000001000);	 //second row
  debugVl();		 //
  debugRb(0b000010000);	 //
  debugVl();		 //
  debugRb(0b000100000);	 //
  debugArrow();		 //
  debugRes(0b000001000); //
  debugVl();		 //
  debugRes(0b000010000); //
  debugVl();		 //
  debugRes(0b000100000); //
  Serial.println();	 //
  debugHl;		 //horizontal lines
  debugSep();		 //
  debugHl();		 //
  Serial.println();	 //
  debugRb(0b001000000);	 //third row
  debugVl();		 //
  debugRb(0b010000000);	 //
  debugVl();		 //
  debugRb(0b100000000);	 //
  debugSep();		 //
  debugRes(0b001000000); //
  debugVl();		 //
  debugRes(0b010000000); //
  debugVl();		 //
  debugRes(0b100000000); //
  Serial.println();      //
  Serial.println();      //
}

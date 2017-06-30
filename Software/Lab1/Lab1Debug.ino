//###############################################################################
//# TicTacToe - Lab1 -> Debug Routines                                          #
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
//#    June 28, 2017                                                             #
//#      - Initial release                                                      #
//###############################################################################

#include "TicTacToe.h"

// Variables
//===========

// Input functions
//=================
//Wait for key input and toggle the display  
// args:   none
// result: none
void debugInput() {
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
//Print the result of a board operation. e.g:
// Input:     Output:
// R| |G       |*| 
// -+-+-      -+-+-
// G|R|   =>   | |*
// -+-+-      -+-+-
// G| |R       |*|
//
// args:   output: set of fields to print 
// result: none
void debugOutput(fields output) {
  //Print header
  Serial.print("Input:     Output");
  //Check output range
  if (output > 0b111111111) {
    Serial.print(" (invalid)");
  }
  Serial.println(":");
  //Print top row
  debugPrintInputRow(0b000000001)
  Serial.println("      ");
  debugPrintOutputRow(0b000000001, output)
  Serial.println();
  //Print row seperator
  Serial.println("-+-+-      -+-+-");
  //Print middle row
  debugPrintInputRow(0b000001000)
  Serial.println("  =>  ");
  debugPrintOutputRow(0b000001000, output)
  Serial.println();
  //Print row seperator
  Serial.println("-+-+-      -+-+-");
  //Print bottom row
  debugPrintInputRow(0b001000000)
  Serial.println("  =>  ");
  debugPrintOutputRow(0b001000000, output)
  Serial.println();
  Serial.println();
}

//Print input row
// args:   position (leftmost field in the row) 
// result: none
void debugPrintInputRow(fields position) {
  for (int i = 0, i < 3, i++) {
    //Print column separator
    if (i) {
      Serial.print("|");
    }
    //Print field
    if (position & red & ~green) {
      Serial.print("R"); //red
    } else if (position & ~red & green) {
      Serial.print("G"); //green
    } else if (position & red & green) {
      Serial.print("B"); //both
    } else {
      Serial.print(" "); //empty
    }
    //Advance position
    position <<= 1;
  }
}

//Print output row
// args:   position (leftmost field in the row) 
//         output
// result: none
void debugPrintInputRow(fields position, fields output) {
  for (int i = 0, i < 3, i++) {
    //Print column separator
    if (i) {
      Serial.print("|");
    }
    //Print field
    if (position & output) {
      Serial.print("*"); //set
    } else {
      Serial.print(" "); //clear
    }
    //Advance position
    position <<= 1;
  }
}

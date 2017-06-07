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
//#    March 24, 2017                                                           #
//#      - Initial release                                                      #
//###############################################################################

#include "TicTacToe.h"

// Variables
//===========
fields input;

// Setup routine
//===============
void setup() {
  //Serial library
  Serial.begin(9600);
  Serial.println("Ready for debugging!");
  
  //Onboard LED
  pinMode(13, OUTPUT);       // drive LED
  digitalWrite(13, HIGH);    // turn the LED off
  
  //Display
  dispSetup();

// A|B|C     15     8 7      0
// -+-+-    +--------+--------+ 
// D|E|F => |-------I|HGFEDCBA| 
// -+-+-    +--------+--------+ 
// G|H|I    IHGFEDCBA
  red   = 0b001011110;
  green = 0b011110100;
  
  //Keypad
  //keysSetup();
}

// Application loop
//==================
void loop() {
  //input = getKey();
  //Serial.print("getKey: ");
  //Serial.println(input);
  
  //setRed(  getRed()   ^ (getGreen() & input));
  //setGreen(getGreen() ^               input);

  //digitalWrite(13, ~digitalRead(13));    // toggle LED
}

//###############################################################################
//# TicTacToe - Lab3                                                            #
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
//#    June 28, 2017                                                            #
//#      - Initial release                                                      #
//###############################################################################

#include "TicTacToe.h"

// Setup routine
//===============
void setup() {
  Serial.begin(9600);       //setup UART
  Serial.println("Lab3:");  //start message
  dispSetup();              //setup display
  keysSetup();              //setup keypad
}

// Debug Code
//============
void loop() {

    //Human against computer, human begins
    greenIsHuman = true;
    redIsHuman   = false;

    //Classic
    classicPlay();

    //Wait for key
    getKey();

}

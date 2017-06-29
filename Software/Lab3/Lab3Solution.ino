//###############################################################################
//# TicTacToe - Lab3 -> Solution                                                #
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

// classicPlay()
//===============
//Play the classic game
// args:   none 
// result: none
void classicPlay () {
  //Game loop
  while (1) {

    //Green move
    //==========
    green |= classicTurn(greenTurn);          //place green piece

    //Check if green won, otherwise check for a tie
    if (blinkGreen = completedRowsIn(green)) {//check if green has won
      break;
    } else if ((red|green) == 0b111111111) {  //check for tie
      blinkRed   = 0b111111111;               //flash all LEDs
      blinkGreen = 0b111111111;
      break; 
    }
  
    //Red move
    //========
    red |= classicTurn(redTurn);              //place red piece

    //Check if red won, otherwise check for a tie
    if (blinkRed = completedRowsIn(red)) {    //check if green has won
      break;
    }
  }
}

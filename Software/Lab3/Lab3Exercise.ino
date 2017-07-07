//###############################################################################
//# TicTacToe - Lab3 -> Exercise                                                #
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
    green = green | classicTurn(greenTurn);   //place green piece

    //Check if green won, otherwise check for a tie
 
       //...your code... (Tip: use "break;" to exit the while-loop)
   
    //Red move
    //========
    red = red | classicTurn(redTurn);         //place red piece

    //Check if red won

       //...your code... (Tip: use "break;" to exit the while-loop)

  }
}

// classicTurn()
//===============
//One turn of the classic game
// args:   color
// result: new mark to be placed
fields classicTurn(turn currentTurn) { 
  if ((currentTurn == greenTurn) ? greenIsHuman : redIsHuman) {
    return classicHumanTurn(currentTurn);
  } else {
    return classicComputerTurn(currentTurn);
  }
}

// classicHumanTurn()
//====================
//Human turn in the classic game
// args:   color
fields classicHumanTurn(turn currentTurn) {
  fields free   = inverseOf(red | green);
  fields input;

  //Highlight free fields
  if (currentTurn == greenTurn) {
    scanGreen = free;
  } else {
    scanRed   = free;
  } 

  //Get valid input
  do {
    input = getKey();

  } while (!(input & free));

  //Clear highlights
  scanGreen = 0;
  scanRed   = 0;

  return input;
}

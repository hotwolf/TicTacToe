//###############################################################################
//# TicTacToe - Classic Game Play                                               #
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
//# Rules:                                                                      #
//# ======                                                                      #
//# The green player begins. Alternately each player places one mark on an      #
//# empty field on the board. The player who first manages to place three marks #
//# in one row (horizontal, vertical, or dialonal) wins the game.               #
//#                                                                             #
//###############################################################################
//# Version History:                                                            #
//#    April 6, 2017                                                            #
//#      - Initial release                                                      #
//###############################################################################

#include "TicTacToe.h"

// Play
//======
//Play the classic game
// args:   none 
// result: none
void classicPlay () {
  //Game loop
  while (1) {

    //Green move
    //==========
    green |= classicTurn(greenTurn);          //place green piece
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
    if (blinkRed = completedRowsIn(red)) {    //check if green has won
      break;
    }
  }
}
   
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
    
//Computer turn in the classic game
// args:   color
fields classicComputerTurn(turn currentTurn) {
  fields player   = (currentTurn == greenTurn) ? green : red;
  fields opponent = (currentTurn == greenTurn) ? red   : green;
  fields free     = inverseOf(red | green);
  fields options;

  //Complete a row if possible
  if (options = completingDrops(player, opponent)) {
    return oneOf(options);
  }

  //Prevent the opponent from completing a row
  if (options = completingDrops(opponent, player)) {
    return oneOf(options);
  }

  //Occupy the center if possible
  if (0b000010000 & free) {
    return 0b000010000;
  }

  //Occupy a corner if possible
  if (options = (0b101000101 & free)) {
    return oneOf(options);
  }

   //Pick a random field
    return oneOf(free);
}

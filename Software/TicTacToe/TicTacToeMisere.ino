//###############################################################################
//# TicTacToe - Misere Rules                                                    #
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
//# empty field on the board. The player who places three marks in one row      #
//# (horizontal, vertical, or dialonal) looses the game.                        #
//#                                                                             #
//###############################################################################
//# Version History:                                                            #
//#    April 6, 2017                                                            #
//#      - Initial release                                                      #
//###############################################################################

#include "TicTacToe.h"

// Play
//======
//Play Misere
// args:   greenIsHuman: true if green player is human
//         redIsHuman:   true if red player is human  
// result: none
void miserePlay() {
  //Game loop
  while (1) {

    //Green move
    //==========
    green |= misereTurn(greenTurn);      //place green piece
    if (blinkRed = completeRows(green)) {//check if green has won
      break;
    } else if ((red|green) == 0b111111111) { //check for tie
      blinkRed   = 0b111111111;              //flash all LEDs
      blinkGreen = 0b111111111;
      break;
    }
  
    //Red move
    //========
    red |= misereTurn(redTurn);                  //place red piece
    if (blinkGreen = completeRows(red)) {    //check if green has won
      break;
    } else if ((red|green) == 0b111111111) { //check for tie
      blinkRed   = 0b111111111;              //flash all LEDs
      blinkGreen = 0b111111111;
      break;
    }
  }

}

//One turn of the Misere game
// args:   color
// result: new mark to be placed
fields misereTurn(turn currentTurn) { 
  if ((currentTurn == greenTurn) ? greenIsHuman : redIsHuman) {
    return classicHumanTurn(currentTurn);
  } else {
    return misereComputerTurn(currentTurn);
  }
}

//Computer turn in the classic game
// args:   color
fields misereComputerTurn(turn currentTurn) {
  fields player   = (currentTurn == greenTurn) ? green : red;
  fields opponent = (currentTurn == greenTurn) ? red   : green;
  fields options  = inverseOf(red | green);
  fields strategicMoves;
  
  Serial.println("misereComputerTurn!");
  Serial.print("red: ");
  Serial.println(red, BIN);
  Serial.print("green: ");
  Serial.println(green, BIN);
  
  //Avoid completing a row
  strategicMoves = completingDrops(player, opponent);
  if (options & ~strategicMoves) {
    options &= ~strategicMoves;
  }
    
  //Don't block the opponent from completing a row
  strategicMoves = completingDrops(opponent, player);
  if (options & ~strategicMoves) {
    options &= ~strategicMoves;
  }
  
  //Avoid the center
  if (options & 0b111101111) {
    options &= 0b111101111;
  }

  //Avoid the cornere
  if (options & 0b010111010) {
    options &= 0b010111010;
  }

  //Pick one of the remaining options
  Serial.println("random");
  return oneOf(options);
}








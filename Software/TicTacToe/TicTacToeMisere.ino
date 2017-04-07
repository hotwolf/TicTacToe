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
//# The green player begins. Alternatelr each player places one mark on an      #
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
//Play Misere
// args:   greenIsHuman: true if green player is human
//         redIsHuman:   true if red player is human  
// result: none
void playMisere (bool greenIsHuman, bool redIsHuman) {
  //Board
  fields red   = 0b000000000;  //set of red marks on the board
  fields green = 0b000000000;  //set of green marks on the board
  
  //Game loop
  while (1) {

    //Green move
    //==========
    green |= makeMoveMisere(greenIsHuman, green, red, red , green);

    //Check board
    //===========
    if (checkBoardMisere(red, green)) {
      break;
    }

    //Red move
    //========
    red |= makeMoveMisere(redIsHuman, red, green, red , green);

    //Check board
    //===========
    if (checkBoardMisere(red, green)) {
      break;
    }
  }

  //Wait for input to continue
  getKey();
}
   
//Make one move in the classic game
// args:   isHuman:  true if current player is human
//         player:   marks of current player
//         opponent: marks of the opponent 
//         red:      all red marks
//         green:    all green marks
// result: new mark to be placed
fields makeMoveMisere(bool isHuman, fields player, fields opponent, fields red , fields green) {
  fields remainingMoves = invert(red|green); //pick the best one out of these fields
  fields tmp            = 0b000000000;       //temporary storage
  
  if (isHuman) {
    //Wait for input
    return selectField(red, green, invert(red|green)); 
  } else {
    //Exclude loosing moves if possible
    tmp = remainingMoves & invert(findCompletableRows(player, opponent));
    if (tmp) {
      remainingMoves = tmp;               //continue selection
    }
    //Keep opponent's completable rows open
    tmp = remainingMoves & invert(findCompletableRows(opponent, player));
    if (tmp) {
      remainingMoves = tmp;               //continue selection
    }
    //Don't select the center 
    tmp = remainingMoves & 0b111101111;
    if (tmp) {
      remainingMoves = tmp;               //continue selection
    }
    //return one of the remaining fields
    return randomField(remainingMoves);
  }
}
  
//Check the status of the board
// args:   red:   all red marks
//         green: all green marks
// result: True if the game is over
bool checkBoardMisere(fields red , fields green) {
  fields tmp   = 0b000000000;  //temporary storage

  //Check if green won
  if (findCompletedRows(red)) {
    //Signal victory
    blink(red, green, green);
    return true;
  }

  //Check if red won
  if (findCompletedRows(green)) {
    //Signal victory
    blink(red, green, red);
    return true;
  }

  //Check for a tie
  if ((red|green) == 0x111111111) {
    return true;
  }
    
  return false;
}

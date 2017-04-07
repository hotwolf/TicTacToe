//###############################################################################
//# TicTacToe - Achi Rules                                                      #
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
//Play the classic game
// args:   greenIsHuman: true if green player is human
//         redIsHuman:   true if red player is human  
// result: none
void playAchi (bool greenIsHuman, bool redIsHuman) {
  //Board
  fields red   = 0b000000000;  //set of red marks on the board
  fields green = 0b000000000;  //set of green marks on the board
  
  //Game loop
  while (1) {

    //Green move
    //==========
    green |= makeMoveAchi(greenIsHuman, green, red, red , green);

    //Check board
    //===========
    if (checkBoardAchi(red, green)) {
      break;
    }

    //Red move
    //========
    red |= makeMoveAchi(redIsHuman, red, green, red , green);

    //Check board
    //===========
    if (checkBoardAchi(red, green)) {
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
fields makeMoveAchi(bool isHuman, fields player, fields opponent, fields red , fields green) {
  fields tmp   = 0b000000000;  //temporary storage

  //Use classic rules for the first eight moves
  if (countFields(red|green) < 8) {
    return makeMoveClassic(isHuman, player, opponent, red, green);
  } else {
    
    

    

  
  if (isHuman) {
    //Wait for input
    return selectField(red, green, invert(red|green)); 
  } else {
    //Try to complete one row
    tmp = findCompletableRows(player, opponent);
    if (tmp) {
      return randomField(tmp);
    } else {
      //Prevent opponent from completing one row
      tmp = findCompletableRows(opponent, player);
      if (tmp) {
	return randomField(tmp);
      } else {
	//Occupy the center if possible
	if (isCenterFree(red|green)) {
	  return 0b000010000;
	} else {
	  //Make random move
	  return randomField(invert(red|green));
	}
      }
    }   
  }
}
  
//Check the status of the board
// args:   red:   all red marks
//         green: all green marks
// result: True if the game is over
bool checkBoardAchi(fields red , fields green) {
  fields tmp   = 0b000000000;  //temporary storage

  //Check if green won
  tmp = findCompletedRows(green);
  if (tmp) {
    //Signal victory
    blink(red, green, tmp);
    return true;
  }

  //Check if red won
  tmp = findCompletedRows(red);
  if (tmp) {
    //Signal victory
    blink(red, green, tmp);
    return true;
  }
  return false;
}

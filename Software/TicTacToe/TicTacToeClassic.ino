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
// args:   greenIsHuman: true if green player is human
//         redIsHuman:   true if red player is human  
// result: none
void playClassic (bool greenIsHuman, bool redIsHuman) {
  //Board
  fields red   = 0b000000000;  //set of red marks on the board
  fields green = 0b000000000;  //set of green marks on the board
  
  //Game loop
  while (1) {

    //Green move
    //==========
    green |= makeMoveClassic(greenIsHuman, green, red, red , green);
    noAnim(red, green);

    //Check board
    //===========
    if (checkBoardClassic(red, green)) {
      break;
    }

    //Red move
    //========
    red |= makeMoveClassic(redIsHuman, red, green, red , green);
    noAnim(red, green);

    //Check board
    //===========
    if (checkBoardClassic(red, green)) {
      break;
    }
  }

  //Wait for input to continue and clear the sisplay
  getKey();
  noAnim(0b000000000, 0b000000000);
}
   
//Make one move in the classic game
// args:   isHuman:  true if current player is human
//         player:   marks of current player
//         opponent: marks of the opponent 
//         red:      all red marks
//         green:    all green marks
// result: new mark to be placed
fields makeMoveClassic(bool isHuman, fields player, fields opponent, fields red , fields green) {
  fields tmp   = 0b000000000;  //temporary storage
    
  if (isHuman) {
    //Wait for input
    return selectField(red, green, inverseOf(red|green)); 
  } else {
    //Try to complete one row
    tmp = completingDrops(player, opponent);
    if (tmp) {
      return oneOf(tmp);
    } else {
      //Prevent opponent from completing one row
      tmp = completingDrops(opponent, player);
      if (tmp) {
	return oneOf(tmp);
      } else {
	//Occupy the center if possible
	if (isCenterFree(red|green)) {
	  return 0b000010000;
	} else {
	  //Make random move
	  return oneOf(inverseOf(red|green));
	}
      }
    }   
  }
}
  
//Check the status of the board
// args:   red:   all red marks
//         green: all green marks
// result: True if the game is over
bool checkBoardClassic(fields red , fields green) {
  fields tmp   = 0b000000000;  //temporary storage

  //Check if green won
  tmp = completedRowsIn(green);
  if (tmp) {
    //Signal victory
    blink(red, green, tmp);
    return true;
  }

  //Check if red won
  tmp = completedRowsIn(red);
  if (tmp) {
    //Signal victory
    blink(red, green, tmp);
    return true;
  }

  //Check for a tie
  if ((red|green) == 0x111111111) {
    return true;
  }
    
  return false;
}

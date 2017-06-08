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
//# The green player begins. The first eight turns are played according to the  #
//# classic TicTacToe rules. From the ninth turn on, the players alternately    #
//# shist one of their marks onto the empty spot. The first player to place     #
//# three marks in one row wins the game.                                       #
//#                                                                             #
//###############################################################################
//# Version History:                                                            #
//#    April 6, 2017                                                            #
//#      - Initial release                                                      #
//###############################################################################

#include "TicTacToe.h"

//// Play
////======
////Play the classic game
//// args:   greenIsHuman: true if green player is human
////         redIsHuman:   true if red player is human  
//// result: none
//void playAchi (bool greenIsHuman, bool redIsHuman) {
//  //Board
//  fields red   = 0b000000000;  //set of red marks on the board
//  fields green = 0b000000000;  //set of green marks on the board
//  fields shift = 0b000000000;  //valid fields for shifting
//  
//  //Game loop
//  while (1) {
//    //Play the classic rules for the first eight moves
//    //================================================
//    if (countOf(red|green) < 8) {
//    
//      //Classic green move
//      //==================
//      green |= makeMoveClassic(greenIsHuman, green, red, red , green);
//      noAnim(red, green);
//      
//      //Check board
//      //===========
//      if (checkBoardAchi(red, green)) {
//	break;
//      }
//
//      //Classic Red move
//      //================
//      red |= makeMoveClassic(redIsHuman, red, green, red , green);
//      noAnim(red, green);
//     
//      //Check board
//      //===========
//      if (checkBoardAchi(red, green)) {
//	break;
//      }
//    } else {
//      //Play the Achi rules for the rest of the game
//      //============================================
//      //Green Achi move
//      //================
//      shift = makeMoveAchi(greenIsHuman, green, red, red , green);
//      if (shift) {
//	green |= inverseOf(red|green);  //mark empty field
//	green &= inverseOf(shift);      //clear shifted field
//      }
//      noAnim(red, green);
//      
//      //Check board
//      //===========
//      if (checkBoardAchi(red, green)) {
//	break;
//      }
//
//      //Green Achi move
//      //================
//      shift = makeMoveClassic(greenIsHuman, green, red, red , green);
//      if (shift) {
//	green |= inverseOf(red|green);  //mark empty field
//	green &= inverseOf(shift);      //clear shifted field
//      }
//      noAnim(red, green);
//      
//      //Check board
//      //===========
//      if (checkBoardAchi(red, green)) {
//	break;
//      }
//    }
//  }
//
//  //Wait for input to continue and clear the sisplay
//  getKey();
//  noAnim(0b000000000, 0b000000000);
//}
//   
////Make one move in the classic game
//// args:   isHuman:  true if current player is human
////         player:   marks of current player
////         opponent: marks of the opponent 
////         red:      all red marks
////         green:    all green marks
//// result: mark to be shifted into the empty spot
//fields makeMoveAchi(bool isHuman, fields player, fields opponent, fields red , fields green) {
//  fields tmp   = 0b000000000;  //temporary storage
//  
//  if (isHuman) {
//    tmp = validShifts(player, opponent);
//    if (tmp) {    
//      //Wait for input
//      return selectField(red, green, tmp);
//    } else {
//      //Can't move -> skip turn
//      return 0x000000000;
//    } 
//  } else {
//    //Try to complete one row
//    tmp = completingShifts(player, opponent);
//    if (tmp) {
//      return oneOf(tmp);
//    } else {
//      //Avoid shifts, that allow the opponent to win
//      tmp = validShifts(player, opponent) & inverseOf(badShifts(player, opponent));
//      if (tmp) {
//	return oneOf(tmp);
//      } else {
//	//See if any move is possible at all
//	tmp = validShifts(player, opponent);
//	if (tmp) {
//	  return oneOf(tmp);
//	} else {
//	  //Can't move -> skip turn
//	  return 0x000000000;
//	}
//      }
//    }
//  }
//}
//  
////Check the status of the board
//// args:   red:   all red marks
////         green: all green marks
//// result: True if the game is over
//bool checkBoardAchi(fields red , fields green) {
//  fields tmp   = 0b000000000;  //temporary storage
//
//  //Check if green won
//  tmp = completedRowsIn(green);
//  if (tmp) {
//    //Signal victory
//    blink(red, green, tmp);
//    return true;
//  }
//
//  //Check if red won
//  tmp = completedRowsIn(red);
//  if (tmp) {
//    //Signal victory
//    blink(red, green, tmp);
//    return true;
//  }
//  return false;
//}

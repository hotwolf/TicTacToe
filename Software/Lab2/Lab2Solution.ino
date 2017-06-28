//###############################################################################
//# TicTacToe - Lab2 -> Solution                                                #
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

// classicComputerTurn()
//=======================
//Computer turn in the classic game
// args:   color
//fields classicComputerTurn(turn currentTurn) {
//  fields player   = (currentTurn == greenTurn) ? green : red;
//  fields opponent = (currentTurn == greenTurn) ? red   : green;
//  fields free     = inverseOf(red | green);
//  fields options;
//
//  //Try to win the game. Complete a row if possible
//  if (options = completingDrops(player, opponent)) {
//    return oneOf(options);
//  }
//
//  //Prevent the opponent from winning. Block a row of the opponent if possible
//  if (options = completingDrops(opponent, player)) {
//    return oneOf(options);
//  }
//
//  //Occupy the center if possible
//  if (0b000010000 & free) {
//    return 0b000010000;
//  }
//
//  //Occupy a corner if possible
//  if (options = (0b101000101 & free)) {
//    return oneOf(options);
//  }
//
//  //Pick a random field
//  return oneOf(free);
//
//}

//###############################################################################
//# TicTacToe - Lab1 -> Solution                                                #
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
//#    July 3, 2017                                                             #
//#      - Initial release                                                      #
//###############################################################################
/*
#include "TicTacToe.h"

// completedRowsIn()
//===================
//Find all completed rows in a given set of fields
// args:   set: set of fields
// result: all fields that are part of a completed row 
fields completedRowsIn(fields set) {
  fields result = 0;

  //Check 8 patterns
  // ---
  // ...
  // ...
  if (isSubsetOf(0b000000111, set)) {
    result = result | 0b000000111;
  }
  // ...
  // ---
  // ...
  if (isSubsetOf(0b000111000, set)) {
    result = result | 0b000111000;
  }
  // ...
  // ...
  // ---
  if (isSubsetOf(0b111000000, set)) {
    result = result | 0b111000000;
  }
  // |..
  // |..
  // |..
  if (isSubsetOf(0b001001001, set)) {
    result = result | 0b001001001;
  }
  // .|.
  // .|.
  // .|.
  if (isSubsetOf(0b010010010, set)) {
    result = result | 0b010010010;
  }
  // ..|
  // ..|
  // ..|
  if (isSubsetOf(0b100100100, set)) {
    result = result | 0b100100100;
  }
  // \..
  // .\.
  // ..\_
  if (isSubsetOf(0b100010001, set)) {
    result = result | 0b100010001;
  }
  // ../
  // ./.
  // /..
  if (isSubsetOf(0b001010100, set)) {
    result = result | 0b001010100;
  }

  return result;
}

// completingDrops()
//===================
//Find all vacant field that will complete a row for the player
// args:   player:   current player's set of fields
//         opponent: opponent's set of fields
// result: all fields that would complete a row for the current player
fields completingDrops(fields player, fields opponent) {

  fields result = 0;   //return value
  fields iterator;     //field iterator

  //Iterate through all fields
  for (iterator = 0b000000001;
       iterator < 0b111111111;
       iterator <<= 1) {

    if (isSubsetOf(iterator, inverseOf(player|opponent))) {
      if (completedRowsIn(player|iterator)) {
        result = result | iterator;
      }
    }

  }
  return result;
}

// isSubsetOf()
//============
//Check if a set of fields is a subset of another set of fields
// args:   superset: set of fields
//         subset:   set of fields
// result: true if "subset" is a subset of "superset"
boolean isSubsetOf(fields subset, fields superset) {
  return ((superset & subset) == subset);
}

// inverseOf()
//=============
//Invert a set of fields
// args:   set: set of fields
// result: inverted set of fields
fields inverseOf(fields set) {
  return (set ^ 0b111111111);
}

*/

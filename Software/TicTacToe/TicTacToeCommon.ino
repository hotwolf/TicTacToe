//###############################################################################
//# TicTacToe - Common Subroutines                                              #
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
//# Version History:                                                            #
//#    April 5, 2017                                                            #
//#      - Initial release                                                      #
//###############################################################################

#include "TicTacToe.h"

// Checks
//========
//Check if a set of fields is a subset of another set of fields
// args:   superset: set of fields
//         subset:   set of fields
// result: true if "subset" is a subset of "superset"
boolean isSubsetOf(fields subset, fields superset) {
  return ((superset & subset) == subset);
}

// Basic operations
//==================
//Invert a set of fields
// args:   set: set of fields
// result: inverted set of fields
fields inverseOf(fields set) {
  return (set ^ 0b111111111);
}

//Find all horizintal and vertical neighbors of a given set of fields
// args:   set: set of fields to find neighbors for
// result: neighbors of input set
// A|B|C     15     8 7      0
// -+-+-    +--------+--------+ 
// D|E|F => |-------I|HGFEDCBA| 
// -+-+-    +--------+--------+ 
// G|H|I
fields neighborsOf(fields set) {
  fields result = 0;

  //Right neighbors
  result |= (set & 0b011011011) << 1;
  //Left neighbors
  result |= (set & 0b110110110) >> 1;
  //Upper neighbors
  result |= (set & 0b111111000) >> 3;
  //Lower neighbors
  result |= (set & 0b000111111) << 3;
  //Upper right neighbors
  result |= (set & 0b011011000) >> 2;
  //Lower left neighbors
  result |= (set & 0b000110110) << 2;
  //Upper left neighbors
  result |= (set & 0b110110000) >> 4;
  //Lower right neighbors
  result |= (set & 0b000011011) << 4;

  return result;
}

//Move a piece in a set
// args: set:          players set of fields
//       fromPosition: field to move away from
//       toPosition:   field to move to
// result: neighbors of input set
fields move(fields set, fields fromPosition, fields toPosition) {

  return (set & inverseOf(fromPosition)) | toPosition;
}

//Count the fields in a given set
// args:   set: set of fields
// result: number of fields in the the set
unsigned char countOf(fields set) {
  unsigned char result = 0; //return value
  fields        iterator;   //field iterator

  //Iterate through all fields
  for (iterator = 0b000000001;
       iterator < 0b111111111;
       iterator <<= 1) {
    if (set & iterator) {
      result++;
    }
  }

  return result;
}

//Select one random field out of a given set
// args:   set: set of selectable fields
// result: randomly selected field
fields oneOf(fields set) {
  unsigned char count;     //number of fields
  unsigned char pick;      //random pick
  fields        iterator;  //field iterator

  //Count the number of fields
  count = countOf(set);

  //No choice
  if (count < 2) {
    return set;
  }

  //Pick a numer that is smaller then the field count
  pick = random(count);

  //Iterate through all fields
  for (iterator = 0b000000001;
       iterator < 0b111111111;
       iterator <<= 1) {
    if (set & iterator) {
      if (!pick--) {
        return iterator;
      }
    }
  }
}

// Board Queries
//===============
//Find all completed rows in a given set of fields
// args:   set: set of fields
// result: all fields that are part of a completed row
fields completedRowsIn(fields set) {
  fields result = 0;

  //Check 8 patterns
  // ---
  // ...
  // ...
  result |= isSubsetOf(0b000000111, set) ? 0b000000111 : 0b000000000;
  // ...
  // ---
  // ...
  result |= isSubsetOf(0b000111000, set) ? 0b000111000 : 0b000000000;
  // ...
  // ...
  // ---
  result |= isSubsetOf(0b111000000, set) ? 0b111000000 : 0b000000000;
  // |..
  // |..
  // |..
  result |= isSubsetOf(0b001001001, set) ? 0b001001001 : 0b000000000;
  // .|.
  // .|.
  // .|.
  result |= isSubsetOf(0b010010010, set) ? 0b010010010 : 0b000000000;
  // ..|
  // ..|
  // ..|
  result |= isSubsetOf(0b100100100, set) ? 0b100100100 : 0b000000000;
  // \..
  // .\.
  // ..\_
  result |= isSubsetOf(0b100010001, set) ? 0b100010001 : 0b000000000;
  // ../
  // ./.
  // /..
  result |= isSubsetOf(0b001010100, set) ? 0b001010100 : 0b000000000;

  return result;
}

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
        result |= iterator;
      }
    }
  }
  return result;
}


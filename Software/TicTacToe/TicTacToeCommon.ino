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
//#                                                                             #
//#                                                                             #
//#                                                                             #
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
boolean isSubset(fields superset, fields subset) {
  return ((superset & subset) == subset);
}

// Basic operations
//==================
//Invert a set of fields
// args:   set: set of fields
// result: inverted set of fields
fields inverseOf(fields set) {

  //Serial.println("inverseOf!");
  //Serial.print("set: ");
  //Serial.println(set, BIN);
  //Serial.print("return: ");
  //Serial.println((~set & 0b111111111), BIN);

  return (~set & 0b111111111);
}

//Find all horizintal and vertical neighbors of a given set of fields
// args:   set: set of fields to find neighbors for
// result: neighbors of input set
fields neighborsOf(fields set) {
  fields result = 0;

  //Left neighbors
  result |= (set & 0b011011011) << 1;
  //Right neighbors
  result |= (set & 0b110110110) >> 1;
  //Upper neighbors
  result |= (set >> 3);
  //Lower neighbors
  result |= (set << 3) & 0b111111111;
  //Exclude input fields
  result &= ~set;

  //Serial.println("neighborsOf!");
  //Serial.print("set: ");
  //Serial.println(set, BIN);
  //Serial.print("return: ");
  //Serial.println(result, BIN);

  return result;
}

//Shift a piece in a set
// args: set:          players set of fields
//       fromPosition: field to move away from
//       toPosition:   field to move to
// result: neighbors of input set
fields shift(fields set, fields fromPosition, fields toPosition) {

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
  //Serial.println("countOf!");
  //Serial.print("set: ");
  //Serial.println(set, BIN);
  //Serial.print("return: ");
  //Serial.println(result);

  return result;
}

//Select one random field out of a given set
// args:   set: set of selectable fields
// result: randomly selected field
fields oneOf(fields set) {
  unsigned char count;     //number of fields
  unsigned char pick;      //random pick
  fields        iterator;  //field iterator

  //Serial.println("oneOf!");
  //Serial.print("set: ");
  //Serial.println(set, BIN);

  //Count the number of fields
  count = countOf(set);

  //no choice
  if (count < 2) {

    //Serial.print("return: ");
    //Serial.println(set, BIN);

    return set;
  }
  
  //Pick a numer that is smaller then the field count  
  pick = random(count);

  //Serial.print("pick: ");
  //Serial.println(pick);

 
  //Iterate through all fields
  for (iterator = 0b000000001;
       iterator < 0b111111111;
       iterator <<= 1) {
    if (set & iterator) {      
      if (!pick--) {

	//Serial.print("return: ");
	//Serial.println(iterator, BIN);

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
fields completeRows(fields set) {
  fields result = 0;

  //Serial.println("completeRows!");
  //Serial.print("set: ");
  //Serial.println(set, BIN);
  
  //Check 8 patterns
  // ---
  // ...
  // ...
  result |= isSubset(set, 0b000000111) ? 0b000000111 : 0b000000000;
  // ...
  // ---
  // ...
  result |= isSubset(set, 0b000111000) ? 0b000111000 : 0b000000000;
  // ...
  // ...
  // ---
  result |= isSubset(set, 0b111000000) ? 0b111000000 : 0b000000000;
  // |..
  // |..
  // |..
  result |= isSubset(set, 0b001001001) ? 0b001001001 : 0b000000000;
  // .|.
  // .|.
  // .|.
  result |= isSubset(set, 0b010010010) ? 0b010010010 : 0b000000000;
  // ..|
  // ..|
  // ..|
  result |= isSubset(set, 0b100100100) ? 0b100100100 : 0b000000000;
  // \..
  // .\.
  // ..\_
  result |= isSubset(set, 0b100010001) ? 0b100010001 : 0b000000000;

  //if (isSubset(set, 0b100010001)) {
  //  Serial.println("Diagonal row!");
  //  Serial.print("set: ");
  //  Serial.println(set, BIN);
  //  boolean _isSubset = isSubset(set, 0b100010001);
  //  Serial.print("_isSubset: ");
  //  Serial.println(_isSubset ? "TRUE" : "FALSE");
  //  fields _pattern = isSubset ? 0b100010001 : 0b000000000;
  //  Serial.print("_pattern: ");
  //  Serial.println(_pattern, BIN);
  //  Serial.print("result: ");
  //  Serial.print(result, BIN);
  //  Serial.print(" => ");
  //  //result |= _pattern;
  //  //result |= _isSubset ? 0b100010001 : 0b000000000;
  //  result |= isSubset(set, 0b100010001) ? 0b100010001 : 0b000000000;
  //  Serial.println(result, BIN);
  //}   

  // ../
  // ./.
  // /..
  result |= isSubset(set, 0b001010100) ? 0b001010100 : 0b000000000;

  //Serial.print("return: ");
  //Serial.println(result, BIN);

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
    if (!isSubset((player|opponent), iterator)) {       
      if (completeRows(player|iterator)) {
        result |= iterator;
      }
    }
  }
  return result;
}

////Find all shiftable fields
//// args:   player:   current player's set of fields
////         opponent: opponent's set of fields
//// result: all fields that would complete a row for the current player
//fields validShifts(fields player, fields opponent) {
//  return (neighborsOf(inverseOf(player|opponent))&player);
//}

////Find all shiftable fields that will complete a row for the player
//// args:   player:   current player's set of fields
////         opponent: opponent's set of fields
//// result: all fields that would complete a row for the current player
//fields completingShifts(fields player, fields opponent) {
//  fields result = 0;    //return value
//  fields valid;         //all eligible shifts
//  fields vacant;        //iterator over vacant
//  fields neighbor;      //iterator over neighbors
//  
//  //Iterate vacant fields
//  for (vacant = 0b000000001;
//       vacant < 0b111111111;
//       vacant <<= 1) {
//    if (!isSubset((player|opponent), vacant)) {  //field must be vacant
//      if (valid = (neighborsOf(vacant) & player)) {
//        for (neighbor = 0b000000001;
//             neighbor < 0b111111111;
//             neighbor <<= 1) {
//          if (isSubset(valid, neighbor)) {
//            if (completedRowsIn(player|vacant&inverseOf(neighbor))) {
//              result |= neighbor;
//            }
//          }
//        }
//      }
//    }
//  }
//  return result;
//}
              
////Find all shiftable fields that will allow the opponent to complete a row next turn
//// args:   player:   current player's set of fields
////         opponent: opponent's set of fields
//// result: all fields that would complete a row for the current player
//fields badShifts(fields player, fields opponent) {
//  fields result = 0;    //return value
//  fields valid;         //all eligible shifts
//  fields vacant;        //iterator over vacant
//  fields neighbor;      //iterator over neighbors
//  
//  //Iterate vacant fields
//  for (vacant = 0b000000001;
//       vacant < 0b111111111;
//       vacant <<= 1) {
//    if (!isSubset((player|opponent), vacant)) {  //field must be vacant
//      if (valid = (neighborsOf(vacant) & player)) {
//        for (neighbor = 0b000000001;
//             neighbor < 0b111111111;
//             neighbor <<= 1) {
//          if (isSubset(valid, neighbor)) {
//            if (completingShifts(opponent ,(player|vacant&inverseOf(neighbor)))) {
//              result |= neighbor;
//            }
//          }
//        }
//      }
//    }
//  }
//  return result;
//}


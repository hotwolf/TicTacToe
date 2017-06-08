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
//# Display:                                                                    #
//# ========                                                                    #
//#                                                                             #
//#  Cathodes:       +-+   +-+   +-+                                            #
//#  PB2 ------------|A|---|B|---|C|                                            #
//#                  +-+   +-+   +-+                                            #
//#                   |     |     |                                             #
//#                  +-+   +-+   +-+                                            #
//#  PB1 ------------|D|---|E|---|F|                                            #
//#                  +-+   +-+   +-+                                            #
//#                   |     |     |                                             #
//#                  +-+   +-+   +-+                                            #
//#  PB0 ------------|G|---|H|---|I|                                            #
//#                  +-+   +-+   +-+                                            #
//#                   |     |     |                                             #
//#  Anodes:          |     |     |                                             #
//#  PC0 --red---+----+     |     |                                             #
//#  PC1 --green-+          |     |                                             #
//#                         |     |                                             #
//#  PC2 --red---+----------+     |                                             #
//#  PC3 --green-+                |                                             #
//#                               |                                             #
//#  PC4 --red---+----------------+                                             #
//#  PC5 --green-+                                                              #
//#                                                                             #
//# Keypad:                                       +-------------------+         #
//# =======                                       |  Wait until all   |         #
//#                                               | keys are released |<--+     #
//#  Rows:           +-+   +-+   +-+              +---------+---------+   |     #
//#  PD4 ------------|A|---|B|---|C|                        |             |     #
//#                  +-+   +-+   +-+                        V             |     #
//#                   |     |     |               +---------+---------+   |     #
//#                  +-+   +-+   +-+              |  Wait until any   |   |     #
//#  PD3 ------------|D|---|E|---|F|              |  key is pressed   |   |     #
//#                  +-+   +-+   +-+              +---------+---------+   |     #
//#                   |     |     |                         |             |     #
//#                  +-+   +-+   +-+                        V             |     #
//#  PD2 ------------|G|---|H|---|I|              +---------+---------+   |     #
//#                  +-+   +-+   +-+              |   Wait for the    |   |     #
//#  Columns:         |     |     |               |  debounce delay   |   |     #
//#  PD5 -------------+     |     |               +---------+---------+   |     #
//#                         |     |                         |             |     #
//#  PD6 -------------------+     |                         V             |     #
//#                               |               +---------+---------+   |     #
//#  PD7 -------------------------+               |  Scan keypad and  |   |     #
//#                                               | queue keycode if  +---+     #
//#                                               |the input is valid |         #
//#                                               +---------+---------+         #
//#                                                                             #
//#                                                                             #
//#                                                                             #
//###############################################################################
//# Version History:                                                            #
//#    April 5, 2017                                                            #
//#      - Initial release                                                      #
//###############################################################################

#include "TicTacToe.h"

//// Checks
////========
////Check if a set of fields is a subset of another set of fields
//// args:   superset: set of fields
////         subset:   set of fields  
//// result: true if "subset" is a subset of "superset"
//boolean isSubset(fields superset, fields subset) {
//  return (superset & subset == subset);
//}
//
////Check if the center field is free 
//// args:   set: set of fields
//// result: true if the center field is free
//boolean isCenterFree(fields set) {
//  return !isSubset(set, 0x000010000);
//}
//
//// Basic operations
////==================
////Invert a set of fields
//// args:   set: set of fields
//// result: inverted set of fields
//fields inverseOf(fields set) {
//  return (~set & 0x111111111);
//}
//
////Find all horizintal and vertical neighbors of a given set of fields
//// args:   set: set of fields to find neighbors for
//// result: neighbors of input set
//fields neighborsOf(fields set) {
//  fields result = 0;
//
//  //Left neighbors
//  result |= (set >> 1) & 0x011011011;
//  //Rightt neighbors
//  result |= (set << 1) & 0x110110110;
//  //Upper neighbors
//  result |= (set >> 3);
//  //Lower neighbors
//  result |= (set << 3);
//  //Exclude input fields
//  result &= ~set;
//  
//  return result;
//}
//
////Find all completed rows in a given set of fields
//// args:   set: set of fields
//// result: all fields that are part of a completed row
//fields completedRowsIn(fields set) {
//  fields result = 0;
//
//  //Check 8 patterns
//  // ---
//  // ...
//  // ...
//  result |= ((set & 0b000000111) == 0b000000111) ? 0b000000111 : 0b000000000;
//  // ...
//  // ---
//  // ...
//  result |= ((set & 0b000111000) == 0b000111000) ? 0b000111000 : 0b000000000;
//  // ...
//  // ...
//  // ---
//  result |= ((set & 0b111000000) == 0x111000000) ? 0b111000000 : 0b000000000;
//  // |..
//  // |..
//  // |..
//  result |= ((set & 0b001001001) == 0x001001001) ? 0b001001001 : 0b000000000;
//  // .|.
//  // .|.
//  // .|.
//  result |= ((set & 0b010010010) == 0x010010010) ? 0b010010010 : 0b000000000;
//  // ..|
//  // ..|
//  // ..|
//  result |= ((set & 0b100100100) == 0x100100100) ? 0b100100100 : 0b000000000;
//  // \..
//  // .\.
//  // ..\
//  result |= ((set & 0b100010001) == 0x100010001) ? 0b100010001 : 0b000000000;
//  // ../
//  // ./.
//  // /..
//  result |= ((set & 0b001010100) == 0x001010100) ? 0b001010100 : 0b000000000;
//
//  return result;
//}
//
////Count the fields in a given set
//// args:   set: set of fields
//// result: number of fields in the the set
//unsigned char countOf(fields set) {
//  unsigned char result = 0; //return value
//  fields        iterator;   //field iterator
//  
//  //Iterate through all fields
//  for (iterator = 0b000000001;
//       iterator < 0b111111111;
//       iterator <<= 1) {
//    if (isSubset(set, iterator)) {      
//      result++;
//    }
//  }
//  return result;
//}
//
////Select one random field out of a given set
//// args:   set: set of selectable fields
//// result: randomly selected field
//fields oneOf(fields set) {
//  unsigned char count;     //counter
//  fields        iterator;  //field iterator
//
//  //Pick a numer that is smaller then the field count  
//  count = random(countOf(set)-1);
//    
//  //Iterate through all fields
//  for (iterator = 0b000000001;
//       iterator < 0b111111111;
//       iterator <<= 1) {
//    if (isSubset(set, iterator)) {      
//      if (!count--) {
//          return iterator;
//      }
//    }   
//  }
//}
//
//// Board Queries
////===============
////Find all vacant field that will complete a row for the player
//// args:   player:   current player's set of fields
////         opponent: opponent's set of fields
//// result: all fields that would complete a row for the current player
//fields completingDrops(fields player, fields opponent) {
//  fields result = 0;   //return value
//  fields iterator;     //field iterator
//
//    //Iterate through all fields
//  for (iterator = 0b000000001;
//       iterator < 0b111111111;
//       iterator <<= 1) {
//    if (!isSubset((player|opponent), iterator)) {       
//      if (completedRowsIn(player|iterator)) {
//        result |= iterator;
//      }
//    }
//  }
//  return result;
//}
//
////Find all shiftable fields
//// args:   player:   current player's set of fields
////         opponent: opponent's set of fields
//// result: all fields that would complete a row for the current player
//fields validShifts(fields player, fields opponent) {
//  return (neighborsOf(inverseOf(player|opponent))&player);
//}
//
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
//              
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
//
//// Inputs
////========
////Select game
//// args:   none 
//// result: pushed button
//fields selectGame() {
//  fields result = 0b000000000;
//
//  //Display banner
//  chooseGameBanner();
//  
//  //Get input
//  result = getKey();
//
//  //Stop blinking
//  noAnim(0x000000000, 0x000000000);
//  
//  return result;
//}
//
////Select field to drop a mark on
//// args:   red:        red fields on the board
////         green:      green fields on the bord
////         selectable: set of selectable fields
//// result: selected field
//fields selectField(fields red, fields green, fields selectable) {
//  fields result = 0b000000000;
//
//  //Display selection
//  scan(red, green, selectable);
//  
//  //Get input
//  do {
//    result = getKey();
//  } while (!isSubset(selectable, result));
//
//  //stop blinking
//  noAnim(red, green);
//  
//  return result;
//}



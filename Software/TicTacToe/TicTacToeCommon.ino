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


//Find row fo three
// args:   board
// result: all rows of three
fields threeInARow(fields player) {
  fields result = 0;

  //Check 8 patterns
  // ---
  // ...
  // ...
  result |= ((player & 0b000000111) == 0b000000111) ? 0b000000111 : 0b000000000;
  // ...
  // ---
  // ...
  result |= ((player & 0b000111000) == 0b000111000) ? 0b000111000 : 0b000000000;
  // ...
  // ...
  // ---
  result |= ((player & 0b111000000) == 0x111000000) ? 0b111000000 : 0b000000000;
  // |..
  // |..
  // |..
  result |= ((player & 0b001001001) == 0x001001001) ? 0b001001001 : 0b000000000;
  // .|.
  // .|.
  // .|.
  result |= ((player & 0b010010010) == 0x010010010) ? 0b010010010 : 0b000000000;
  // ..|
  // ..|
  // ..|
  result |= ((player & 0b100100100) == 0x100100100) ? 0b100100100 : 0b000000000;
  // \..
  // .\.
  // ..\
  result |= ((player & 0b100010001) == 0x100010001) ? 0b100010001 : 0b000000000;
  // ../
  // ./.
  // /..
  result |= ((player & 0b001010100) == 0x001010100) ? 0b001010100 : 0b000000000;

  return result;
}










//###############################################################################
//# TicTacToe - Lab4 -> Common Subroutines                                      #
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
//#    June 28, 2017                                                            #
//#      - Initial release                                                      #
//###############################################################################

#include "TicTacToe.h"

// Basic operations
//==================
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

  //Exclude input fields
  result &= ~set;

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

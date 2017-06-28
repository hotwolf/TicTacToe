//###############################################################################
//# TicTacToe - Lab2 -> Exercise                                                #
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
fields classicComputerTurn(turn currentTurn) {
  fields player   = (currentTurn == greenTurn) ? green : red;
  fields opponent = (currentTurn == greenTurn) ? red   : green;
  fields free     = inverseOf(red | green);
  fields options;

  //Try to win the game. Complete a row if possible


     //...your code...


  //Prevent the opponent from winning. Block a row of the opponent if possible


     //...your code...


  //Occupy the center if possible


     //...your code...


  //Occupy a corner if possible


     //...your code...


  //Pick a random field


     //...your code...

}

  //Tip:
  //To pick one field from a set, use the function oneOf(...);
  //


// oneOf()
//=========
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

// countOf()
//===========
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

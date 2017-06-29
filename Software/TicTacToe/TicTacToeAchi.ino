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

// Play
//======
//Play the classic game
// args:   greenIsHuman: true if green player is human
//         redIsHuman:   true if red player is human
// result: none
void achiPlay() {
  //Variables
  boolean gameOver = false;

  Serial.println("Achi!");

  //4 rounds of drop game
  while (countOf(red) < 4)

    //Green move
    //==========
    green |= classicTurn(greenTurn);           //place green piece
    if (blinkGreen = completedRowsIn(green)) { //check if green has won
      gameOver = true;
      break;
    }

    //Red move
    //========
    red |= classicTurn(redTurn);               //place red piece
    if (blinkRed = completedRowsIn(red)) {     //check if green has won
      gameOver = true;
      break;
    }
  }

  //Start move game in case of a tie
  if (!gameOver) {

    //Move game
    while (1) {
      fields achiMove;

      //Green move
      //==========
      if (achiMove = achiTurn(greenTurn)){     //move green piece

        green = move(green, achiMove, inverseOf(red | green));//update fields

        if (blinkGreen = completedRowsIn(green)) {//check if green has won
          break;
        }

      } else {
        blinkRed = red;                        //green can't move => red won
        break;
      }

      //Red move
      //========
      if (achiMove = achiTurn(redTurn)){       //move green piece

        red = move(red, achiMove, inverseOf(red | green));//update fields

        if (blinkRed = completedRowsIn(red)) { //check if green has won
          break;
        }

      } else {
        blinkGreen = green;                    //red can't move => green won
        break;
      }

    }
  }
}

//One turn of the move game
// args:   color
// result: new mark to be placed
fields achiTurn(turn currentTurn) {
  fields player   = (currentTurn == greenTurn) ? green : red;
  fields opponent = (currentTurn == greenTurn) ? red   : green;
  fields free     = inverseOf(red | green);
  fields options  = neighborsOf(free) & player;

  //Check if there are any moves left
  if (options) {

    //Human or computer turn
    if ((currentTurn == greenTurn) ? greenIsHuman : redIsHuman) {
      return achiHumanTurn(currentTurn);
    } else {
      return achiComputerTurn(currentTurn);
    }

  } else {

    return 0; //no move left

  }
}

//Human turn in the move game
// args:   color
fields achiHumanTurn(turn currentTurn) {
  fields input    = 0;
  fields player   = (currentTurn == greenTurn) ? green : red;
  fields opponent = (currentTurn == greenTurn) ? red   : green;
  fields free     = inverseOf(red | green);
  fields options  = neighborsOf(free) & player;

  //Highlight options
  if (currentTurn == greenTurn) {
    scanGreen  = options;
    blinkGreen = options;
  } else {
    scanRed  = options;
    blinkRed = options;
  }

  //Get valid input
  do {
    gameSelection = getKey();

  } while (!(input & options));

  //Clear highlights
  scanGreen  = 0;
  scanRed    = 0;
  blinkGreen = 0;
  blinkRed   = 0;

  return input;

}

//Computer turn in the move game
// args:   color
fields achiComputerTurn(turn currentTurn) {
  fields player   = (currentTurn == greenTurn) ? green : red;
  fields opponent = (currentTurn == greenTurn) ? red   : green;
  fields free     = inverseOf(red | green);
  fields options  = neighborsOf(free) & player;
  fields iterator;   //field iterator
  fields moved;    //resust of potential move

  //Try to win
  for (iterator = 0b000000001;
       iterator < 0b111111111;
       iterator <<= 1) {
    if (options & iterator) {
      //Move palayer's field at the iterator
      moved = move(player, iterator, free);
      //Three in a row
      if (completedRowsIn(moved)) {
        return iterator;
      }
      //Opponent can't move
      if (!((neighborsOf(inverseOf(opponent | moved))) & (opponent))) {
        return iterator;
      }
    }
  }

  //Pick a random field
   return oneOf(options);

}


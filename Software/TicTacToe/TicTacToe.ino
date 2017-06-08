//###############################################################################
//# TicTacToe - Game                                                            #
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
//# Classic Rules:                                                              #
//# ==============                                                              #
//# The green player begins. Alternately each player places one mark on an      #
//# empty field on the board. The player who first manages to place three marks #
//# in one row (horizontal, vertical, or dialonal) wins the game.               #
//#                                                                             #
//# Misere Rules:                                                               #
//# =============                                                               #
//# The green player begins. Alternately each player places one mark on an      #
//# empty field on the board. The player who places three marks in one row      #
//# (horizontal, vertical, or dialonal) looses the game.                        #
//#                                                                             #
//# Achi Rules:                                                                 #
//# ===========                                                                 #
//# The green player begins. The first eight turns are played according to the  #
//# classic TicTacToe rules. From the ninth turn on, the players alternately    #
//# shist one of their marks onto the empty spot. The first player to place     #
//# three marks in one row wins the game.                                       #
//#                                                                             #
//###############################################################################
//# Version History:                                                            #
//#    March 24, 2017                                                           #
//#      - Initial release                                                      #
//###############################################################################

#include "TicTacToe.h"

// Variables
//===========
fields input;
bool greenIsHuman;
bool redIsHuman;

// Setup routine
//===============
void setup() {
  //Serial library
  Serial.begin(9600);
  Serial.println("Ready for debugging!");

  //Display
  dispSetup();

  //Keypad
  keysSetup();

  bannerStart();
}

// Application loop
//==================
void loop() {
//  //Select game
//  chooseGameBanner();
//  input = getKey();
//
//  //Determine players
//  if (input & 0b001001001) {
//    //Me 1st
//    greenIsHuman = true;
//    redIsHuman   = false;
//  } else if (input & 0b010010010) {
//    //Arduino 1st
//    greenIsHuman = false;
//    redIsHuman   = true;
//  } else {
//    //Two players
//    greenIsHuman = true;
//    redIsHuman   = true;
//  }
//  
//  //Determine rules
//  if (input & 0b000000111) {
//    //Classic
//    playClassic(greenIsHuman, redIsHuman);
//  } else if (input & 0b000111000) {
//    //Misere
//    playMisere(greenIsHuman, redIsHuman);
//  } else {
//    //Achi
//    playAchi(greenIsHuman, redIsHuman);
//  }
}


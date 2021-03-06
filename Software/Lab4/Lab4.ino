//###############################################################################
//# TicTacToe - Lab4 (complete game)                                            #
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
//#    June 28, 2017                                                            #
//#      - Initial release                                                      #
//###############################################################################

#include "TicTacToe.h"

// Variables
//===========
fields gameSelection;
  
// Setup routine
//===============
void setup() {
  //Serial library
  //Serial.begin(9600);
  //Serial.println("Lab4!");

  //Random seed
  randomSeed(analogRead(0));
  
  //Display
  dispSetup();

  //Keypad
  keysSetup();

  //Intro text
  //Control characters: \x80 = loop
  //                    \x81 = display red text
  //                    \x82 = display green text
  //                    \x83 = display bicolor (red+green) text
  //                    \x84 = start of the loop
  //  
  //          green    red    green     loop
  //            V       V       V        V 
  //textShow("\x82TIC \x81TAC \x82TOE \x80");

  textShow("...put your own text here...\x80");  

  gameSelection = getKey();
  textStop();

}

// Game loop
//===========
void loop() {
  //Clear display
  red        = 0;
  green      = 0;
  scanRed    = 0;
  scanGreen  = 0;
  blinkRed   = 0;
  blinkGreen = 0;
  
  //Determine players
  if (gameSelection & 0b001001001) {
    //Me 1st
    greenIsHuman = true;
    redIsHuman   = false;
  } else if (gameSelection & 0b010010010) {
    //Arduino 1st
    greenIsHuman = false;
    redIsHuman   = true;
  } else {
    //Two players
    greenIsHuman = true;
    redIsHuman   = true;
  }
  
  //Start Game
  if (gameSelection & 0b000000111) {
    //Classic
    classicPlay();
  } else if (gameSelection & 0b000111000) {
    //Misere
    miserePlay();
  } else {
    //Achi
    achiPlay();
  }

  //Next game
  gameSelection = getKey();
}

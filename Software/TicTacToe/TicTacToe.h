#ifndef TicTacToe_h
#define TicTacToe_h
//###############################################################################
//# TicTacToe                                                                   #
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
//#    March 30, 2017                                                           #
//#      - Initial release                                                      #
//###############################################################################

#include "TicTacToeDrv.h"
#include "TicTacToeAnim.h"
using namespace TicTacToeDrv;
using namespace TicTacToeAnim;

// Common functions
//==================

// Checks
//========
//Check if a set of fields is a subset of another set of fields
// args:   superset: set of fields
//         subset:   set of fields  
// result: true if "subset" is a subset of "superset"
boolean isSubset(fields superset, fields subset);

//Check if the center field is free 
// args:   set: set of fields
// result: true if the center field is free
boolean isCenterFree(fields set);

// Basic operations
//==================
//Invert a set if fields
// args:   set: set of fields
// result: inverted set of fields
fields invert(fields set);

//Count fields
// args:   player: current player's fields
// result: number of fields occupied by the player
unsigned char countFields(fields player);

//Select a random field
// args:   set: set of selectable fields
// result: randomly selected field
fields randomField(fields set);

// Queries
//=========
//Find completed rows
// args:   set: set of fields to query
// result: all fields that are part of a completed row
fields findCompletedRows(fields set);

//Find completable rows
// args:   player:   current player's set offields
//         opponent: opponent's set of fields
// result: all fields that would complete a row for the current player
fields findCompletableRows(fields player, fields opponent);

//Find neighbors
// args:   set: set of fields to find neighbors for
// result: all fields that are part of a completed row
fields findNeighbors(fields set);

//Check 8 patterns
// Inputs
//========
//Select game
// args:   none 
// result: pushed button
fields selectGame();

//Select field
// args:   red:        red fields on the board
//         green:      green fields on the bord
//         selectable: set of selectable fields
// result: selected field
fields selectField(fields red, fields green, fields selectable);

// Classic game
//==============
//Play the classic game
// args:   greenIsHuman: true if green player is human
//         redIsHuman:   true if red player is human  
// result: none
void playClassic (bool greenIsHuman, bool redIsHuman);

//Make one move in the classic game
// args:   isHuman:  true if current player is human
//         player:   marks of current player
//         opponent: marks of the opponent 
//         red:      all red marks
//         green:    all green marks
// result: new mark to be placed
fields makeMoveClassic(bool isHuman, fields player, fields opponent, fields red , fields green);

//Check the status of the board
// args:   red:   all red marks
//         green: all green marks
// result: True if the game is over
bool checkBoardClassic(fields red , fields green);

// Misere
//========
//Play Misere
// args:   greenIsHuman: true if green player is human
//         redIsHuman:   true if red player is human  
// result: none
void playMisere (bool greenIsHuman, bool redIsHuman);

//Make one move in the Misere game
// args:   isHuman:  true if current player is human
//         player:   marks of current player
//         opponent: marks of the opponent 
//         red:      all red marks
//         green:    all green marks
// result: new mark to be placed
fields makeMoveMisere(bool isHuman, fields player, fields opponent, fields red , fields green);

//Check the status of the board
// args:   red:   all red marks
//         green: all green marks
// result: True if the game is over
bool checkBoardMisere(fields red , fields green);

// Achi
//======
//Play Achi
// args:   greenIsHuman: true if green player is human
//         redIsHuman:   true if red player is human  
// result: none
void playAchi (bool greenIsHuman, bool redIsHuman);

//Make one move in the Achi game
// args:   isHuman:  true if current player is human
//         player:   marks of current player
//         opponent: marks of the opponent 
//         red:      all red marks
//         green:    all green marks
// result: new mark to be placed
fields makeMoveAchi(bool isHuman, fields player, fields opponent, fields red , fields green);

//Check the status of the board
// args:   red:   all red marks
//         green: all green marks
// result: True if the game is over
bool checkBoardAchi(fields red , fields green);

#endif

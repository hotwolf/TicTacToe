#ifndef TicTacToeAnim_h
#define TicTacToeAnim_h
//###############################################################################
//# TicTacToe - Animation Routines                                              #
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
//#    March 24, 2017                                                           #
//#      - Initial release                                                      #
//###############################################################################

// Constants
//===========

// Type definitions
//==================

// Inline assembler
//==================

// Functions
//===========
namespace TicTacToeAnim {
  void   blink( fields red, fields green, fields highlight); //blink selected fields
  void   scan(  fields red, fields green, fields highlight); //move highlight through selected fields
  void   noAnim(fields red, fields green);                   //stop all animations   
  void   chooseGameBanner();                                 //scroll a "Choose Game" banner
}

#endif

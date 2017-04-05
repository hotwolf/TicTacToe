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

#include <Arduino.h>
#include <avr/pgmspace.h>
#include "TicTacToeDrv.h"
#include "TicTacToeAnim.h"

// Target Check
//==============
#if defined(ARDUINO_AVR_UNO)
#else
#error Unsupported hardware
#endif

// Hidden Variables
//==================
namespace {
  fields        _animBuf[4] = { 0 };        //display buffer for animations
  int           _animCount  =   0;          //frame counter

  //.@@.@.@.@@@.@@@..@@.@@@....@...@..@@@.@@@....
  //@...@@@.@.@.@.@..@..@@....@...@@@.@@@.@@.....
  //.@@.@.@.@@@.@@@.@@..@@@....@@.@.@.@.@.@@@....
  //18E   16D   1EF   125   020   17A   16D   000
  //   0B2   0D3   1A4   0CB   0C1   0B6   0CB
  const fields _chooseGameBanner[] PROGMEM = {0x018E,
                                              0X00B2,
                                              0X016D,
                                              0X00D3,
                                              0X01EF,
                                              0X01A4,
                                              0X0125,
                                              0X00CB,
                                              0X0020,
                                              0X00C1,
                                              0X017A,
                                              0X00B6,
                                              0X016D,
                                              0X00CB,
                                              0X0000};
  
  //@@@.@..@@.@.@....@...@..@@@.@@@.....
  //@@@.@.@...@@....@...@@@.@@@.@@......
  //@...@..@@.@.@....@@.@.@.@.@.@@@.....
  //07F   18E   041   160   17F   041
  //   092   0B2   114   099   1B6   000
  /*
  const fields _chooseGameBanner[] PROGMEM = {0x07F,
                                              0X0092,
                                              0X018E,
                                              0X00B2,
                                              0X0O41,
                                              0X0114,
                                              0X0160,
                                              0X0099,
                                              0X017F,
                                              0X01B6,
                                              0X0041,
                                              0X0000};
*/



}

// Hidden Functions
//==================
namespace {
  void blinkCallback();                     //callback routine for the blink animation
  void scanCallback();                      //callback routine for the scan animation
  void chooseGameCallback();                //callback routine for the "Choose Game" animation
}

// Functions
//===========

//Blink selected fields
// args:   selected fields
// result: none
void TicTacToeAnim::blink(fields highlight) {
  //Save current screen
  //  red   -> animBuf[0] 
  //  green -> animBuf[1]
  _animBuf[0] = TicTacToeDrv::getRed();
  _animBuf[1] = TicTacToeDrv::getGreen();
  
  //Calculate highlighted screen
  _animBuf[2] = _animBuf[0] | highlight;     //red
  _animBuf[3] = _animBuf[3] | highlight;     //green
  
  //Set animation counter
  _animCount = FRAMERATE;                   //duration: 1sec

  //Set animation callback
  TicTacToeDrv::setAnimation(blinkCallback);
}

//Blink callback
void blinkCallback() {
  switch(--_animCount) {
  case (0.25*FRAMERATE):
    TicTacToeDrv::setRed(_animBuf[2]);      //show highlighted screen
    TicTacToeDrv::setGreen(_animBuf[3]);    //
    break;
  case 0:
    _animCount = FRAMERATE;                 //reset animation counter
    TicTacToeDrv::setRed(_animBuf[0]);      //show plain screen
    TicTacToeDrv::setGreen(_animBuf[1]);    //
    break;
  }
}

//Move highlight through selected fields
// args:   selected fields
// result: none
void TicTacToeAnim::scan(fields highlight) {
  //Save current screen
  //  red   -> animBuf[0] 
  //  green -> animBuf[1]
  _animBuf[0] = TicTacToeDrv::getRed();
  _animBuf[1] = TicTacToeDrv::getGreen();
  
  //Save selection
  _animBuf[2] = highlight;

  //Reset field pointer
  _animBuf[3] = 0;

  //Set animation counter
  _animCount = 0.5*FRAMERATE;               //duration: 0.5sec

  //Set animation callback
  TicTacToeDrv::setAnimation(scanCallback);
}

//Scan callback
void scanCallback() {
  if (--_animCount == 0) {
    _animCount = 0.5*FRAMERATE;             //reset animation counter

    //Check for start of scan cycle
    if (_animBuf[3] == 0) {
      _animBuf[3] == 1;                     //start new cycle
    } else {
      _animBuf[3] == _animBuf[3] << 1;      //switch to next field
    }

    //Shift to next highlighted field
    while ( (_animBuf[3] <= _animBuf[2])  &&
            !(_animBuf[3]  & _animBuf[2])) {
      _animBuf[3] == _animBuf[3] << 1;      //switch to next field
    }
    if  (_animBuf[3] > _animBuf[2]) {
      _animBuf[3] = 0;                       //restart scan cycle
    }
      
    //Update display
    TicTacToeDrv::setRed(  _animBuf[0] | _animBuf[3]);
    TicTacToeDrv::setGreen(_animBuf[1] | _animBuf[3]);
  }
}

//Scroll "Choose Game" banner
// args:   
// result: none
void TicTacToeAnim::chooseGame() {
  //Save current screen
  //  red   -> animBuf[0] 
  //  green -> animBuf[1]
  _animBuf[0] = TicTacToeDrv::getRed();
  _animBuf[1] = TicTacToeDrv::getGreen();
  
  //Current pattern
  _animBuf[2] = 0;

  //Follow-up pattern
  _animBuf[3] = 0;

  //Set animation counter
  _animCount = -1;

  //Set animation callback
  TicTacToeDrv::setAnimation(chooseGameCallback);
}

//"Choose Game" callback
void chooseGameCallback() {
  //Local variables
  byte patternCount;
  
  //Increment animation counter
  _animCount++;
  
  //Check if an animation is required
  if ((_animCount % (FRAMERATE/4)) == 4) {

    //Animate
    switch ((_animCount / (FRAMERATE/4) % 3)) {
      case 0:
        //Shift in next pattern
        _animBuf[2] = _animBuf[3];
        _animBuf[3] = pgm_read_word(&_chooseGameBanner[_animCount / (3*(FRAMERATE/4))]);
        
        //Display pattern
        TicTacToeDrv::setRed(  _animBuf[2]);
        TicTacToeDrv::setGreen(_animBuf[2]);
        
        //Reset frame counter
        if (_animBuf[3] == 0) {
          _animCount = 0;
        }
        break;
        
      case 1:     
        //Display pattern
        TicTacToeDrv::setRed(((_animBuf[2] & 0x1B6) >> 1) |
                             ((_animBuf[3] & 0x049) << 2));
        TicTacToeDrv::setGreen(TicTacToeDrv::getRed());
        break;                 
        
      case 2:     
        //Display pattern
        TicTacToeDrv::setRed(((_animBuf[2] & 0x124) >> 2) |
                             ((_animBuf[3] & 0x0DB) << 1));
        TicTacToeDrv::setGreen(TicTacToeDrv::getRed());
        break;                 
    }
  }
}       

//Stop ongoing animation
// args:   
// result: none
void TicTacToeAnim::noAnim() {
  //Restore screen
  //  red   -> animBuf[0] 
  //  green -> animBuf[1]
  TicTacToeDrv::setRed(  _animBuf[0]);
  TicTacToeDrv::setGreen(_animBuf[1]);

  //Remove animation callback
  TicTacToeDrv::setAnimation(NULL);
}


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
//namespace {
  void blinkCallback();                     //callback routine for the blink animation
  void scanCallback();                      //callback routine for the scan animation
  void chooseGameBannerCallback();                //callback routine for the "Choose Game" animation
//}

// Functions
//===========

//Blink selected fields
// args:   red:       set of red fields
//         green:     set of green fields
//         highlight: set of highlighted fields
// result: none
void TicTacToeAnim::blink(fields red, fields green, fields highlight) {
  //Set animation buffer
  _animBuf[0] = red;                        //phase1 red
  _animBuf[1] = green;                      //phase1 green
  _animBuf[2] = red   | highlight;          //phase2 red
  _animBuf[3] = green | highlight;          //phase2 green
  
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
// args:   red:       set of red fields
//         green:     set of green fields
//         highlight: set of highlighted fields
// result: none
void TicTacToeAnim::scan(fields red, fields green, fields highlight) {
  //Set animation buffer
  _animBuf[0] = red;                        //red fields
  _animBuf[1] = green;                      //green fields
  _animBuf[2] = highlight;                  //highlights
  _animBuf[3] = 0;                          //iterator

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
// args:   none
// result: none
void TicTacToeAnim::chooseGameBanner() {
  //Set animation buffer
  _animBuf[0] = 0x000000000;                 //current pattern
  _animBuf[1] = 0x000000000;                 //follow-up pattern

  //Set animation counter
  _animCount = -1;

  //Set animation callback
  TicTacToeDrv::setAnimation(chooseGameBannerCallback);
}

//"Choose Game" callback
void chooseGameBannerCallback() {
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
        _animBuf[0] = _animBuf[1];
        _animBuf[1] = pgm_read_word(&_chooseGameBanner[_animCount / (3*(FRAMERATE/4))]);
        
        //Display pattern
        TicTacToeDrv::setRed(  _animBuf[0]);
        TicTacToeDrv::setGreen(_animBuf[0]);
        
        //Reset frame counter
        if (_animBuf[3] == 0) {
          _animCount = 0;
        }
        break;
        
      case 1:     
        //Display pattern
        TicTacToeDrv::setRed(((_animBuf[0] & 0x1B6) >> 1) |
                             ((_animBuf[1] & 0x049) << 2));
        TicTacToeDrv::setGreen(TicTacToeDrv::getRed());
        break;                 
        
      case 2:     
        //Display pattern
        TicTacToeDrv::setRed(((_animBuf[2] & 0x124) >> 2) |
                             ((_animBuf[1] & 0x0DB) << 1));
        TicTacToeDrv::setGreen(TicTacToeDrv::getRed());
        break;                 
    }
  }
}       

//Stop ongoing animation
// args:   red:   set of red fields
//         green: set of green fields
// result: none
void TicTacToeAnim::noAnim(fields red, fields green) {
  //Set animation buffer
  _animBuf[0] = red;                        //red fields
  _animBuf[1] = green;                      //green fields

  //Remove animation callback
  TicTacToeDrv::setAnimation(NULL);
}


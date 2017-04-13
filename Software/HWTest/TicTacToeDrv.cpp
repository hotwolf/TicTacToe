//###############################################################################
//# TicTacToe - Driver Library                                                  #
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
#include <avr/sleep.h>
#include <avr/power.h>
#include "TicTacToeDrv.h"

// Target Check
//==============
#if defined(ARDUINO_AVR_UNO)
#else
#error Unsupported hardware
#endif

// Hidden Variables
//==================
namespace {
  keyState      _keyState          = release; //key pad state
  unsigned char _keyBuf[FIFODEPTH] = { 0 };   //input FIFO
  unsigned char _keyBufIn          = 0;       //index of next free entry in FIFO
  unsigned char _keyBufOut         = 0;       //index of oldest entry in FIFO buffer
  fields        _dispBuf[2]        = { 0 };   //display buffer (0=red, 1=green)
  unsigned char _dispSubFrame      = 0;       //index of oldest entry in FIFO buffer  
  animCallback  _dispAnimate       = NULL;    //animation callback
}

// Hidden Functions
//==================
namespace {
  void isrTim2MatchA();                     //timer 2 compare match A handler
  void isrTim2MatchB();                     //timer 2 compare match B handler
  void isrPinChange2();                     //pin change interrupt 2 handler
}

// Functions
//===========
//Driver setup
// args:   none
// result: none
void TicTacToeDrv::setup() {
  //Initialize timer 2
  //TCCR2A = 0;
  TCCR2B = (1 << CS22) |                    //set timer clock to 15.625kHz
           (1 << CS21) |
           (1 << CS20);
  OCR2A  = TCNT2+(15625/(6*FRAMERATE));     //next match A in 1/(3*frame rate)
  //OCR2B  = TCNT2;
  TIFR2  = (1 << OCF2B) |                   //clear output compare B interrupt flag
           (1 << OCF2A);                    //clear output compare A interrupt flag
  TIMSK2 = (1 << OCIE2A);                   //enable output compare A interrupt
  //ASSR   = 0;
  //GTCCR  = 0;

  //Initialize the display
  PORTB    = 0xFF;
  PORTC    = 0xFF;
  DDRB     = 0x07;
  DDRC     = 0x3F;
  
  //Initialize pin change interrupt
  PORTD  = 0xE3;                            //drive PD[4:2] low
  DDRD   = 0x1C;                            //set PD[7:5] to input 
  PCMSK2 = 0xE0;                            //enable pin change interrupt on PD[7:5]
  PCIFR  = (1 << PCIF2);                    //clear pin change interrupt flag   
  PCICR  = (1 << PCIE2);                    //enable pin change interrupt
  isrPinChange2();                          //handle initial key pad state  
}
//Wait for one keypad entry
// args:   none
// result: field associated with a key press
fields TicTacToeDrv::getKey() {
  //Local variables
  fields result;                            //return value

  //Start of atomic sequence
  noInterrupts();                           //disable interrupts
  
  //Wait until there is data in the queue
  SMCR = (1 << SE);                         //enable idle mode
  while(_keyBufIn == _keyBufOut) {          //repeat while the buffer is empty
    WAIT_FOR_INTERRUPT();                   //wait for anything to happen
    noInterrupts();                         //disable interrupts
  }
  SMCR = 0x00;                              //disable SLEEP mode
  
  //End of atomic sequence
  interrupts();                             //enable interrupts
  
  //Unqueue key entry
  result     = (fields) (1 << _keyBuf[_keyBufOut]);//get result
  _keyBufOut = (_keyBufOut++)%FIFODEPTH;    //advance output pointer

  return result;                            //return result
}

//Set red display fields 
// args:   fields
// result: none
void TicTacToeDrv::setRed(fields red) {
#ifdef CORRECTION
  _dispBuf[0] = 0b111111111 & ((~CORRECTION & red) | ( CORRECTION & _dispBuf[0]));
  _dispBuf[1] = 0b111111111 & (( CORRECTION & red) | (~CORRECTION & _dispBuf[1]));;
#else
  _dispBuf[0] = red;
#endif
}

//Set green display fields 
// args:   fields
// result: none
void TicTacToeDrv::setGreen(fields green) {
#ifdef CORRECTION
  _dispBuf[0] = 0b111111111 & (( CORRECTION & green) | (~CORRECTION & _dispBuf[0]));
  _dispBuf[1] = 0b111111111 & ((~CORRECTION & green) | ( CORRECTION & _dispBuf[1]));;
#else  
  _dispBuf[1] = green;
#endif
}

//Get red display fields 
// args:   none
// result: fields
fields TicTacToeDrv::getRed() {
  return _dispBuf[0];
}

//Get green display fields 
// args:   none
// result: fields
fields TicTacToeDrv::getGreen() {
  return _dispBuf[1];
}

//Set animation callback
// args:   none
// result: fields
void TicTacToeDrv::setAnimation(animCallback callback) {
  _dispAnimate = callback;
}

// ISRs
//======
namespace {
  // Timer 2 compare match A handler
  //---------------------------------
  void isrTim2MatchA() {
    //Local variables
    unsigned char colRaw;                     //unformated column pattern
    unsigned char colPat;                     //formated column pattern
    unsigned char colNum;                     //column number
    unsigned char colSel;                     //column selector
    
    //Restart timer
    OCR2A += (15625/(6*FRAMERATE));           //set next timer delay
  
    //Calculate column selector and row pattern
    colNum = _dispSubFrame%6;
    colSel = 1 << colNum;
    colRaw = (unsigned char) (_dispBuf[colNum & 1]) >> (colNum >> 1);
    colPat = ~(((colRaw & 0x40) >> 4) |
             ((colRaw & 0x08) >> 2) |
             ( colRaw & 0x01));
  
    //Apply column selector and row pattern
    PORTC = 0;                                //deselect all columns                
    PORTB = colPat;                           //apply column pattern
    PORTC = colSel;                           //select column
  
    //Animation callback
    if (_dispAnimate != NULL) {
      _dispAnimate();
    }    
  }
  
  // Timer 2 compare match B handler
  //---------------------------------
  void isrTim2MatchB() {
    //Local variables
    fields        keys;                       //captured keys
    unsigned char key;                        //key iterator
    
    //Capture keys
    PORTD  = 0xEF;                            //select row ABC   
    keys   = (PIND & 0xE0) >> 5;              //capture row ABC
    PORTD  = 0xF7;                            //select row DEF   
    keys  |= (PIND & 0xE0) >> 2;              //capture row DEF
    PORTD     = 0xFB;                         //select row GHI   
    keys  |= (PIND & 0xE0) << 1;              //capture row GHI
    PORTD     = 0xE3;                         //select all rows   
  
    //Parse captured keys
    key = 0;                                  //initialize iterator
    while (( keys      != 0) &&               //unparsed keys left
         ((keys & 1) == 0)) {               //current key is not pushed
      key++;                                  //increment iterator
      keys >>= 1;                             //shift to next key
    }
    if (keys == 1) {                          //input is valid
      //Queue valid input
      _keyBuf[_keyBufIn] = key;               //store key in keyBuf
      _keyBufIn = (_keyBufIn++)%FIFODEPTH;    //advance input pointer
      if (_keyBufIn == _keyBufOut) {          //check for overflow
        _keyBufOut = (_keyBufOut++)%FIFODEPTH;//delete oldest entry if necessary
      }
    }
  
    //Disable bebounce timer
    TIMSK2 = (1 << OCIE2A);                   //enable output compare A interrupt
  
    //Prepare next key input 
    _keyState  = release;                     //make sure all keys are released
    PCIFR  = (1 << PCIF2);                    //clear pin change interrupt flag   
    PCICR  = (1 << PCIE2);                    //enable pin change interrupt
    isrPinChange2();                          //handle initial key pad state    
  }
  
  // Pin change interrupt 2 handler
  //--------------------------------
  void isrPinChange2() {
    switch (_keyState) {
    case release:
      //Wait until all keys have been released
      if ((PIND & 0xE0) == 0xE0) {
        _keyState = detect;                            //wait until any key is pushed
      }
      break;
    case detect:
      //Wait until any key is pushed
      if ((PIND & 0xE0) != 0xE0) {
        _keyState = debounce;                          //debounce key
        OCR2B  = TCNT2 + (15625 * DEBOUNCE / 1000);    //set debounce delay
        TIFR2  = (1 << OCF2B);                         //clear output compare B interrupt flag
        TIMSK2 = (1 << OCIE2B) |                       //enable output compare B interrupt
                 (1 << OCIE2A);                        //enable output compare A interrupt
        PCICR  = 0;                                    //disable pin change interrupt
      }
      break;
    }
  }
}

// Connect Interrupt Service Routines
//====================================
//Timer2 output compare A interrupt
ISR(TIMER2_COMPA_vect){                    
  isrTim2MatchA();
}

//Timer2 output compare B interrupt
ISR(TIMER2_COMPB_vect){                    
  isrTim2MatchB();
}

//Pin change interrupt 2
ISR(PCINT2_vect){                    
  isrPinChange2();
}

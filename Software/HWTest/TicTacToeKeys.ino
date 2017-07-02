//###############################################################################
//# TicTacToe - Keypad Driver                                                   #
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
//###############################################################################
//# Version History:                                                            #
//#    March 24, 2017                                                           #
//#      - Initial release                                                      #
//###############################################################################

#include <Arduino.h>
#include <avr/sleep.h>
#include <avr/power.h>
#include "TicTacToe.h"

// Constants
//===========
#define KEYS_FIFODEPTH       8             //key strokes to be queued
#define KEYS_DEBOUNCE_DELAY 35             //debounce delay [ms]

// Variables                                
//===========
fields        keysBuf[KEYS_FIFODEPTH] = { 0 };        //input FIFO
unsigned char keysBufIn               = 0;            //index of next free entry in FIFO
unsigned char keysBufOut              = 0;            //index of oldest entry in FIFO buffer
unsigned char keysDelay               = 0;            //extended debounce delay
boolean       keysReady               = true;         //ready to detect keyboard input

// Setup routine
//===============
void keysSetup() {
  //Initialize pin change interrupt
  PORTD  = 0xE3;                            //drive PD[4:2] low
  DDRD   = 0x1C;                            //set PD[7:5] to input 
  PCMSK2 = 0xE0;                            //enable pin change interrupt on PD[7:5]
  PCIFR  = (1 << PCIF2);                    //clear pin change interrupt flag   
  PCICR  = (1 << PCIE2);                    //enable pin change interrupt
}

// Queue access
//===============
//Wait for one keypad entry
// args:   none
// result: field associated with a key press
fields getKey() {
  //Local variables
  fields result;                            //return value

  //Start of atomic sequence
  noInterrupts();                           //disable interrupts
  
  //Wait until there is data in the queue
  SMCR = (1 << SE);                         //enable idle mode
  while(keysBufIn == keysBufOut) {          //repeat while the buffer is empty
    WAIT_FOR_INTERRUPT();                   //wait for anything to happen
    noInterrupts();                         //disable interrupts
  }
  SMCR = 0x00;                              //disable SLEEP mode
  
  //End of atomic sequence
  interrupts();                             //enable interrupts
  
  //Unqueue key entry
  result     = keysBuf[keysBufOut];         //get result
  keysBufOut = (keysBufOut+1)%KEYS_FIFODEPTH;//advance output pointer

  return result;                            //return result
}

// Interrupt Service xRoutines
//============================
//Timer2 output compare B interrupt
ISR(TIMER2_COMPB_vect){                    
  //Local variables
  fields        keys;                       //captured keys
  fields        key;                        //key iterator

  //Debug code
  //digitalWrite(13, HIGH);                 //turn LED on during the execution of the ISR
  //digitalWrite(13, !digitalRead(13));     //turn LED on during the execution of the ISR
  //Serial.println("Delay!");

  if (--keysDelay <= 0) {                    //handle extended delay
    keysDelay = 0;
  
    //Check if all keys have been released
    if ((PIND & 0xE0) == 0xE0) {
      //All pins released
      TIMSK2    = (1 << OCIE2A);              //disable timer interrupt
      keysReady = true;                       //ready for next input
      
      //Debug code
      //Serial.print("Keypad ready again! ");
      
    } else if (keysReady) {    
      keysReady = false;                      //input in process
      
      //Capture keys
      PORTD  = 0xEF;                        //select row ABC   
      NOP();
      keys   = (~PIND & 0xE0) >> 5;         //capture row ABC
      PORTD  = 0xF7;                        //select row DEF   
      NOP();
      keys  |= (~PIND & 0xE0) >> 2;         //capture row DEF
      PORTD     = 0xFB;                     //select row GHI   
      NOP();   
      keys  |= (~PIND & 0xE0) << 1;         //capture row GHI
      PORTD     = 0xE3;                     //select all rows   
      
      //Debug code
      //Serial.print("Captured: ");
      //Serial.println(keys, BIN);
      
      //Parse captured keys
      key = 0x100;                          //initialize iterator
      while (key) {                         //iterate through keys
        if (key == keys) {                  //check if key has been pressed
          break;                            //single key press detected
        }
        key >>= 1;                          //try next key
      }
      
      //Debug code
      //Serial.print("Parsed: ");
      //Serial.println(key, BIN);
      
      if (key) {                            //input is valid              
        //Queue valid input
        keysBuf[keysBufIn] = key;                    //store key in keyBuf
        keysBufIn = (keysBufIn+1)%KEYS_FIFODEPTH;    //advance input pointer
        if (keysBufIn == keysBufOut) {               //check for overflow
          keysBufOut = (keysBufOut+1)%KEYS_FIFODEPTH;//delete oldest entry if necessary
        }
      }
      
      //Debug code
      //Serial.print("Queue in: ");
      //Serial.print(keysBufIn);
      //Serial.print(" out: ");
      //Serial.println(keysBufOut);
    } 
  }
    
  //Debug code
  //digitalWrite(13, LOW);                  //turn LED off
}

//Pin change interrupt 2
ISR(PCINT2_vect){                    

  //Debug code
  //digitalWrite(13, HIGH);                 //turn LED on during the execution of the ISR
  //digitalWrite(13, !digitalRead(13));     //turn LED on during the execution of the ISR
  //Serial.println("Pin change!");

  //Trigger debounce delay
  OCR2B     = TCNT2;                           //~32ms debounce delay
  keysDelay = KEYS_DEBOUNCE_DELAY/16;          //reset extended delay
  TIFR2     = (1 << OCF2B);                    //clear output compare ABinterrupt flag
  TIMSK2    = (1 << OCIE2A) |                  //enable output compare A interrupt
              (1 << OCIE2B);                   //enable output compare A interrupt
  
  //Debug code
  //digitalWrite(13, LOW);                  //turn LED off
}

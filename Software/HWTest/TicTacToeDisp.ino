//###############################################################################
//# TicTacToe - Display Driver                                                  #
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
//# ========                      +-+   +-+   +-+                               #
//#          C    PB2 ------------|A|---|B|---|C|                               #
//#          A                    +-+   +-+   +-+                               #
//#          T                     |     |     |                                #
//#          H                    +-+   +-+   +-+                               #
//#          O    PB1 ------------|D|---|E|---|F|                               #
//#          D                    +-+   +-+   +-+                               #
//#          E                     |     |     |                                #
//#          S                    +-+   +-+   +-+                               #
//#               PB0 ------------|G|---|H|---|I|                               #
//#                               +-+   +-+   +-+                               #
//#                                |     |     |                                #
//#          A    PC0 --red---+----+     |     |                                #
//#          N    PC1 --green-+          |     |                                #
//#          O                           |     |                                #
//#          D    PC2 --red---+----------+     |                                #
//#          E    PC3 --green-+                |                                #
//#          S                                 |                                #
//#               PC4 --red---+----------------+                                #
//#               PC5 --green-+                                                 #
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
#define DISP_FPS  120          //refresh rate [fps]
//#define DISP_FIX 0b000000000 //fix swapped LEDs

// Variables                                
//===========                                
fields       dispRedBuf     = 0;    //red display buffer
fields       dispGreenBuf   = 0;    //green display buffer

byte         dispColumn     = 0;    //current column

byte         dispNextPortB  = 0x07; //next port B output
byte         dispNextPortC  = 0x00; //next port C output

// Setup routine
//===============
void dispSetup() {
  //Initialize the display
  PORTB   &= 0xF8;
  PORTC   |= 0x3F;
  DDRB    |= 0x07;
  DDRC    |= 0x3F;

  //Initialize timer 2
  TCCR2A = 0;                               //normal mode
  //TCCR2A = (1 << WGM21);                  //CTC mode, no pin toggling
  TCCR2B = (1 << CS22) |                    //set timer clock to 15.625kHz
           (1 << CS21) |
           (1 << CS20);
  OCR2A  = 15625/(6*DISP_FPS);              //set interrupt frequency
  OCR2B  = 0;                               //
  TIMSK2 = (1 << OCIE2A);                   //enable output compare A interrupt

  //Initialize default animation routine
  
  //Power modes
  power_timer2_enable();                    //make sure timer2 is powered up
  set_sleep_mode(SLEEP_MODE_IDLE);          //use idle mode
  sleep_enable();                           //enable sleep instruction
}

// Animation Routines
//====================


// Interrupt Service Routines
//============================
ISR(TIMER2_COMPA_vect){                     //timer2 output compare A interrupt
  fields tmpBuf;                            //intermediate display buffer

  digitalWrite(13, HIGH);                   //turn LED on during the execution of the ISR
  //digitalWrite(13, !digitalRead(13));     //turn LED on during the execution of the ISR

  //Prepare next delay 
  //OCR2A += 15625/(6*DISP_FPS);             //set new delay
  OCR2A =  (dispColumn & 1) ?                //compensate for different brightness
    OCR2A + ((15625*0.3)/(6*DISP_FPS)) :     //red
    OCR2A + ((15625*1.7)/(6*DISP_FPS));      //green

  //Serial.println("ISR!");
 
  //Drive previously calculated output
  PORTB |= 0x07;                            //turn off all LEDs
  PORTC  = dispNextPortC;                   //set new anode pattern
  PORTB &= dispNextPortB;                   //select new cathode column  
   
  //Update column
  dispColumn = ((dispColumn + 1) % 6);      //advance column indax

  //Update content
  if ((!dispColumn) {                       //start of freame
    if (dispAnimator == NULL) {             //no custom animator

    //Set solid pattern
    dispRedBuf   = red;
    dispGreenBuf = green;

    //Set scan pattern


    
    
  

  
  
//  if ((!dispColumn) &&
//      (dispAnimator != NULL)) {
//    dispAnimator();   
//#ifdef DISP_FIX
//    tmpBuf       = dispRedBuf;            //handle swapped LEDs
//    dispRedBuf   = 0x01FF & (( DISP_FIX & dispGreenBuf) | (~DISP_FIX & tmpBuf));
//    dispGreenBuf = 0x01FF & ((~DISP_FIX & dispGreenBuf) | ( DISP_FIX & tmpBuf));
//#endif
//  }
    
  //Calculate next port output
  dispNextPortC = (0x20 >> dispColumn);     //set cathode column
  tmpBuf = (dispColumn & 1) ?
    dispRedBuf   >> (dispColumn >> 1) :     //use red buffer
    dispGreenBuf >> (dispColumn >> 1);      //use green buffer
  dispNextPortB =
    ~(((tmpBuf & 0x40) >> 4) |              //set top row
      ((tmpBuf & 0x08) >> 2) |              //set center row
      ( tmpBuf & 0x01));                    //set bottom row

  digitalWrite(13, LOW);                    //turn LED off

}


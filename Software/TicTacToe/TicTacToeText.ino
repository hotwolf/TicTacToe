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
//# Special characters in strings:                                              #
//#    \x80 Loop string output                                                  #
//#    \x81 Use red LEDs                                                        #
//#    \x82 Use green LEDs                                                      #
//#    \x83 Use red and green LEDs                                              #
//#    \x84 Mark the beginning of the loop                                      #
//#                                                                             #
//###############################################################################
//# Version History:                                                            #
//#    March 24, 2017                                                           #
//#      - Initial release                                                      #
//###############################################################################

#include <Arduino.h>
#include <avr/pgmspace.h>
#include "TicTacToe.h"

// Font look-up table
//===================
// A|B|C     15     8 7      0
// -+-+-    +--------+--------+ 
// D|E|F => |-------I|HGFEDCBA| 
// -+-+-    +--------+--------+ 
// G|H|I                                 IHGFEDCBA 
const fields textFontTable[]PROGMEM = {0b000010000, // 0b00 NUL ... ... ... ...
                                       0b000010000, // 0b01 SOH .#. .#. .#. .#.
                                       0b000010000, // 0b02 STX ... ... ... ...
                                       0b000010000, // 0b03 ETX                
				       
                                       0b000010000, // 0b04 EOT ... ... ... ...
                                       0b000010000, // 0b05 ENQ .#. .#. .#. .#.
                                       0b000010000, // 0b06 ACK ... ... ... ...
                                       0b000010000, // 0b07 BEL                
				       
                                       0b000010000, // 0b08 BS  ... ... ... ...
                                       0b000010000, // 0b09 HT  .#. .#. .#. .#.
                                       0b000010000, // 0b0A LF  ... ... ... ...
                                       0b000010000, // 0b0B VT                 
				       
                                       0b000010000, // 0b0C FF  ... ... ... ...
                                       0b000010000, // 0b0D CR  .#. .#. .#. .#.
                                       0b000010000, // 0b0E SO  ... ... ... ...
                                       0b000010000, // 0b0F SI                 
				       
                                       0b000010000, // 0x10 DLE ... ... ... ...
                                       0b000010000, // 0x11 DC1 .#. .#. .#. .#.
                                       0b000010000, // 0x12 DC2 ... ... ... ...
                                       0b000010000, // 0x13 DC3                
				       
                                       0b000010000, // 0x14 DC4 ... ... ... ...
                                       0b000010000, // 0x15 NAK .#. .#. .#. .#.
                                       0b000010000, // 0x16 SYN ... ... ... ...
                                       0b000010000, // 0x17 ETB                
				       
                                       0b000010000, // 0x18 CAN ... ... ... ...
                                       0b000010000, // 0x19 EM  .#. .#. .#. .#.
                                       0b000010000, // 0x1A SUB ... ... ... ...
                                       0b000010000, // 0x1B ESC                
				       
                                       0b000010000, // 0x1C FS  ... ... ... ...
                                       0b000010000, // 0x1D GS  .#. .#. .#. .#.
                                       0b000010000, // 0x1E RS  ... ... ... ...
                                       0b000010000, // 0x1F US                 
				       
                                       0b000000000, // 0x20 SP  ... .#. #.# .#.
                                       0b010010010, // 0x21 !   ... .#. #.# ###
                                       0b000101101, // 0x22 "   ... .#. ... .#.
                                       0b010111010, // 0x23 #	                
				       
                                       0b011010110, // 0x24 $   .## ..# .#. .#.
                                       0b001010100, // 0x25 %   .#. .#. ##. .#.
                                       0b111011010, // 0x26 &   ##. #.. ### ...
                                       0b000010010, // 0x27 '                  
				       
                                       0b010001010, // 0x28 (   .#. .#. ... .#.
                                       0b010100010, // 0x29 )   #.. ..# .#. ###
                                       0b000010000, // 0x2A *   .#. .#. ... .#.
                                       0b010111010, // 0x2B +                   
				       
                                       0b010010000, // 0x2C ,   ... ... ... ..#.
                                       0b000111000, // 0x2D -   .#. ### ... .#..
                                       0b010000000, // 0x2E .   .#. ... .#. #...
                                       0b001010100, // 0x2F /                  .
				       
                                       0b111101111, // 0x30 0   ### .#. ##. ###
                                       0b010010010, // 0x31 1   #.# .#. .#. .##
                                       0b110010011, // 0x32 2   ### .#. .## ###
                                       0b111110111, // 0x33 3                  
				       
                                       0b100111101, // 0x34 4   #.# .## #.. ###
                                       0b011010110, // 0x35 5   ### .#. ### ..#
                                       0b111111001, // 0x36 6   ..# ##. ### ..#
                                       0b100100111, // 0x37 7                   
				       
                                       0b111111011, // 0x38 8   .## ### .#. ...
                                       0b100111111, // 0x39 9   ### ### ... .#.
                                       0b010000010, // 0x3A :   ### ..# .#. .#.
                                       0b010010000, // 0x3B ;                  
				       
                                       0b100010100, // 0x3C <   ..# ### #.. ###
                                       0b111000111, // 0x3D =   .#. ... .#. .##
                                       0b001010001, // 0x3E >   ..# ### #.. .#.
                                       0b010110111, // 0x3F ?                  
				       
                                       0b010111010, // 0x40 @   .#. .#. ##. .## 
                                       0b101111010, // 0x41 A   ### ### ### #.. 
                                       0b111111011, // 0x42 B   .#. #.# ### .## 
                                       0b110001110, // 0x43 C                   
		                                   
                                       0b011101011, // 0x44 D   ##. ### ### ##. 
                                       0b111011111, // 0x45 E   #.# ##. ##. #.# 
                                       0b001011111, // 0x46 F   ##. ### #.. ### 
                                       0b111101011, // 0x47 G                   
		                                   
                                       0b101111101, // 0x48 H   #.# .#. ### #.#
                                       0b010010010, // 0x49 I   ### .#. ..# ##.
                                       0b011100111, // 0x4A J   #.# .#. ##. #.#
                                       0b101011101, // 0x4B K                  
		                                   
                                       0b111001001, // 0x4C L   #.. ### ##. ###
                                       0b101111111, // 0x4D M   #.. ### ### #.#
                                       0b101111011, // 0x4E N   ### #.# #.# ###
                                       0b111101111, // 0x4F O                  
		                                   
                                       0b001111111, // 0x50 P   ### ### ### .##
                                       0b011101111, // 0x51 Q   ### #.# ##. .#.
                                       0b101011111, // 0x52 R   #.. ##. #.# ##.
                                       0b011010110, // 0x53 S                  
		                                   
                                       0b010010111, // 0x54 T   ### #.# #.# #.#
                                       0b111101101, // 0x55 U   .#. #.# #.# ###
                                       0b010101101, // 0x56 V   .#. ### .#. ###
                                       0b111111101, // 0x57 W                  
		                                   
                                       0b101010101, // 0x58 X   #.# #.# ##. ##.
                                       0b010010101, // 0x59 Y   .#. .#. .#. #..
                                       0b110010011, // 0x5A Z   #.# .#. .## ##.
                                       0b011001011, // 0x5B [                  
				       
                                       0b100010001, // 0x5C \   #.. .## .#. ...
                                       0b110100110, // 0x5D ]   .#. ..# #.# ...
                                       0b000101010, // 0x5E ^   ..# .## ... ###
                                       0b111000000, // 0x5F _                  
				       
                                       0b000010010, // 0x60 `   .#. .#. ##. .##
                                       0b101111010, // 0x61 a   .#. ### ### #..
                                       0b111111011, // 0x62 b   ... #.# ### .##
                                       0b110001110, // 0x63 c                  
		                                   
                                       0b011101011, // 0x64 d   ##. ### ### ##.
                                       0b111011111, // 0x65 e   #.# ##. ##. #.#
                                       0b001011111, // 0x66 f   ##. ### #.. ###
                                       0b111101011, // 0x67 g                   
		                                   
                                       0b101111101, // 0x68 h   #.# .#. ### #.#
                                       0b010010010, // 0x69 i   ### .#. ..# ##.
                                       0b011100111, // 0x6A j   #.# .#. ##. #.#
                                       0b101011101, // 0x6B k                  
		                                   
                                       0b111001001, // 0x6C l   #.. ### ##. ###
                                       0b101111111, // 0x6D m   #.. ### ### #.#
                                       0b101111011, // 0x6E n   ### #.# #.# ###
                                       0b111101111, // 0x6F o                  
		                                   
                                       0b001111111, // 0x70 p   ### ### ### .##
                                       0b011101111, // 0x71 q   ### #.# ##. .#.
                                       0b101011111, // 0x72 r   #.. ##. #.# ##.
                                       0b011010110, // 0x73 s                  
		                                   
                                       0b010010111, // 0x74 t   ### #.# #.# #.#
                                       0b111101101, // 0x75 u   .#. #.# #.# ###
                                       0b010101101, // 0x76 v   .#. ### .#. ###
                                       0b111111101, // 0x77 w                  
		                                   
                                       0b101010101, // 0x78 x   #.# #.# ##. .#.
                                       0b010010101, // 0x79 y   .#. .#. .#. #..
                                       0b110010011, // 0x7A z   #.# .#. .## .#.
                                       0b011001011, // 0x7B {
				       
                                       0b010010010, // 0x7C |   .#. .#. ... ...
                                       0b010100010, // 0x7D }   .#. ..# ### .#.
                                       0b000111000, // 0x7E ~   .#. .#. ... ...
                                       0b000010000};// 0x7F DEL




// Constants
//===========
					     
// Variables                                
//===========
byte    textFrameCount;  //determines the duration of each displayed character
char    *textStart;      //start of the string
char    *textRemaining;  //current position of the string
boolean textRed;         //display text with red LEDs
boolean textGreen;       //display text with green LEDs

// Banner control
//================
//Show a string once
// args:   none
// result: nons
void textShow(char *text) {
  textFrameCount = FRAMERATE;
  textStart      = text;
  textRemaining  = text;
  textRed        = false;
  textGreen      = true;
  dispAnimator   = textAnimator; 
}

//Stop showing text
// args:   none
// result: nons
void textStop() {
  dispAnimator = NULL;
}

// Animator
//==========
void textAnimator(fields *redBuf, fields *greenBuf) {
  //Handle special characters
  if (*textRemaining <= 0) {
    //Handle escape characters
    while (((*textRemaining & 0xFF) == 0x80) ||
	   ((*textRemaining & 0xFF) == 0x81) ||
	   ((*textRemaining & 0xFF) == 0x82) ||
	   ((*textRemaining & 0xFF) == 0x83) ||
	   ((*textRemaining & 0xFF) == 0x84)) {
      if ((*textRemaining & 0xFF) == 0x80) {
	//Loop
	textRemaining = textStart;
      } else if ((*textRemaining & 0xFF) == 0x84) {
	//Set loop marker
	textRemaining++;                     //advance to next character    
	textStart = textRemaining;
      } else {
	//Set color
	textRed   = (*textRemaining & 0x01) ? true : false;
	textGreen = (*textRemaining & 0x02) ? true : false;
	textRemaining++;                     //advance to next character    
      }
    }    
    //Handle end of string
    if (*textRemaining == 0) {
      //Stop text display
      dispAnimator = NULL;
      *redBuf   = 0;
      *greenBuf = 0;
    }
  }
    
  //Display character
  if (textFrameCount > (FRAMERATE/16)) {
    //Display character
    fields pattern = pgm_read_word(&textFontTable[*textRemaining & 0x7F]);
    *redBuf   = textRed   ? pattern : 0;
    *greenBuf = textGreen ? pattern : 0;
  } else {
    //Blank diaplay
    *redBuf   = 0;
    *greenBuf = 0;
  }
  
  //Character timing
  if (textFrameCount > 0) {
    textFrameCount--;
  } else {
    //Switch to next character
    textRemaining++;                     //advance to next character    
    textFrameCount = FRAMERATE;
  }
}


/*
 Rainbowduino v3.0 Library. 
 
 2011 Copyright (c) Seeed Technology Inc.
 
 Authors: Albert.Miao, Visweswara R

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/

/*
This library heavily makes use of line, circle and other shape drawing algorithms and code presented
in paper "The Beauty of Bresenham's Algorithm" by Alois Zingl, Vienna, Austria. The original author
has kindly released these example programs with no copyright.
*/

#ifndef _MY9221_H_
#define _MY9221_H_

#include <avr/pgmspace.h>

// MY9221 interfaces 

// DDR
#define MY9221_DI_DDR    DDRC
#define MY9221_DCKI_DDR  DDRC

// PORT
#define MY9221_DI_PORT   PORTC
#define MY9221_DCKI_PORT PORTC

// PIN
#define MY9221_DCKI_PIN  PC0
#define MY9221_DI_PIN    PC1

#define GRAYSCALE_8_BIT   0x00
#define GRAYSCALE_12_BIT  0x01
#define GRAYSCALE_14_BIT  0x10
#define GRAYSCALE_16_BIT  0x11

//#define CMD_MODE 0x00
#define CMD_MODE (GRAYSCALE_16_BIT << 8)

void my9221_init(void);
void my9221_send16bits(uint16_t data);
void my9221_latch(void);
void my9221_clr_disp(void);
// void my9221_blank_disp(void);
// void my9221_setPixelXY(uint8_t x, uint32_t colorRGB /*24-Bit RGB Color*/);

#endif /* _MY9221_H_ */


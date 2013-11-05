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

#define F_CPU 8000000UL
#include <util/delay.h>
#include "my9221.h"

void my9221_init(void)
{
    MY9221_DI_DDR |= _BV(MY9221_DI_PIN);     // set as output
    MY9221_DCKI_DDR |= _BV(MY9221_DCKI_PIN); // set as output

    MY9221_DI_PORT &= ~_BV(MY9221_DI_PIN);     // Low
    MY9221_DCKI_PORT &= ~_BV(MY9221_DCKI_PIN); // Low

    my9221_clr_disp();
}

// send 16 bits data to MY9221

void my9221_send16bits(uint16_t data)
{
    uint8_t i;

    for(i=0; i<16; i++)
    {
        if(data & 0x8000)
            MY9221_DI_PORT |= _BV(MY9221_DI_PIN);
        else
            MY9221_DI_PORT &= ~_BV(MY9221_DI_PIN);

        MY9221_DCKI_PORT ^= _BV(MY9221_DCKI_PIN);
        data <<= 1;
    }
}

// latch data

void my9221_latch(void)
{
    MY9221_DI_PORT &= ~_BV(MY9221_DI_PIN); // Low

    _delay_us(200);

    for(uint8_t i=0; i<8; i++)
        MY9221_DI_PORT ^= _BV(MY9221_DI_PIN);
}

// clear MY9221
// internally used for avoiding flicker. This is not the same as blank disply.

void my9221_clr_disp(void)
{
    uint8_t i = 0;

    my9221_send16bits(CMD_MODE);
    MY9221_DI_PORT &= ~_BV(MY9221_DI_PIN); // Low

    // send train of 0s
    for(i=0; i<192; i++)
        MY9221_DCKI_PORT ^= _BV(MY9221_DCKI_PIN);

    my9221_send16bits(CMD_MODE);

    MY9221_DI_PORT &= ~_BV(MY9221_DI_PIN); // Low

    // send train of 0s
    for(i=0; i<192; i++)
        MY9221_DCKI_PORT ^= _BV(MY9221_DCKI_PIN);

    my9221_latch();
}

// set the pixel (X,Y) of RGB matrix with colour 24-bit RGB Colour 
/*24-bit RGB Color*/
/*
void my9221_setPixelXY(uint8_t x, uint32_t colorRGB
{
    colorRGB = (colorRGB & 0x00FFFFFF);
    frameBuffer[0][x][y]=(colorRGB & 0x0000FF); //channel Blue
    colorRGB = (colorRGB >> 8);
    frameBuffer[1][x][y]=(colorRGB & 0x0000FF); //channel Green
    colorRGB = (colorRGB >> 8);
    frameBuffer[2][x][y]=(colorRGB & 0x0000FF); //channel Red
}
*/

//set the pixel (X,Y) of RGB matrix with colours R,G,B 
/*
void my_setPixelXY(unsigned char x, unsigned char y, unsigned char  colorR,  unsigned char colorG, unsigned char colorB)
{
    frameBuffer[0][x][y]= colorB ; //channel Blue
    frameBuffer[1][x][y]= colorG ; //channel Green
    frameBuffer[2][x][y]= colorR ; //channel Red
}
*/


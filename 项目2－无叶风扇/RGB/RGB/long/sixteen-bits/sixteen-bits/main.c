/*
 * 一共 208 位
 * 数据 12*16 = 192 bits
 * command: 16 bits
 *
 *
 *
 * 输出顺序 OUT3 OUT2 OUT1 OUT0
 * 颜色顺序 RGB
 */
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "my9221.h"

volatile uint16_t timer_1s_counter;
volatile uint8_t time_1s_ok;
// These variables store the current time.
volatile uint8_t time_s = 3, time_m = 11, time_h = 10;
// ... and current date
volatile uint8_t date_m, date_d, date_y;

uint16_t buffer[13]; // 26 个整数(占用 52 字节ram)
// [cmd][r][g][b] [r][g][b] [r][g][b] [r][g][b]
// [cmd][r][g][b] [r][g][b] [r][g][b] [r][g][b]

/*
PROGMEM struct color_tab {
    uint8_t color;
    uint16_t rgb[3];
}table[4] = {
*/

// resistor color code
// http://www.december.com/html/spec/colorcodes.html
uint16_t color_tab[10][3] = {
{0x0000, 0x0000, 0x0000},  // 0 black  rgb(0%, 0%, 0%)
{0x8CCC, 0x2666, 0x0000}, // 1 brown rgb(50%, 16%, 16%)  
//{0x7FFF, 0x2F85, 0x2F85}, // brown (SVG)  rgb(65%, 16%, 16%)
{0xFFFF, 0x0000, 0x0000},  // 2 red  rgb(100%, 0%, 0%)
{0xFFFF, 0xA665, 0x0000},  // 3 orange (SVG) rgb(100%, 65%, 0%)
{0xFFFF, 0xFFFF, 0x0000},  // 4 yellow rgb(100%, 100%, 0%) 
{0x0000, 0xFFFF, 0x0000},  // 5 green  rgb(0%, 100%, 0%)
{0x0000, 0x0000, 0xFFFF},  // 6 blue   rgb(0%, 0%, 100%)
//{0x7FFF, 0x0000, 0x7FFF},  // 7 violet/purple rgb(50%, 0%, 50%)
{0xEE13, 0x828E, 0xEE13}, // violet (SVG) rgb(93%, 51%, 93%)
{0x3333, 0x3333, 0x3333},  // 8 gray
{0xFFFF, 0xFFFF, 0xFFFF},  // 9 white (100%, 100%, 100%)
};

uint8_t time[6];

// Convert temperature to display buffer
void time2buffer(void)
{
    buffer[0] = CMD_MODE;

    buffer[1] = color_tab[time[0]][0];
    buffer[2] = color_tab[time[0]][1];
    buffer[3] = color_tab[time[0]][2];

    buffer[4] = color_tab[time[1]][0];
    buffer[5] = color_tab[time[1]][1];
    buffer[6] = color_tab[time[1]][2];

    buffer[7] = color_tab[time[2]][0];
    buffer[8] = color_tab[time[2]][1];
    buffer[9] = color_tab[time[2]][2];

    buffer[10] = color_tab[time[0]][0];
    buffer[11] = color_tab[time[0]][1];
    buffer[12] = color_tab[time[0]][2];
}

void refresh_led(void)
{
    uint8_t i;

    for (i=0; i<13; i++)
        my9221_send16bits(buffer[i]);

    my9221_latch();
}

// This displays a time on the clock
void display_time(uint8_t h, uint8_t m, uint8_t s)
{
    time[0] =  s % 10;
    time[1] =  s / 10;

    time[2] =  m % 10;
    time[3] =  m / 10;

    time[4] =  (h%24) % 10;
    time[5] =  (h%24) / 10;
}


void timer0_init(void)
{
    // Timer/Counter0 initialization
    TCCR0B = 0x03; // Clock set to clk/64
    TCNT0 = 0;    // Start timer0 at 0
    TIMSK0 = 1;
}

// Timer/Counter 0 Overflow Interrupt ISR
ISR(TIMER0_OVF_vect)
{
    TCNT0 = 6;  // Reload timer0 for next period, a period = 2ms

    // refresh();  // Scan LED matrix
    
    if (timer_1s_counter++ >= 500) {
        time_1s_ok++;
        refresh_led();  // Scan LED matrix
        timer_1s_counter = 0;

        time_s++;             // one second has gone by

        // a minute!
        if (time_s >= 60) {
            time_s = 0;
            time_m++;
        }

        // an hour...
        if (time_m >= 60) {
            time_m = 0;
            time_h++;
            // lets write the time to the EEPROM
        }

        // a day....
        if (time_h >= 24) {
            time_h = 0;
            date_d++;
        }
    }
}


void main(void)
{
    my9221_init();
    timer0_init();
    sei();

    while (1)
    {
        display_time(time_h, time_m, time_s);
        time2buffer();
    }
}


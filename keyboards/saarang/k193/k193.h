/* Copyright 2020 Jayesh Vora
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2c_master.h"
#include <util/delay.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00

// I2C aliases and register addresses`
#define I2C_ADDR                0b0100000       // Address of MCP23018 slave device on Right Keypad; Note that Addr pin is tied to GND.
#define I2C_ADDR_NUMBER_KEYPAD     0b0100111    // Address of MCP23018 slave device on Number Keypad; Note that Addr pin is tied to VDD.
#define I2C_ADDR_WRITE  ( (I2C_ADDR<<1) | I2C_WRITE )
#define I2C_ADDR_READ   ( (I2C_ADDR<<1) | I2C_READ  )
#define I2C_ADDR_NUMBER_KEYPAD_WRITE  ( (I2C_ADDR_NUMBER_KEYPAD<<1) | I2C_WRITE )
#define I2C_ADDR_NUMBER_KEYPAD_READ   ( (I2C_ADDR_NUMBER_KEYPAD<<1) | I2C_READ  )
#define IODIRA          0x00            // i/o direction register
#define IODIRB          0x01
#define GPPUA           0x0C            // GPIO pull-up resistor register
#define GPPUB           0x0D
#define GPIOA           0x12            // general purpose i/o port register (write modifies OLAT)
#define GPIOB           0x13
#define OLATA           0x14            // output latch register
#define OLATB           0x15

extern i2c_status_t mcp23018_status;            // status of MCP23018 on Right Keypad
extern i2c_status_t mcp23018_status_number_keypad; // status of MCP23018 on Number Keypad

extern bool is_right_keypad_present;
extern bool is_number_keypad_present;

#define K19_I2C_TIMEOUT 100

// TO DO
//#define UNICODE_WINC_KEY KC_LALT

void init_k19(void);
void k19_blink_all_leds(void);
uint8_t init_mcp23018(void);
uint8_t init_mcp23018_number_keypad(void);
uint8_t k19_left_leds_update(void);

// We do not change LED brightness levels
/*
#ifndef LED_BRIGHTNESS_LO
#define LED_BRIGHTNESS_LO       15
#endif
#ifndef LED_BRIGHTNESS_HI
#define LED_BRIGHTNESS_HI       255
#endif
*/

/* To turn on the LED, set both DDR bit and Port bit to 1 */
inline void k19_shift_led_on(void)      { writePinHigh(B7); }
inline void k19_ralt_led_on(void)       { writePinHigh(D7); }
inline void k19_ctrl_led_on(void)       { writePinHigh(D6); }
inline void k19_lalt_led_on(void)       { writePinHigh(B4); }
inline void k19_l1_led_on(void)         { writePinHigh(C7); }
inline void k19_num_led_on(void)        { writePinHigh(C6); }
inline void k19_caps_led_on(void)       { writePinHigh(B6); }
inline void k19_media_led_on(void)      { writePinHigh(B5); }


//inline void ergodox_right_led_on(uint8_t led) { DDRB |= (1<<(led+4)); PORTB |= (1<<(led+4)); }

/* To turn off the LED, set both DDR bit and Port bit to 0 */
inline void k19_shift_led_off(void)     { writePinLow(B7); }
inline void k19_ralt_led_off(void)      { writePinLow(D7); }
inline void k19_ctrl_led_off(void)      { writePinLow(D6); }
inline void k19_lalt_led_off(void)      { writePinLow(B4); }
inline void k19_l1_led_off(void)        { writePinLow(C7); }
inline void k19_num_led_off(void)       { writePinLow(C6); }
inline void k19_caps_led_off(void)      { writePinLow(B6); }
inline void k19_media_led_off(void)     { writePinLow(B5); }


//inline void ergodox_right_led_off(uint8_t led) { DDRB &= ~(1<<(led+4)); PORTB &= ~(1<<(led+4)); }

inline void k19_all_led_on(void)
{
    k19_shift_led_on();
    k19_ralt_led_on();
    k19_ctrl_led_on();
    k19_lalt_led_on();
    k19_l1_led_on();
    k19_num_led_on();
    k19_caps_led_on();
    k19_media_led_on();
}

inline void k19_all_led_off(void)
{
    k19_shift_led_off();
    k19_ralt_led_off();
    k19_ctrl_led_off();
    k19_lalt_led_off();
    k19_l1_led_off();
    k19_num_led_off();
    k19_caps_led_off();
    k19_media_led_off();
}

/* These are probably for PWM purpose. As PWM is not enabled, so commenting them out
inline void k19_ctrl_led_set(uint8_t n)       { OCR1AL = n; }
inline void k19_alt_led_set(uint8_t n)        { OCR1AH = n; }
inline void k19_shift_led_set(uint8_t n)      { OCR1BL = n; }
inline void k19_dvorak_led_set(uint8_t n)     { OCR1BH = n; }
inline void k19_media_led_set(uint8_t n)      { OCR1CL = n; }
inline void k19_num_led_set(uint8_t n)        { OCR3AL = n; }
inline void k19_caps_led_set(uint8_t n)       { OCR3AH = n; }

inline void ergodox_right_led_set(uint8_t led, uint8_t n)  {
    (led == 1) ? (OCR1A = n) :
    (led == 2) ? (OCR1B = n) :
                 (OCR1C = n);
}

inline void k19_all_led_set(uint8_t n)
{
    k19_ctrl_led_set(n);
    k19_alt_led_set(n);
    k19_shift_led_set(n);
    k19_dvorak_led_set(n);
    k19_media_led_set(n);
    k19_num_led_set(n);
    k19_caps_led_set(n);
}
*/

/*  -------- LEFT KEY PAD ------------      --------- RIGHT KEY PAD ----------      --- NUMBER KEY PAD --- */
#define LAYOUT_k19(                                                                                                 \
    LA1, LA2, LB1, LC1, LD1, LE1, LF1, LG1,     RA1, RB1, RC1, RD1, RE1, RF1, RG2, RG1,                             \
         LA3, LB3, LC2, LD2, LE2, LF2, LG3,     RA3, RB2, RC2, RD2, RE2, RF3, RG3,          NA2, NB2, NC2, ND3,     \
         LA4, LB4, LC3, LD3, LE3, LF3, LG4,     RA4, RB3, RC3, RD3, RE3, RF4, RG4,          NA3, NB3, NC3, ND4,     \
         LA5, LB5, LC4, LD4, LE4, LF4, LG5,     RA5, RB4, RC4, RD4, RE4, RF5, RG5,          NA4, NB4, NC4, ND5,     \
         LA6, LB6, LC5, LD5, LE5, LF5, LG6,     RA6, RB5, RC5, RD5, RE5, RF6, RG6,          NA5, NB5, NC5, ND6,     \
              LB7, LC6, LD6, LE6, LF6, LG7,     RA7, RB6, RC6, RD6, RE6, RF7,               NA6, NB6, NC6,          \
                   LC7, LD7, LE7,                         RC7, RD7, RE7)                                            \
                                                                                                                    \
   /* matrix positions */                                                                                           \
    {                                                                                                               \
    { LA1, LB1, LC1, LD1, LE1, LF1, LG1,    RA1, RB1, RC1, RD1, RE1, RF1, RG1,          KC_NO,KC_NO,KC_NO,KC_NO},   \
    { LA2,KC_NO,LC2, LD2, LE2, LF2,KC_NO,   KC_NO,RB2,RC2, RD2, RE2,KC_NO,RG2,          NA2,  NB2,  NC2,  KC_NO},   \
    { LA3, LB3, LC3, LD3, LE3, LF3, LG3,    RA3, RB3, RC3, RD3, RE3, RF3, RG3,          NA3,  NB3,  NC3,  ND3 },    \
    { LA4, LB4, LC4, LD4, LE4, LF4, LG4,    RA4, RB4, RC4, RD4, RE4, RF4, RG4,          NA4,  NB4,  NC4,  ND4 },    \
    { LA5, LB5, LC5, LD5, LE5, LF5, LG5,    RA5, RB5, RC5, RD5, RE5, RF5, RG5,          NA5,  NB5,  NC5,  ND5 },    \
    { LA6, LB6, LC6, LD6, LE6, LF6, LG6,    RA6, RB6, RC6, RD6, RE6, RF6, RG6,          NA6,  NB6,  NC6,  ND6 },    \
    { KC_NO,LB7,LC7, LD7, LE7,KC_NO,LG7,    RA7,KC_NO,RC7, RD7, RE7, RF7,KC_NO,         KC_NO,KC_NO,KC_NO,KC_NO},   \
    }

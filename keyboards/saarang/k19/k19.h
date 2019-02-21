/* Copyright 2019 Jayesh Vora
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

#ifndef K19_H
#define K19_H

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2c_master.h"
#include <util/delay.h>

#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz       0x00

// I2C aliases and register addresses (see "mcp23018.md")
#define I2C_ADDR        0b0100000
#define I2C_ADDR_WRITE  ( (I2C_ADDR<<1) | I2C_WRITE )
#define I2C_ADDR_READ   ( (I2C_ADDR<<1) | I2C_READ  )
#define IODIRA          0x00            // i/o direction register
#define IODIRB          0x01
#define GPPUA           0x0C            // GPIO pull-up resistor register
#define GPPUB           0x0D
#define GPIOA           0x12            // general purpose i/o port register (write modifies OLAT)
#define GPIOB           0x13
#define OLATA           0x14            // output latch register
#define OLATB           0x15

extern i2c_status_t mcp23018_status;

#define K19_I2C_TIMEOUT 100

// TO DO
//#define UNICODE_WINC_KEY KC_LALT

void init_k19(void);
void k19_blink_all_leds(void);
uint8_t init_mcp23018(void);
uint8_t k19_left_leds_update(void);

#ifndef LED_BRIGHTNESS_LO
#define LED_BRIGHTNESS_LO       15
#endif
#ifndef LED_BRIGHTNESS_HI
#define LED_BRIGHTNESS_HI       255
#endif

/* To turn on the LED, set both DDR bit and Port bit to 1 */
inline void k19_ctrl_led_on(void)       { writePinHigh(B6); }
inline void k19_alt_led_on(void)        { writePinHigh(B5); }
inline void k19_shift_led_on(void)      { writePinHigh(D7); }
inline void k19_spch_led_on(void)       { writePinHigh(D6); }
inline void k19_media_led_on(void)      { writePinHigh(D5); }
inline void k19_game_led_on(void)       { writePinHigh(C7); }
inline void k19_num_led_on(void)        { writePinHigh(C6); }
inline void k19_caps_led_on(void)       { writePinHigh(B7); }

//inline void ergodox_right_led_on(uint8_t led) { DDRB |= (1<<(led+4)); PORTB |= (1<<(led+4)); }

/* To turn off the LED, set both DDR bit and Port bit to 0 */
inline void k19_ctrl_led_off(void)      { writePinLow(B6); }
inline void k19_alt_led_off(void)       { writePinLow(B5); }
inline void k19_shift_led_off(void)     { writePinLow(D7); }
inline void k19_spch_led_off(void)      { writePinLow(D6); }
inline void k19_media_led_off(void)     { writePinLow(D5); }
inline void k19_game_led_off(void)      { writePinLow(C7); }
inline void k19_num_led_off(void)       { writePinLow(C6); }
inline void k19_caps_led_off(void)      { writePinLow(B7); }

//inline void ergodox_right_led_off(uint8_t led) { DDRB &= ~(1<<(led+4)); PORTB &= ~(1<<(led+4)); }

inline void k19_all_led_on(void)
{
    k19_ctrl_led_on();
    k19_alt_led_on();
    k19_shift_led_on();
    k19_spch_led_on();
    k19_media_led_on();
    k19_game_led_on();
    k19_num_led_on();
    k19_caps_led_on();
}

inline void k19_all_led_off(void)
{
    k19_ctrl_led_off();
    k19_alt_led_off();
    k19_shift_led_off();
    k19_spch_led_off();
    k19_media_led_off();
    k19_game_led_off();
    k19_num_led_off();
    k19_caps_led_off();
}

/* Not sure about use of these methods; so commenting them out for now
inline void k19_ctrl_led_set(uint8_t n)       { OCR1AL = n; }
inline void k19_alt_led_set(uint8_t n)        { OCR1AH = n; }
inline void k19_shift_led_set(uint8_t n)      { OCR1BL = n; }
inline void k19_spch_led_set(uint8_t n)       { OCR1BH = n; }
inline void k19_media_led_set(uint8_t n)      { OCR1CL = n; }
inline void k19_game_led_set(uint8_t n)       { OCR1CH = n; }
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
    k19_spch_led_set(n);
    k19_media_led_set(n);
    k19_game_led_set(n);
    k19_num_led_set(n);
    k19_caps_led_set(n);
}
*/

/*  ---------- LEFT HAND -----------   ---------- RIGHT HAND ---------- */
#define LAYOUT_k19(                                                     \
    L7A,L6B,L7B,L7C,L7D,L7E,L7F,           R7A,R7B,R7C,R7D,R7E,R6E,R7F, \
    L6A,            L6D,L6E,L6F,           R6A,R6B,R6C,            R6F, \
    L5A,    L5B,L6C,L5D,L5E,L5F,           R5A,R5B,R5C,R6D,R5E,    R5F, \
        L4A,L4B,L5C,L4D,L4E,L4F,           R4A,R4B,R4C,R5D,R4E,R4F,     \
        L3A,L3B,L4C,L3D,L3E,L3F,           R3A,R3B,R3C,R4D,R3E,R3F,     \
        L2A,L2B,L3C,L2D,L2E,L2F,           R2A,R2B,R2C,R3D,R2E,R2F,     \
        L1A,        L1E,    L1F,           R1A,    R1B,    R2D,R1F,     \
                                                       R1C,R1D,R1E)     \
                                                                        \
   /* matrix positions */                   \
    {                                       \
    { L7A, L7B, L7C, L7D, L7E, L7F, R7A, R7B, R7C, R7D, R7E, R7F },       \
    { L6A, L6B, L6C, L6D, L6E, L6F, R6A, R6B, R6C, R6D, R6E, R6F },       \
    { L5A, L5B, L5C, L5D, L5E, L5F, R5A, R5B, R5C, R5D, R5E, R5F },       \
    { L4A, L4B, L4C, L4D, L4E, L4F, R4A, R4B, R4C, R4D, R4E, R4F },       \
    { L3A, L3B, L3C, L3D, L3E, L3F, R3A, R3B, R3C, R3D, R3E, R3F },       \
    { L2A, L2B, KC_NO, L2D, L2E, L2F, R2A, R2B, R2C, R2D, R2E, R2F },     \
    { L1A, KC_NO, KC_NO, KC_NO, L1E, L1F, R1A, R1B, R1C, R1D, R1E, R1F }, \
    }

#endif

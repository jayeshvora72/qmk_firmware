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

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x04D8
#define PRODUCT_ID      0xEDCD
#define DEVICE_VER      0x0001
#define MANUFACTURER    Saarang Innovation
#define PRODUCT         Saarang K19
#define DESCRIPTION     Ergonomic Split Keyboard

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 12
#define MATRIX_COLS_PER_SIDE (MATRIX_COLS / 2)

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, bottom to top
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/

/*
 * In the PCB design the rows are numbered as one to seven moving from bottom to top,
 * however, the QMK software starts numbering of the rows from top to bottom, that
 * means for QMK the top most row is row-one and the bottom most row is row-seven.
 * Keeing this in mind, the ordering of rows has been reversed in MATRIX_ROW_PINS
 * as compared to the circuit schematic.
 */
#define MATRIX_ROW_PINS { D5, D3, D2, B3, B2, B1, B0 }
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7 }
#define UNUSED_PINS     { B4, D4, E6 }

/* COL2ROW, ROW2COL, or CUSTOM_MATRIX */
#define DIODE_DIRECTION COL2ROW

#define ONESHOT_TAP_TOGGLE 2  /* Tapping this number of times holds the key until tapped once again. */
#define ONESHOT_TIMEOUT 5000  /* Time (in ms) before the one shot key is released */

#define UNICODE_WINC_KEY KC_LALT

/*
#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_DELAY          0
#define MOUSEKEY_TIME_TO_MAX    60
#define MOUSEKEY_MAX_SPEED      7
#define MOUSEKEY_WHEEL_DELAY 0
*/

#define TAPPING_TOGGLE  1

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

#define TAPPING_TERM    200
#define IGNORE_MOD_TAP_INTERRUPT // this makes it possible to do rolling combos (zx) with keys that convert to other keys on hold (z becomes ctrl when you hold it, and when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x. That's bad.)

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || \
    keyboard_report->mods == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) \
)

/* number of backlight levels */

#define BACKLIGHT_LEVELS 3

#ifndef LED_BRIGHTNESS_LO
#define LED_BRIGHTNESS_LO       15
#endif
#ifndef LED_BRIGHTNESS_HI
#define LED_BRIGHTNESS_HI       255
#endif
#define LED_BRIGHTNESS_DEFAULT (LED_BRIGHTNESS_HI)


/* ws2812 RGB LED */
/*
#define RGB_DI_PIN D7
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 15     // Number of LEDs
#define RGBLIGHT_HUE_STEP 12
#define RGBLIGHT_SAT_STEP 255
#define RGBLIGHT_VAL_STEP 12
*/

/* fix space cadet rollover issue */
#define DISABLE_SPACE_CADET_ROLLOVER

/*
#define RGBW_BB_TWI

#define RGBW 1
*/

/*
 * The debounce filtering reports a key/switch change directly,
 * without any extra delay. After that the debounce logic will filter
 * all further changes, until the key/switch reports the same state for
 * the given count of scans.
 * So a perfect switch will get a short debounce period and
 * a bad key will get a much longer debounce period.
 * The result is an adaptive debouncing period for each switch.
 *
 * If you don't define it here, the matrix code will default to
 * 5, which is now closer to 10ms, but still plenty according to
 * manufacturer specs.
 */
#define DEBOUNCE    10

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCING_DELAY 5


#define USB_MAX_POWER_CONSUMPTION 500

// RGB backlight
/*
#define DRIVER_ADDR_1 0b1110100
#define DRIVER_ADDR_2 0b1110111
#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 24
#define DRIVER_2_LED_TOTAL 24
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL
#define RGB_MATRIX_SKIP_FRAMES 10
*/

// #define RGBLIGHT_COLOR_LAYER_0 0x00, 0x00, 0xFF
/* #define RGBLIGHT_COLOR_LAYER_1 0x00, 0x00, 0xFF */
/* #define RGBLIGHT_COLOR_LAYER_2 0xFF, 0x00, 0x00 */
/* #define RGBLIGHT_COLOR_LAYER_3 0x00, 0xFF, 0x00 */
/* #define RGBLIGHT_COLOR_LAYER_4 0xFF, 0xFF, 0x00 */
/* #define RGBLIGHT_COLOR_LAYER_5 0x00, 0xFF, 0xFF */
/* #define RGBLIGHT_COLOR_LAYER_6 0xFF, 0x00, 0xFF */
/* #define RGBLIGHT_COLOR_LAYER_7 0xFF, 0xFF, 0xFF */

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
//#define DEBUG_MATRIX_SCAN_RATE


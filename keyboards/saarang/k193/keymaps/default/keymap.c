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


#include QMK_KEYBOARD_H

#define ____ KC_TRNS

/*
#define BASE    0   // Default QWERTY layer
#define NUMBER  1   // Number Layer
#define MEDIA   2   // Multi Media Layer
*/
enum layers {
  BASE,
  NUMBER,
  MEDIA
};

// Though the custom keycode of EPRM is not used currently, have still maintained it here
enum custom_keycodes {
  EPRM = SAFE_RANGE
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Default QWERTY layer
 *
 * ---------------------------------    ------------------------------------
 * |   |Med|F1 |F2 |F3 |F4 |F5 |F6  |   |F7  |F8 |F9 |F10|F11|F12|PrSc|Paus|
 * |---+---+---+---+---+---+---+----|   |----+---+---+---+---+---+----+----|    -----------------
 *     | ` | 1 | 2 | 3 | 4 | 5 |Caps|   |Num | 6 | 7 | 8 | 9 | 0 | \  |         |Tab| / | * |Bspc|
 *     |---+---+---+---+---+---+----|   |----+---+---+---+---+---+----|         |---+---+---+----|
 *     |Esc| Q | W | E | R | T |PgUp|   |Home| Y | U | I | O | P |Bspc|         | 7 | 8 | 9 | -  |
 *     |---+---+---+---+---+---+----|   |----+---+---+---+---+---+----|         |---+---+---+----|
 *     |Tab| A | S | D | F | G |PgDn|   |End | H | J | K | L | ; |Ent |         | 4 | 5 | 6 | +  |
 *    |----+---+---+---+---+---+----|   |----+---+---+---+---+---+----|         |---+---+---+----|
 *    |Shft| Z | X | C | V | B |Ins |   |Ctrl| N | M | , | . | / |Shft|         | 1 | 2 | 3 |Ent |
 *    |----+---+---+---+---+---+----|   |----+---+---+---+---+---+----|         |---+---+---+----|
 *         |Win| = | - | ' |Spc|Del |   |Alt |Spc| [ |Up | ] |Win|              | 0 | , | . |
 *         |---+---+---+---+---+----|   |----+---+---+---+---+---|              -------------
 *             |Alt|App|Ctrl|                    |Lft|Dn |Rt |
 *             --------------                    -------------
 *
 */
[BASE] = LAYOUT_k19(
  ____,TG(MEDIA),   KC_F1, KC_F2, KC_F3,    KC_F4,  KC_F5, KC_F6,          KC_F7,     KC_F8, KC_F9,  KC_F10, KC_F11, KC_F12, KC_PSCR, KC_PAUS,
       KC_GRV,      KC_1,  KC_2,  KC_3,     KC_4,   KC_5,  KC_CAPS,        TG(NUMBER),KC_6,  KC_7,   KC_8,   KC_9,   KC_0,   KC_BSLS,              KC_TAB,  KC_PSLS, KC_PAST, KC_BSPC,
       KC_ESC,      KC_Q,  KC_W,  KC_E,     KC_R,   KC_T,  KC_PGUP,        KC_HOME,   KC_Y,  KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,              KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
       KC_TAB,      KC_A,  KC_S,  KC_D,     KC_F,   KC_G,  KC_PGDN,        KC_END,    KC_H,  KC_J,   KC_K,   KC_L,   KC_SCLN,KC_ENT,               KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
       OSM(MOD_LSFT),KC_Z, KC_X,  KC_C,     KC_V,   KC_B,  KC_INS,      OSM(MOD_RCTL),KC_N,  KC_M,   KC_COMM,KC_DOT, KC_SLSH,OSM(MOD_RSFT),        KC_P1,   KC_P2,   KC_P3,   KC_ENT,
                    KC_LWIN,KC_EQL,KC_MINS,  KC_QUOT,KC_SPC,KC_DEL,     OSM(MOD_RALT),KC_SPC,KC_LBRC,KC_UP,  KC_RBRC,KC_RWIN,                      KC_P0,   KC_COMM, KC_PDOT,
                    OSM(MOD_LALT),KC_APP,   OSM(MOD_LCTL),                                   KC_LEFT,KC_DOWN,KC_RIGHT
),

/* Keymap 1: Number layer
 *
 * ---------------------------------      ---------------------------------
 * |   |   |   |   |   |   |   |   |      |   |   |   |   |   |   |   |   |
 * |---+---+---+---+---+---+---+---|      |---+---+---+---+---+---+---+---|     -----------------
 *     |   |   |   |   |   |   |   |      |   |   |Tab| / | * |   |   |         |   |   |   |   |
 *     |---+---+---+---+---+---+---|      |---+---+---+---+---+---+---|         |---+---+---+---|
 *     |   |   |   |   |   |   |   |      |   |   | 7 | 8 | 9 | - |   |         |   |   |   |   |
 *     |---+---+---+---+---+---+---|      |---+---+---+---+---+---+---|         |---+---+---+---|
 *     |   |   |   |   |   |   |   |      |   |   | 4 | 5 | 6 | + |   |         |   |   |   |   |
 *     |---+---+---+---+---+---+---|      |---+---+---+---+---+---+---|         |---+---+---+---|
 *     |   |   |   |   |   |   |   |      |   |   | 1 | 2 | 3 | , |   |         |   |   |   |   |
 *     |---+---+---+---+---+---+---|      |---+---+---+---+---+---+---|         |---+---+---+---|
 *         |   |   |   |   |   |   |      |   |   | 0 |   | . |   |             |   |   |   |
 *         |---+---+---+---+---+---|      |---+---+---+---+---+---|             -------------
 *             |   |   |   |                      |   |   |   |
 *             -------------                      -------------
 *
 */
[NUMBER] = LAYOUT_k19(
  ____, ____, ____, ____, ____, ____, ____, ____,     ____, ____, ____,    ____,    ____,    ____,    ____, ____,
        ____, ____, ____, ____, ____, ____, ____,     ____, ____, KC_TAB,  KC_PSLS, KC_PAST, ____,    ____,          ____, ____, ____, ____,
        ____, ____, ____, ____, ____, ____, ____,     ____, ____, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, ____,          ____, ____, ____, ____,
        ____, ____, ____, ____, ____, ____, ____,     ____, ____, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, ____,          ____, ____, ____, ____,
        ____, ____, ____, ____, ____, ____, ____,     ____, ____, KC_P1,   KC_P2,   KC_P3,   KC_COMM, ____,          ____, ____, ____, ____,
              ____, ____, ____, ____, ____, ____,     ____, ____, KC_P0,   ____,    KC_PDOT, ____,                   ____, ____, ____,
                    ____, ____, ____,                             ____,    ____,    ____
),
/* Keymap 2: Media Layer
 *
 * -----------------------------------------      ---------------------------------
 * |    |    |Mute|VolD|VolU|PrTr|PlPs|NxTr|      |   |   |   |   |   |   |   |   |
 * |----+----+----+----+----+----+----+----|      |---+---+---+---+---+---+---+---|     -----------------
 *      |    |    |    |    |    |    |    |      |   |   |   |   |   |   |   |         |   |   |   |   |
 *      |----+----+----+----+----+----+----|      |---+---+---+---+---+---+---|         |---+---+---+---|
 *      |    |    |    |    |    |    |    |      |   |   |   |   |   |   |   |         |   |   |   |   |
 *      |----+----+----+----+----+----+----|      |---+---+---+---+---+---+---|         |---+---+---+---|
 *      |    |    |    |    |    |    |    |      |   |   |   |   |   |   |   |         |   |   |   |   |
 *      |----+----+----+----+----+----+----|      |---+---+---+---+---+---+---|         |---+---+---+---|
 *      |    |    |    |    |    |    |    |      |   |   |   |   |   |   |   |         |   |   |   |   |
 *      |----+----+----+----+----+----+----|      |---+---+---+---+---+---+---|         |---+---+---+---|
 *           |    |    |    |    |    |    |      |   |   |   |   |   |   |             |   |   |   |
 *           |----+----+----+----+----+----|      |---+---+---+---+---+---|             -------------
 *                |    |    |    |                        |   |   |   |
 *                ----------------                        -------------
 */
[MEDIA] = LAYOUT_k19(
  ____, ____, KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT,     ____, ____, ____, ____, ____, ____, ____, ____,
        ____, ____,    ____,    ____,    ____,    ____,    ____,        ____, ____, ____, ____, ____, ____, ____,           ____, ____, ____, ____,
        ____, ____,    ____,    ____,    ____,    ____,    ____,        ____, ____, ____, ____, ____, ____, ____,           ____, ____, ____, ____,
        ____, ____,    ____,    ____,    ____,    ____,    ____,        ____, ____, ____, ____, ____, ____, ____,           ____, ____, ____, ____,
        ____, ____,    ____,    ____,    ____,    ____,    ____,        ____, ____, ____, ____, ____, ____, ____,           ____, ____, ____, ____,
              ____,    ____,    ____,    ____,    ____,    ____,        ____, ____, ____, ____, ____, ____,                 ____, ____, ____,
                       ____,    ____,    ____,                                      ____, ____, ____
),
};

/*
const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};
*/

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case EPRM:
        eeconfig_init();
        return false;
    }
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

// Runs whenever there is a layer state change.
uint32_t layer_state_set_user(uint32_t state) {

  // turn off all layers related LEDs.
  k19_num_led_off();
  k19_media_led_off();

  // Check if BASE layer is enabled
  if (state & 1) {
    // do nothing as we are checking for the BASE layer, i.e. QWERTY layer, no LEDs to be turned on
  }

  // check if number layer is enabled
  if (state & 2) {
    k19_num_led_on();
  }

  // check if media layer is enabled
  if (state & 4) {
    k19_media_led_on();
  }

  return state;
};

void led_set_user(uint8_t usb_led) {
  // do nothing
}

/*
void eeconfig_init_user(void) {
  set_unicode_input_mode(UC_WINC);
}
*/

void oneshot_layer_changed_user(uint8_t layer) {
// do nothing
/*
  if (layer == SYMBOL) {
    k19_symbol_led_on();
  }
  if (!layer) {
    k19_symbol_led_off();
  }
*/
}

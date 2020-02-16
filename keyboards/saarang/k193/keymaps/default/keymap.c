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


#include QMK_KEYBOARD_H

#define ____ KC_TRNS

/*
#define BASE    0   // Default QWERTY layer
#define NUMBER  1   // Number Layer
#define MEDIA   2   // Multi Media Layer
#define DVORAK  3   // Dvorak Layer
*/
enum layers {
  BASE,
  NUMBER,
  MEDIA,
  DVORAK
};

// Though the custom keycode of EPRM is not used currently, have still maintained it here
enum custom_keycodes {
  EPRM = SAFE_RANGE
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Default QWERTY layer
 *
 * -------------------------------    -------------------------------
 * |F1 |F2 |F3 |F4 |F5 | F6 |PgUp|    |Home| F7 |F8 |F9 |F10|F11|F12|
 * |---+---+---+---+---+----+----|    |----+----+---+---+---+---+---|
 * |Caps           |Med|PrSc|PgDn|    |End |Paus|Num            |Dvo|
 * |---+---+---+---+---+----+----|    |----+----+---+---+---+---+---|    -----------------
 *     | 1 | 2 | 3 | 4 | 5  |Esc |    |Ins | 6  | 7 | 8 | 9 | 0 |        | = | / | * | % |
 *     |---+---+---+---+----+----|    |----+----+---+---+---+---|        |---+---+---+---|
 *     | Q | W | E | R | T  |Tab |    |Del | Y  | U | I | O | P |        | 7 | 8 | 9 | - |
 *     |---+---+---+---+----+----|    |----+----+---+---+---+---|        |---+---+---+---|
 *     | A | S | D | F | G  |Bspc|    |Ent | H  | J | K | L | ; |        | 4 | 5 | 6 | + |
 *     |---+---+---+---+----+----|    |----+----+---+---+---+---|        |---+---+---+---|
 *     | Z | X | C | V | B  |alt |    |App | N  | M | , | . | / |        | 1 | 2 | 3 |Ent|
 *     |---+---+---+---+----+----|    |----+----+---+---+---+---|        |---+---+---+---|
 *     | ` | _ | " | ' |Spc |Shft|    |Shft|Spc | [ |Up | ] | \ |        | 0 | , | . |
 *     |---+---+---+---+----+----|    |----+----+---+---+---+---|        -------------
 *         | = | - | +      |Ctrl|    |Win      |Lft|Dn |Rt |
 *         -----------------------    -----------------------
 *
 */
[BASE] = LAYOUT_k19(
  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_PGUP,        KC_HOME,   KC_F7,    KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,
  KC_CAPS,                TG(MEDIA), KC_PSCR, KC_PGDN,      KC_END,    KC_PAUS,  TG(NUMBER),                 TG(DVORAK),
         KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_ESC,         KC_INS,    KC_6,     KC_7,   KC_8,   KC_9,   KC_0,               KC_EQL,  KC_PSLS, KC_PAST, KC_PERC,
         KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_TAB,         KC_DEL,    KC_Y,     KC_U,   KC_I,   KC_O,   KC_P,               KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
         KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_BSPC,        KC_ENT,    KC_H,     KC_J,   KC_K,   KC_L,   KC_SCLN,            KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
         KC_Z,  KC_X,  KC_C,  KC_V,  KC_B, OSM(MOD_LALT),   KC_APP,    KC_N,     KC_M,   KC_COMM,KC_DOT, KC_SLASH,           KC_P1,   KC_P2,   KC_P3,   KC_ENT,
     KC_GRV,KC_UNDS,KC_DQUO,KC_QUOT,KC_SPC,OSM(MOD_LSFT),   OSM(MOD_RSFT),KC_SPC,KC_LBRC,KC_UP,  KC_RBRC,KC_BSLS,            KC_P0,   KC_COMM, KC_PDOT,
             KC_EQL,KC_MINS,KC_PLUS,       OSM(MOD_LCTL),   OSM(MOD_RGUI),       KC_LEFT,KC_DOWN,KC_RIGHT
),

/* Keymap 1: Number layer
 *
 * -----------------------------      -----------------------------
 * |   |   |   |   |   |   |   |      |   |   |   |   |   |   |   |
 * |---+---+---+---+---+---+---|      |---+---+---+---+---+---+---|
 * |               |   |   |   |      |   |   |               |   |
 * |---+---+---+---+---+---+---|      |---+---+---+---+---+---+---|      -----------------
 *     |   |   |   |   |   |   |      |   |   | = | / | * | , |          |   |   |   |   |
 *     |---+---+---+---+---+---|      |---+---+---+---+---+---|          |---+---+---+---|
 *     |   |   |   |   |   |   |      |   |   | 7 | 8 | 9 | - |          |   |   |   |   |
 *     |---+---+---+---+---+---|      |---+---+---+---+---+---|          |---+---+---+---|
 *     |   |   |   |   |   |   |      |   |   | 4 | 5 | 6 | + |          |   |   |   |   |
 *     |---+---+---+---+---+---|      |---+---+---+---+---+---|          |---+---+---+---|
 *     |   |   |   |   |   |   |      |   |   | 1 | 2 | 3 |Ent|          |   |   |   |   |
 *     |---+---+---+---+---+---|      |---+---+---+---+---+---|          |---+---+---+---|
 *     |   |   |   |   |   |   |      |   |   | 0 |   | . |   |          |   |   |   |
 *     |---+---+---+---+---+---|      |---+---+---+---+---+---|          -------------
 *         |   |   |       |   |      |       |   |   |   |
 *         ---------------------      ---------------------
 *
 */
[NUMBER] = LAYOUT_k19(
  ____, ____, ____, ____, ____, ____, ____,     ____, ____, ____,    ____,    ____,    ____,   ____,
  ____,                   ____, ____, ____,     ____, ____, ____,                              ____,
        ____, ____, ____, ____, ____, ____,     ____, ____, KC_EQL,  KC_PSLS, KC_PAST, KC_COMM,          ____, ____, ____, ____,
        ____, ____, ____, ____, ____, ____,     ____, ____, KC_P7,   KC_P8,   KC_P9,   KC_PMNS,          ____, ____, ____, ____,
        ____, ____, ____, ____, ____, ____,     ____, ____, KC_P4,   KC_P5,   KC_P6,   KC_PPLS,          ____, ____, ____, ____,
        ____, ____, ____, ____, ____, ____,     ____, ____, KC_P1,   KC_P2,   KC_P3,   KC_ENT,           ____, ____, ____, ____,
        ____, ____, ____, ____, ____, ____,     ____, ____, KC_P0,   ____,    KC_PDOT, ____,             ____, ____, ____,
              ____, ____, ____,       ____,     ____,       ____,    ____,    ____
),
/* Keymap 2: Media Layer
 *
 * -----------------------------------      -----------------------------
 * |Mute|VolD|VolU|PrTr|PlPs|NxTr|   |      |   |   |   |   |   |   |   |
 * |----+----+----+----+----+----+---|      |---+---+---+---+---+---+---|
 * |                   |    |    |   |      |   |   |               |   |
 * |----+----+----+----+----+----+---|      |---+---+---+---+---+---+---|      -----------------
 *      |    |    |    |    |    |   |      |   |   |   |   |   |   |          |   |   |   |   |
 *      |----+----+----+----+----+---|      |---+---+---+---+---+---|          |---+---+---+---|
 *      |    |    |    |    |    |   |      |   |   |   |   |   |   |          |   |   |   |   |
 *      |----+----+----+----+----+---|      |---+---+---+---+---+---|          |---+---+---+---|
 *      |    |    |    |    |    |   |      |   |   |   |   |   |   |          |   |   |   |   |
 *      |----+----+----+----+----+---|      |---+---+---+---+---+---|          |---+---+---+---|
 *      |    |    |    |    |    |   |      |   |   |   |   |   |   |          |   |   |   |   |
 *      |----+----+----+----+----+---|      |---+---+---+---+---+---|          |---+---+---+---|
 *      |    |    |    |    |    |   |      |   |   |   |   |   |   |          |   |   |   |
 *      |----+----+----+----+----+---|      |---+---+---+---+---+---|          -------------
 *           |    |    |         |   |      |       |   |   |   |
 *           -------------------------      ---------------------
 */
[MEDIA] = LAYOUT_k19(
  KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT, ____,       ____, ____, ____, ____, ____, ____, ____,
  ____,                               ____,    ____,    ____,       ____, ____, ____,                   ____,
           ____,    ____,    ____,    ____,    ____,    ____,       ____, ____, ____, ____, ____, ____,         ____, ____, ____, ____,
           ____,    ____,    ____,    ____,    ____,    ____,       ____, ____, ____, ____, ____, ____,         ____, ____, ____, ____,
           ____,    ____,    ____,    ____,    ____,    ____,       ____, ____, ____, ____, ____, ____,         ____, ____, ____, ____,
           ____,    ____,    ____,    ____,    ____,    ____,       ____, ____, ____, ____, ____, ____,         ____, ____, ____, ____,
           ____,    ____,    ____,    ____,    ____,    ____,       ____, ____, ____, ____, ____, ____,         ____, ____, ____,
                    ____,    ____,    ____,             ____,       ____,       ____, ____, ____
),
/* Keymap 3: Dvorak Layer
 *
 * -----------------------------      -----------------------------
 * |   |   |   |   |   |   |   |      |   |   |   |   |   |   |   |
 * |---+---+---+---+---+---+---|      |---+---+---+---+---+---+---|
 * |               |   |   |   |      |   |   |               |   |
 * |---+---+---+---+---+---+---|      |---+---+---+---+---+---+---|      -----------------
 *     |   |   |   |   |   |   |      |   |   |   |   |   |   |          |   |   |   |   |
 *     |---+---+---+---+---+---|      |---+---+---+---+---+---|          |---+---+---+---|
 *     | ' | , | . | P | Y |   |      |   | F | G | C | R | L |          |   |   |   |   |
 *     |---+---+---+---+---+---|      |---+---+---+---+---+---|          |---+---+---+---|
 *     | A | O | E | U | I |   |      |   | D | H | T | N | S |          |   |   |   |   |
 *     |---+---+---+---+---+---|      |---+---+---+---+---+---|          |---+---+---+---|
 *     | ; | Q | J | K | X |   |      |   | B | M | W | V | Z |          |   |   |   |   |
 *     |---+---+---+---+---+---|      |---+---+---+---+---+---|          |---+---+---+---|
 *     |   |   |   | / |   |   |      |   |   |   |   |   |   |          |   |   |   |
 *     |---+---+---+---+---+---|      |---+---+---+---+---+---|          -------------
 *         |   |           |   |      |       |   |   |   |
 *         ---------------------      ---------------------
 */
[DVORAK] = LAYOUT_k19(
  ____, ____,   ____,   ____,   ____, ____, ____,       ____, ____, ____, ____, ____, ____, ____,
  ____,                         ____, ____, ____,       ____, ____, ____,                   ____,
        ____,   ____,   ____,   ____, ____, ____,       ____, ____, ____, ____, ____, ____,         ____, ____, ____, ____,
        KC_QUOT,KC_COMM,KC_DOT, KC_P, KC_Y, ____,       ____, KC_F, KC_G, KC_C, KC_R, KC_L,         ____, ____, ____, ____,
        KC_A,   KC_O,   KC_E,   KC_U, KC_I, ____,       ____, KC_D, KC_H, KC_T, KC_N, KC_S,         ____, ____, ____, ____,
        KC_SCLN,KC_Q,   KC_J,   KC_K, KC_X, ____,       ____, KC_B, KC_M, KC_W, KC_V, KC_Z,         ____, ____, ____, ____,
        ____,   ____,   ____,KC_SLSH, ____, ____,       ____, ____, ____, ____, ____, ____,         ____, ____, ____,
                ____,   ____,   ____,       ____,       ____,       ____, ____, ____
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
  k19_dvorak_led_off();

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

  // check if dvorak layer is enabled
  if (state & 8) {
    k19_dvorak_led_on();
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

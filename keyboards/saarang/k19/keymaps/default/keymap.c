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
#define SPCH    2   // Special Characters Layer
#define MEDIA   3   // Multi Media Layer
*/
enum layers {
  BASE,
  NUMBER,
  SPCH,
  MEDIA
};

// Though the custom keycode of EPRM is not used currently, have still maintained it here
enum custom_keycodes {
  EPRM = SAFE_RANGE
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Default QWERTY layer
 *
 * --------------------------------------------------      --------------------------------------------------
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  | PgUp |      | Home |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Caps                      |Media |PrScr | PgDn |      | End  |Pause | Num                | Menu | Win  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 *        |  1   |  2   |  3   |  4   |  5   | Esc  |      | Del  |  6   |  7   |  8   |  9   |  0   |
 *        |------+------+------+------+------+------|      |------+------+------+------+------+------|
 *        |  Q   |  W   |  E   |  R   |  T   | Tab  |      | SpCh |  Y   |  U   |  I   |  O   |  P   |
 *        |------+------+------+------+------+------|      |------+------+------+------+------+------|
 *        |  A   |  S   |  D   |  F   |  G   | Bspc |      | Ent  |  H   |  J   |  K   |  L   |  ;   |
 *        |------+------+------+------+------+------|      |------+------+------+------+------+------|
 *        |  Z   |  X   |  C   |  V   |  B   | Alt  |      | Ins  |  N   |  M   |  ,   |  .   |  /   |
 *        |------+------+------+------+------+------|      |------+------+------+------+------+------|
 *               |  '          |  -   |Space | Ctrl |      | Shft |Space               |  Up  |
 *               |------+------+------+------+------|      |------+------+------+------+------+------|
 *                                                                               |Left | Down | Right|
 *                                                                               |-----+------+------|
 *
 */
[BASE] = LAYOUT_k19(
  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_PGUP,        KC_HOME,    KC_F7,    KC_F8, KC_F9,   KC_F10, KC_F11, KC_F12,
  KC_CAPS,                TG(MEDIA), KC_PSCR, KC_PGDN,      KC_END,     KC_PAUS,  TG(NUMBER),             KC_APP, KC_RWIN,
         KC_1,  KC_2,  KC_3,  KC_4,  KC_5,  KC_ESC,         KC_DEL,     KC_6,     KC_7,  KC_8,    KC_9,   KC_0,
         KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,  KC_TAB,         OSL(SPCH),  KC_Y,     KC_U,  KC_I,    KC_O,   KC_P,
         KC_A,  KC_S,  KC_D,  KC_F,  KC_G,  KC_BSPC,        KC_ENT,     KC_H,     KC_J,  KC_K,    KC_L,   KC_SCLN,
         KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  OSM(MOD_LALT),  KC_INS,     KC_N,     KC_M,  KC_COMM, KC_DOT, KC_SLASH,
                KC_QUOT,     KC_MINS,KC_SPC,OSM(MOD_LCTL),  OSM(MOD_RSFT),KC_SPC,                 KC_UP,
                                                                                        KC_LEFT,  KC_DOWN,KC_RIGHT
),

/* Keymap 1: Number layer
 *
 * --------------------------------------------------      --------------------------------------------------
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |                           |      |      |      |      |      |      |                    |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 *        |      |      |      |      |      |      |      |      |  -   |      |Slash |Asterisk| -  |
 *        |------+------+------+------+------+------|      |------+------+------+------+------+------|
 *        |      |      |      |      |      |      |      |      |  +   |  7   |  8   |  9   |  +   |
 *        |------+------+------+------+------+------|      |------+------+------+------+------+------|
 *        |      |      |      |      |      |      |      |      |  0   |  4   |  5   |  6   |  0   |
 *        |------+------+------+------+------+------|      |------+------+------+------+------+------|
 *        |      |      |      |      |      |      |      |      |  .   |  1   |  2   |  3   |  .   |
 *        |------+------+------+------+------+------|      |------+------+------+------+------+------|
 *               |             |      |      |      |      |      |                    |      |
 *               |------+------+------+------+------|      |------+------+------+------+------+------|
 *                                                                              |      |      |      |
 *                                                                              |------+------+------|
 *
 */
[NUMBER] = LAYOUT_k19(
  ____,  ____,  ____,  ____,  ____,  ____,  ____,           ____,  ____,  ____,  ____,    ____,    ____,   ____,
  ____,                       ____,  ____,  ____,           ____,  ____,  ____,                    ____,   ____,
         ____,  ____,  ____,  ____,  ____,  ____,           ____,  KC_PMNS,  ____,  KC_PSLS, KC_PAST, KC_PMNS,
         ____,  ____,  ____,  ____,  ____,  ____,           ____,  KC_PPLS,  KC_P7, KC_P8,   KC_P9,   KC_PPLS,
         ____,  ____,  ____,  ____,  ____,  ____,           ____,  KC_P0,    KC_P4, KC_P5,   KC_P6,   KC_P0,
         ____,  ____,  ____,  ____,  ____,  ____,           ____,  KC_PDOT,  KC_P1, KC_P2,   KC_P3,   KC_PDOT,
                ____,         ____,  ____,  ____,           ____,  ____,                  ____,
                                                                                 ____,    ____,    ____
),
/* Keymap 2: Special Characters Layer
 *
 * --------------------------------------------------      --------------------------------------------------
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |                           |      |      |      |      |      |      |                    |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 *        |      |      |      |      |      |      |      |      |      |      |      |      |      |
 *        |------+------+------+------+------+------|      |------+------+------+------+------+------|
 *        |  ~   |  |   |  {   |  }   |      |      |      |      |      |      |      |      |      |
 *        |------+------+------+------+------+------|      |------+------+------+------+------+------|
 *        |  `   |  \   |  [   |  ]   |      |      |      |      |      |      |      |      |      |
 *        |------+------+------+------+------+------|      |------+------+------+------+------+------|
 *        |      |      |  =   |  +   |      |      |      |      |      |      |      |      |      |
 *        |------+------+------+------+------+------|      |------+------+------+------+------+------|
 *               |             |      |      |      |      |      |                    |      |
 *               |------+------+------+------+------|      |------+------+------+------+------+------|
 *                                                                              |      |      |      |
 *                                                                              |------+------+------|
 */
[SPCH] = LAYOUT_k19(
  ____,  ____,  ____,  ____,  ____,  ____,  ____,          ____,  ____,  ____,  ____,  ____,  ____,  ____,
  ____,                       ____,  ____,  ____,          ____,  ____,  ____,                ____,  ____,
         ____,  ____,  ____,  ____,  ____,  ____,          ____,  ____,  ____,  ____,  ____,  ____,
         KC_TILD,KC_PIPE, KC_LCBR, KC_RCBR, ____, ____,    ____,  ____,  ____,  ____,  ____,  ____,
         KC_GRV, KC_BSLS, KC_LBRC, KC_RBRC, ____, ____,    ____,  ____,  ____,  ____,  ____,  ____,
         ____,  ____,     KC_EQL,  KC_PLUS, ____, ____,    ____,  ____,  ____,  ____,  ____,  ____,
         ____,                        ____, ____, ____,    ____,  ____,                ____,
                                                                                ____,  ____,  ____
),
/* Keymap 3: Media Layer
 *
 * --------------------------------------------------      --------------------------------------------------
 * |Mute |VolDn |VolUp |PrevTr|PlayPause|NextTr|    |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |                           |      |      |      |      |      |      |                    |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 *        |      |      |      |      |      |      |      |      |      |      |      |      |      |
 *        |------+------+------+------+------+------|      |------+------+------+------+------+------|
 *        |      |      |      |      |      |      |      |      |      |      |      |      |      |
 *        |------+------+------+------+------+------|      |------+------+------+------+------+------|
 *        |      |      |      |      |      |      |      |      |      |      |      |      |      |
 *        |------+------+------+------+------+------|      |------+------+------+------+------+------|
 *        |      |      |      |      |      |      |      |      |      |      |      |      |      |
 *        |------+------+------+------+------+------|      |------+------+------+------+------+------|
 *               |             |      |      |      |      |      |                    |      |
 *               |------+------+------+------+------|      |------+------+------+------+------+------|
 *                                                                              |      |      |      |
 *                                                                              |------+------+------|
 */
[MEDIA] = LAYOUT_k19(
  KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT,  ____,      ____,  ____,  ____,  ____,  ____,  ____,  ____,
  ____,                       ____,  ____,  ____,                   ____,  ____,  ____,                ____,  ____,
         ____,  ____,  ____,  ____,  ____,  ____,                   ____,  ____,  ____,  ____,  ____,  ____,
         ____,  ____,  ____,  ____,  ____,  ____,                   ____,  ____,  ____,  ____,  ____,  ____,
         ____,  ____,  ____,  ____,  ____,  ____,                   ____,  ____,  ____,  ____,  ____,  ____,
         ____,  ____,  ____,  ____,  ____,  ____,                   ____,  ____,  ____,  ____,  ____,  ____,
                ____,         ____,  ____,  ____,                   ____,  ____,                ____,
                                                                                         ____,  ____,  ____
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

  // Trying to get this to work using oneshot_layer_changed_user() method
  //k19_spch_led_off();

  k19_media_led_off();
  k19_num_led_off();

  // Check if BASE layer is enabled
  if (state & 1) {
    // do nothing as we are checking for the BASE layer, i.e. QWERTY layer, no LEDs to be turned on
  }

  // check if number layer is enabled
  if (state & 2) {
    k19_num_led_on();
  }

  /* Trying to get this to work using oneshot_layer_changed_user() method
  // check if special characters layer is enabled
  if (state & 4) {
    k19_spch_led_on();
  }
  */

  // check if media layer is enabled
  if (state & 8) {
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
  if (layer == SPCH) {
    k19_spch_led_on();
  }
  if (!layer) {
    k19_spch_led_off();
  }
}

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

enum unicode_name {
  DECIMAL_POINT,
  ZERO,
  ONE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  POUND,
  RUPEE,
  EURO,
  CURL_BRAC_S,
  CURL_BRAC_E,
  DOUBLE_QUOTE,
  PIPE,
  TILDE,
  SQ_BRAC_S,
  SQ_BRAC_E,
  SINGLE_QUOTE,
  BACK_SLASH,
  BACK_TICK,
  EQUAL,
  MINUS,
  PLUS,
  UNDERSCORE
};

const uint32_t PROGMEM unicode_map[] = {
  [DECIMAL_POINT] = 0x2E,
  [ZERO] =          0x30,
  [ONE] =           0x31,
  [TWO] =           0x32,
  [THREE] =         0x33,
  [FOUR] =          0x34,
  [FIVE] =          0x35,
  [SIX] =           0x36,
  [SEVEN] =         0x37,
  [EIGHT] =         0x38,
  [NINE] =          0x39,
  [POUND] =         0xA3,
  [RUPEE] =         0x20B9,
  [EURO] =          0x20AC,
  [CURL_BRAC_S] =   0x7B,
  [CURL_BRAC_E] =   0x7D,
  [DOUBLE_QUOTE] =  0x22,
  [PIPE] =          0x7C,
  [TILDE] =         0x7E,
  [SQ_BRAC_S] =     0x5B,
  [SQ_BRAC_E] =     0x5D,
  [SINGLE_QUOTE] =  0x27,
  [BACK_SLASH] =    0x5C,
  [BACK_TICK] =     0x60,
  [EQUAL] =         0x3D,
  [MINUS] =         0x2D,
  [PLUS] =          0x2B,
  [UNDERSCORE] =    0x5F
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Default QWERTY layer
 *
 * --------------------------------------------------      --------------------------------------------------
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  | PgUp |      | Home |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Caps                      | PScr | Paus | PgDn |      | End  |Media | Num                       | Menu |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * | Shft        |  2   |  3   |  4   |  5   | Esc  |      | Ins  |  6   |  7   |  8   |  9          | Win  |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |         1   |  W   |  E   |  R   |  T   | Tab  |      | Del  |  Y   |  U   |  I   |  O   |  0          |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |         Q   |  S   |  D   |  F   |  G   | Bspc |      | Ent  |  H   |  J   |  K   |  L   |  P          |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |         A   |  X   |  C   |  V   |  B   | Alt  |      | SpCh |  N   |  M   |  ,   |  .   |  ;          |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |         Z   |                  Space    | Ctrl |      | Shft |    Space           |  Up  |  /          |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 *                                                         |                     Right | Down | Left        |
 *                                                         |------+------+------+------+------+------+------|
 *
 */
[BASE] = LAYOUT_k19(
  KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_PGUP,        KC_HOME,    KC_F7,    KC_F8, KC_F9,   KC_F10, KC_F11, KC_F12,
  KC_CAPS,                KC_PSCR, KC_PAUS, KC_PGDN,        KC_END,     TG(MEDIA),TG(NUMBER),                     KC_APP,
  OSM(MOD_LSFT),KC_2,  KC_3,  KC_4,  KC_5,  KC_ESC,         KC_INS,     KC_6,     KC_7,  KC_8,    KC_9,           KC_RWIN,
         KC_1,  KC_W,  KC_E,  KC_R,  KC_T,  KC_TAB,         KC_DEL,     KC_Y,     KC_U,  KC_I,    KC_O,   KC_0,
         KC_Q,  KC_S,  KC_D,  KC_F,  KC_G,  KC_BSPC,        KC_ENT,     KC_H,     KC_J,  KC_K,    KC_L,   KC_P,
         KC_A,  KC_X,  KC_C,  KC_V,  KC_B,  OSM(MOD_LALT),  OSL(SPCH),  KC_N,     KC_M,  KC_COMM, KC_DOT, KC_SCLN,
         KC_Z,                KC_SPC,       OSM(MOD_LCTL),  OSM(MOD_RSFT), KC_SPC,                KC_UP,  KC_SLASH,
                                                                                        KC_RIGHT, KC_DOWN,KC_LEFT
),

/* Keymap 1: Number layer
 *
 * --------------------------------------------------      --------------------------------------------------
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |                           |      |      |      |      |      |      |                           |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |             |      |      |      |      |      |      |      |      |      |Slash |Asterisk     |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |             |      |      |      |      |      |      |      |      |  7   |  8   |  9   |  -          |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |             |      |      |      |      |      |      |      |      |  4   |  5   |  6   |  +          |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |             |      |      |      |      |      |      |      |      |  1   |  2   |  3   |  0          |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |             |                           |      |      |      |                    |      |  .          |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 *                                                         |                           |      |             |
 *                                                         |------+------+------+------+------+------+------|
 *
 */
[NUMBER] = LAYOUT_k19(
  ____,  ____,  ____,  ____,  ____,  ____,  ____,           ____,  ____,  ____,     ____,     ____,     ____,   ____,
  ____,                       ____,  ____,  ____,           ____,  ____,  ____,                                 ____,
  ____,         ____,  ____,  ____,  ____,  ____,           ____,  ____,  ____,     KC_PSLS,  KC_PAST,          ____,
         ____,  ____,  ____,  ____,  ____,  ____,           ____,  ____,  X(SEVEN), X(EIGHT), X(NINE), KC_PMNS,
         ____,  ____,  ____,  ____,  ____,  ____,           ____,  ____,  X(FOUR), X(FIVE), X(SIX), KC_PPLS,
         ____,  ____,  ____,  ____,  ____,  ____,           ____,  ____,  X(ONE), X(TWO), X(THREE), X(ZERO),
         ____,                ____,         ____,           ____,  ____,                      ____,     X(DECIMAL_POINT),
                                                                                    ____,     ____,     ____
),
/* Keymap 2: Special Characters Layer
 *
 * --------------------------------------------------      --------------------------------------------------
 * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |                           |      |      |      |      |      |      |                           |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |             |      |Pound |Rupee | Euro |      |      |      |      |      |      |             |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |             |  {   |  }   |  "   |  |   |      |      |      |      |      |      |      |             |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |         ~   |  [   |  ]   |  '   |  \   |      |      |      |      |      |      |      |             |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |         `   |  =   |  -   |  +   |      |      |      |      |      |      |      |      |             |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |         _   |                           |      |      |      |                    |      |             |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 *                                                         |                           |      |             |
 *                                                         |------+------+------+------+------+------+------|
 */
[SPCH] = LAYOUT_k19(
  ____,  ____,  ____,  ____,  ____,  ____,  ____,                                       ____,  ____,  ____,  ____,  ____,  ____,  ____,
  ____,                       ____,  ____,  ____,                                       ____,  ____,  ____,                       ____,
  ____,         ____,         X(POUND),       X(RUPEE),         X(EURO),       ____,    ____,  ____,  ____,  ____,  ____,         ____,
         ____, X(CURL_BRAC_S), X(CURL_BRAC_E), X(DOUBLE_QUOTE), X(PIPE),       ____,    ____,  ____,  ____,  ____,  ____,  ____,
     X(TILDE), X(SQ_BRAC_S),  X(SQ_BRAC_E),   X(SINGLE_QUOTE),  X(BACK_SLASH), ____,    ____,  ____,  ____,  ____,  ____,  ____,
     X(BACK_TICK), X(EQUAL),  X(MINUS),       X(PLUS),          ____,          ____,    ____,  ____,  ____,  ____,  ____,  ____,
     X(UNDERSCORE),                           ____,                            ____,    ____,  ____,                ____,  ____,
                                                                                                             ____,  ____,  ____
),
/* Keymap 3: Media Layer
 *
 * --------------------------------------------------      --------------------------------------------------
 * | Mute |VolDn |VolUp |PrevTr|PlayPause|NextTr|   |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |                           |      |      |      |      |      |      |                           |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |             |      |      |      |      |      |      |      |      |      |      |             |      |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |             |      |      |      |      |      |      |      |      |      |      |      |             |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |             |      |      |      |      |      |      |      |      |      |      |      |             |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |             |      |      |      |      |      |      |      |      |      |      |      |             |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 * |             |                           |      |      |      |                    |      |             |
 * |------+------+------+------+------+------+------|      |------+------+------+------+------+------+------|
 *                                                         |                           |      |             |
 *                                                         |------+------+------+------+------+------+------|
*/
[MEDIA] = LAYOUT_k19(
  KC_MUTE, KC_VOLD, KC_VOLU, KC_MPRV, KC_MPLY, KC_MNXT,  ____,      ____,  ____,  ____,  ____,  ____,  ____,  ____,
  ____,                       ____,  ____,  ____,                   ____,  ____,  ____,                       ____,
  ____,         ____,  ____,  ____,  ____,  ____,                   ____,  ____,  ____,  ____,  ____,         ____,
         ____,  ____,  ____,  ____,  ____,  ____,                   ____,  ____,  ____,  ____,  ____,  ____,
         ____,  ____,  ____,  ____,  ____,  ____,                   ____,  ____,  ____,  ____,  ____,  ____,
         ____,  ____,  ____,  ____,  ____,  ____,                   ____,  ____,  ____,  ____,  ____,  ____,
         ____,                ____,         ____,                   ____,  ____,                ____,  ____,
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

void eeconfig_init_user(void) {
  set_unicode_input_mode(UC_WINC);
}

void oneshot_layer_changed_user(uint8_t layer) {
  if (layer == SPCH) {
    k19_spch_led_on();
  }
  if (!layer) {
    k19_spch_led_off();
  }
}

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
#include "action_util.h"

bool i2c_initialized = 0;
i2c_status_t mcp23018_status = 0x20;
i2c_status_t mcp23018_status_number_keypad = 0x20;

void matrix_init_kb(void) {


    // We do not plan to use PWM so commenting out PWM related part
    /*
    // keyboard LEDs (see "PWM on ports OC1(A|B|C)" in "teensy-2-0.md")
    TCCR1A = 0b10101001;  // set and configure fast PWM
    TCCR1B = 0b00001001;  // set and configure fast PWM
    */

    // unused pins - B4, D4, E6
    // set as input with internal pull-up enabled
    /* Use new GPIO APIs instead of this code
    DDRB  &= ~(1<<4);
    DDRD  &= ~(1<<4);
    DDRE  &= ~(1<<6);
    PORTB |=  (1<<4);
    PORTD |=  (1<<4);
    PORTE |=  (1<<6);
    */
    setPinInputHigh(B4);
    setPinInputHigh(D4);
    setPinInputHigh(E6);

    // set GPIO pins as Output for LEDs
    setPinOutput(B7);   // Ctrl LED
    setPinOutput(D6);   // Alt LED
    setPinOutput(D7);   // Shift LED
    setPinOutput(B5);   // SpCh LED
    setPinOutput(B6);   // Media LED
    setPinOutput(C6);   // Num LED
    setPinOutput(C7);   // Caps Lock LED

    k19_blink_all_leds();

    matrix_init_user();
}

void k19_blink_all_leds(void)
{
    k19_all_led_off();
    //k19_all_led_set(LED_BRIGHTNESS_DEFAULT);
    k19_ctrl_led_on();
    _delay_ms(50);
    k19_alt_led_on();
    _delay_ms(50);
    k19_shift_led_on();
    _delay_ms(50);
    k19_spch_led_on();
    _delay_ms(50);
    k19_media_led_on();
    _delay_ms(50);
    k19_num_led_on();
    _delay_ms(50);
    k19_caps_led_on();
    _delay_ms(50);

    k19_ctrl_led_off();
    _delay_ms(50);
    k19_alt_led_off();
    _delay_ms(50);
    k19_shift_led_off();
    _delay_ms(50);
    k19_spch_led_off();
    _delay_ms(50);
    k19_media_led_off();
    _delay_ms(50);
    k19_num_led_off();
    _delay_ms(50);
    k19_caps_led_off();
    _delay_ms(50);
}

uint8_t init_mcp23018(void) {
    mcp23018_status = 0x20;

    // I2C subsystem

    // uint8_t sreg_prev;
    // sreg_prev=SREG;
    // cli();

    if (i2c_initialized == 0) {
        i2c_init();  // on pins D(1,0)
        i2c_initialized = true;
        _delay_ms(1000);
    }

#if (DIODE_DIRECTION == COL2ROW)

    // i2c_init(); // on pins D(1,0)
    // _delay_ms(1000);

    // Initialization of MCP23018 on Right Keypad

    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, K19_I2C_TIMEOUT);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(IODIRA, K19_I2C_TIMEOUT);            if (mcp23018_status) goto out;
    // 7 rows set for output in IODIRA
    mcp23018_status = i2c_write(0b00000000, K19_I2C_TIMEOUT);        if (mcp23018_status) goto out;
    // 6 columns set for input in IODIRB.
    // Address is automatically incremented to IODIRB.
    mcp23018_status = i2c_write(0b00111111, K19_I2C_TIMEOUT);        if (mcp23018_status) goto out;
    i2c_stop();

    // set pull-up
    // - unused  : on  : 1
    // - input   : on  : 1
    // - driving : off : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, K19_I2C_TIMEOUT);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(GPPUA, K19_I2C_TIMEOUT);             if (mcp23018_status) goto out;
    // disable pull-up for rows in Port A
    mcp23018_status = i2c_write(0b00000000, K19_I2C_TIMEOUT);        if (mcp23018_status) goto out;
    // enable pull-up for columns in Port B
    // Address is automatically incremented to GPPUB.
    mcp23018_status = i2c_write(0b00111111, K19_I2C_TIMEOUT);        if (mcp23018_status) goto out;
    i2c_stop();


#elif (DIODE_DIRECTION == ROW2COL)

    // Initialization of MCP23018 on Right Keypad

    // set pin direction
    // - unused  : input  : 1
    // - input   : input  : 1
    // - driving : output : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, K19_I2C_TIMEOUT);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(IODIRA, K19_I2C_TIMEOUT);            if (mcp23018_status) goto out;
    // 7 rows set for input in IODIRA
    mcp23018_status = i2c_write(0b01111111, K19_I2C_TIMEOUT);        if (mcp23018_status) goto out;
    // 6 columns set for output in IODIRB.
    // Address is automatically incremented to IODIRB.
    mcp23018_status = i2c_write(0b00000000, K19_I2C_TIMEOUT);        if (mcp23018_status) goto out;
    i2c_stop();

    // set pull-up
    // - unused  : on  : 1
    // - input   : on  : 1
    // - driving : off : 0
    mcp23018_status = i2c_start(I2C_ADDR_WRITE, K19_I2C_TIMEOUT);    if (mcp23018_status) goto out;
    mcp23018_status = i2c_write(GPPUA, K19_I2C_TIMEOUT);             if (mcp23018_status) goto out;
    // enable pull-up for rows in Port A
    mcp23018_status = i2c_write(0b01111111, K19_I2C_TIMEOUT);        if (mcp23018_status) goto out;
    // disable pull-up for columns in Port B
    // Address is automatically incremented to GPPUB.
    mcp23018_status = i2c_write(0b00000000, K19_I2C_TIMEOUT);        if (mcp23018_status) goto out;
    i2c_stop();

#endif

out:
    i2c_stop();
    // SREG=sreg_prev;

    return mcp23018_status;
}

uint8_t init_mcp23018_number_keypad(void) {
    mcp23018_status_number_keypad = 0x20;

    // I2C subsystem

    // uint8_t sreg_prev;
    // sreg_prev=SREG;
    // cli();

    if (i2c_initialized == 0) {
        i2c_init();  // on pins D(1,0)
        i2c_initialized = true;
        _delay_ms(1000);
    }

#if (DIODE_DIRECTION == COL2ROW)

    // Initialization of MCP23018 on Number Keypad

    mcp23018_status_number_keypad = i2c_start(I2C_ADDR_NUMBER_KEYPAD_WRITE, K19_I2C_TIMEOUT);
    if (mcp23018_status_number_keypad) goto out;
    mcp23018_status_number_keypad = i2c_write(IODIRA, K19_I2C_TIMEOUT);
    if (mcp23018_status_number_keypad) goto out;
    // 5 rows set for output in IODIRA
    mcp23018_status_number_keypad = i2c_write(0b00000000, K19_I2C_TIMEOUT);
    if (mcp23018_status_number_keypad) goto out;
    // 4 columns set for input in IODIRB.
    // Address is automatically incremented to IODIRB.
    mcp23018_status_number_keypad = i2c_write(0b00001111, K19_I2C_TIMEOUT);
    if (mcp23018_status_number_keypad) goto out;
    i2c_stop();


    mcp23018_status_number_keypad = i2c_start(I2C_ADDR_NUMBER_KEYPAD_WRITE, K19_I2C_TIMEOUT);
    if (mcp23018_status_number_keypad) goto out;
    mcp23018_status_number_keypad = i2c_write(GPPUA, K19_I2C_TIMEOUT);
    if (mcp23018_status_number_keypad) goto out;
    // disable pull-up for rows in Port A
    mcp23018_status_number_keypad = i2c_write(0b00000000, K19_I2C_TIMEOUT);
    if (mcp23018_status_number_keypad) goto out;
    // enable pull-up for columns in Port B
    // Address is automatically incremented to GPPUB.
    mcp23018_status_number_keypad = i2c_write(0b00001111, K19_I2C_TIMEOUT);
    if (mcp23018_status_number_keypad) goto out;


#elif (DIODE_DIRECTION == ROW2COL)

    // Initialization of MCP23018 on Number Keypad

    mcp23018_status_number_keypad = i2c_start(I2C_ADDR_WRITE, K19_I2C_TIMEOUT);
    if (mcp23018_status_number_keypad) goto out;
    mcp23018_status_number_keypad = i2c_write(IODIRA, K19_I2C_TIMEOUT);
    if (mcp23018_status_number_keypad) goto out;
    // 5 rows set for input in IODIRA
    mcp23018_status_number_keypad = i2c_write(0b00011111, K19_I2C_TIMEOUT);
    if (mcp23018_status_number_keypad) goto out;
    // 4 columns set for output in IODIRB.
    // Address is automatically incremented to IODIRB.
    mcp23018_status_number_keypad = i2c_write(0b00000000, K19_I2C_TIMEOUT);
    if (mcp23018_status_number_keypad) goto out;
    i2c_stop();

    mcp23018_status_number_keypad = i2c_start(I2C_ADDR_WRITE, K19_I2C_TIMEOUT);
    if (mcp23018_status_number_keypad) goto out;
    mcp23018_status_number_keypad = i2c_write(GPPUA, K19_I2C_TIMEOUT);
    if (mcp23018_status_number_keypad) goto out;
    // enable pull-up for rows in Port A
    mcp23018_status_number_keypad = i2c_write(0b00011111, K19_I2C_TIMEOUT);
    if (mcp23018_status_number_keypad) goto out;
    // disable pull-up for columns in Port B
    // Address is automatically incremented to GPPUB.
    mcp23018_status_number_keypad = i2c_write(0b00000000, K19_I2C_TIMEOUT);
    if (mcp23018_status_number_keypad) goto out;

#endif

out:
    i2c_stop();
    // SREG=sreg_prev;

    return mcp23018_status_number_keypad;
}

void led_set_kb(uint8_t usb_led) {
	// put your keyboard LED indicator (ex: Caps Lock LED) toggling code here
  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
		k19_caps_led_on();
	} else {
		k19_caps_led_off();
  }

	led_set_user(usb_led);
}

void oneshot_mods_changed_kb(uint8_t mods) {
  uint8_t locked_mods = get_oneshot_locked_mods();
  if ((mods & MOD_MASK_SHIFT) || (locked_mods & MOD_MASK_SHIFT)) {
    k19_shift_led_on();
  }
  else
  {
    k19_shift_led_off();
  }

  if ((mods & MOD_MASK_CTRL) || (locked_mods & MOD_MASK_CTRL)) {
    k19_ctrl_led_on();
  }
  else
  {
    k19_ctrl_led_off();
  }

  if ((mods & MOD_MASK_ALT) || (locked_mods & MOD_MASK_ALT)) {
    k19_alt_led_on();
  }
  else
  {
    k19_alt_led_off();
  }

  if (!mods && !locked_mods) {
    k19_ctrl_led_off();
    k19_alt_led_off();
    k19_shift_led_off();
  }
  oneshot_mods_changed_user(mods);
}

void oneshot_locked_mods_changed_kb(uint8_t mods) {
  uint8_t os_mods = get_oneshot_mods();
  if ((mods & MOD_MASK_SHIFT) || (os_mods & MOD_MASK_SHIFT)) {
    k19_shift_led_on();
  }
  else
  {
    k19_shift_led_off();
  }

  if ((mods & MOD_MASK_CTRL) || (os_mods & MOD_MASK_CTRL)) {
    k19_ctrl_led_on();
  }
  else
  {
    k19_ctrl_led_off();
  }

  if ((mods & MOD_MASK_ALT) || (os_mods & MOD_MASK_ALT)) {
    k19_alt_led_on();
  }
  else
  {
    k19_alt_led_off();
  }

  if (!mods && !os_mods) {
    k19_ctrl_led_off();
    k19_alt_led_off();
    k19_shift_led_off();
  }
  oneshot_locked_mods_changed_user(mods);
}

void oneshot_layer_changed_kb(uint8_t layer) {
  oneshot_layer_changed_user(layer);
}

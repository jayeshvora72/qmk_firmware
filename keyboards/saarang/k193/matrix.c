/*
Copyright 2019 Jayesh Vora

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"

#include "config.h"
#include QMK_KEYBOARD_H


#if (MATRIX_COLS <= 8)
#  define print_matrix_header() print("\nr/c 01234567\n")
#  define print_matrix_row(row) print_bin_reverse8(matrix_get_row(row))
#  define matrix_bitpop(i) bitpop(matrix[i])
#  define ROW_SHIFTER ((uint8_t)1)
#elif (MATRIX_COLS <= 16)
#    define print_matrix_header()  print("\nr/c 0123456789ABCDEF\n")
#    define print_matrix_row(row)  print_bin_reverse16(matrix_get_row(row))
#    define matrix_bitpop(i)       bitpop16(matrix[i])
#    define ROW_SHIFTER ((uint16_t)1)
#elif (MATRIX_COLS <= 32)
#    define print_matrix_header()  print("\nr/c 0123456789ABCDEF0123456789ABCDEF\n")
#    define print_matrix_row(row)  print_bin_reverse32(matrix_get_row(row))
#    define matrix_bitpop(i)       bitpop32(matrix[i])
#    define ROW_SHIFTER  ((uint32_t)1)
#endif

// Matrix mask lets you disable switches in the returned matrix data. For example, if you have a
// switch blocker installed and the switch is always pressed.
#ifdef MATRIX_MASKED
    extern const matrix_row_t matrix_mask[];
#endif

#if (DIODE_DIRECTION == ROW2COL) || (DIODE_DIRECTION == COL2ROW)
static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS_LEFT_KEYPAD] = MATRIX_COL_PINS;
#endif

/* matrix state(1:on, 0:off) */
static matrix_row_t raw_matrix[MATRIX_ROWS];

static matrix_row_t matrix[MATRIX_ROWS];

#if (DIODE_DIRECTION == COL2ROW)
    static void init_cols(void);
    static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row);
    static void unselect_rows(void);
    static void select_row(uint8_t row);
    static void unselect_row(uint8_t row);
    static void select_row_on_mcp23018(uint8_t row);
    static void select_row_on_mcp23018_number_keypad(uint8_t row);
    static uint8_t read_cols_on_mcp23018(void);
    static uint8_t read_cols_on_mcp23018_number_keypad(void);
#elif (DIODE_DIRECTION == ROW2COL)
    static void init_rows(void);
    static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col);
    static void unselect_cols(void);
    static void unselect_col(uint8_t col);
    static void select_col(uint8_t col);
    static void select_col_on_mcp23018(uint8_t col);
    static uint8_t read_rows_on_mcp23018(void);
#endif

static uint8_t mcp23018_reset_loop;
static uint8_t mcp23018_number_keypad_reset_loop;

__attribute__ ((weak))
void matrix_init_quantum(void) {
    matrix_init_kb();
}

__attribute__ ((weak))
void matrix_scan_quantum(void) {
    matrix_scan_kb();
}

__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

inline
uint8_t matrix_rows(void) {
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void) {
    return MATRIX_COLS;
}

// void matrix_power_up(void) {
// #if (DIODE_DIRECTION == COL2ROW)
//     for (int8_t r = MATRIX_ROWS - 1; r >= 0; --r) {
//         /* DDRxn */
//         _SFR_IO8((row_pins[r] >> 4) + 1) |= _BV(row_pins[r] & 0xF);
//         toggle_row(r);
//     }
//     for (int8_t c = MATRIX_COLS - 1; c >= 0; --c) {
//         /* PORTxn */
//         _SFR_IO8((col_pins[c] >> 4) + 2) |= _BV(col_pins[c] & 0xF);
//     }
// #elif (DIODE_DIRECTION == ROW2COL)
//     for (int8_t c = MATRIX_COLS - 1; c >= 0; --c) {
//         /* DDRxn */
//         _SFR_IO8((col_pins[c] >> 4) + 1) |= _BV(col_pins[c] & 0xF);
//         toggle_col(c);
//     }
//     for (int8_t r = MATRIX_ROWS - 1; r >= 0; --r) {
//         /* PORTxn */
//         _SFR_IO8((row_pins[r] >> 4) + 2) |= _BV(row_pins[r] & 0xF);
//     }
// #endif
// }

void matrix_init(void) {

  mcp23018_status = init_mcp23018();
  mcp23018_status_number_keypad = init_mcp23018_number_keypad();

    // initialize row and col
#if (DIODE_DIRECTION == COL2ROW)
    unselect_rows();
    init_cols();
#elif (DIODE_DIRECTION == ROW2COL)
    unselect_cols();
    init_rows();
#endif

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i] = 0;
    }
    debounce_init(MATRIX_ROWS);

    matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
  if (mcp23018_status) { // if there was an error
    if (++mcp23018_reset_loop == 0) {
    // if (++mcp23018_reset_loop >= 1300) {
        // since mcp23018_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans
        // this will be approx bit more frequent than once per second
      print("trying to reset mcp23018 in Right Keypad\n");
      mcp23018_status = init_mcp23018();
      if (mcp23018_status) {
          print("Right keypad not responding\n");
      } else {
          print("Right keypad attached\n");
          k19_blink_all_leds();
      }
    }
  }

  if (mcp23018_status_number_keypad) { // if there was an error
    if (++mcp23018_number_keypad_reset_loop == 0) {
    // if (++mcp23018_reset_loop >= 1300) {
        // since mcp23018_reset_loop is 8 bit - we'll try to reset once in 255 matrix scans
        // this will be approx bit more frequent than once per second
      print("trying to reset mcp23018 in Number Keypad\n");
      mcp23018_status_number_keypad = init_mcp23018_number_keypad();
      if (mcp23018_status_number_keypad) {
          print("Number Keypad not responding\n");
      } else {
          print("Number Keypad attached\n");
          k19_blink_all_leds();
      }
    }
  }

  bool changed = false;

#if (DIODE_DIRECTION == COL2ROW)
  // Set row, read cols
  for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
    changed |= read_cols_on_row(raw_matrix, current_row);
  }
#elif (DIODE_DIRECTION == ROW2COL)
  // Set col, read rows
  for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
    changed |= read_rows_on_col(raw_matrix, current_col);
  }
#endif

  debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

  matrix_scan_quantum();
  return 1;
}

bool matrix_is_modified(void)
{
    if (debounce_active()) return false;
    return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    // Matrix mask lets you disable switches in the returned matrix data. For example, if you have a
    // switch blocker installed and the switch is always pressed.
#ifdef MATRIX_MASKED
    return matrix[row] & matrix_mask[row];
#else
    return matrix[row];
#endif
}

void matrix_print(void)
{
    print_matrix_header();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        print_matrix_row(row);
        print("\n");
    }
}

uint8_t matrix_key_count(void)
{
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += matrix_bitpop(i);
    }
    return count;
}



#if (DIODE_DIRECTION == COL2ROW)

static void init_cols(void)
{
    // init on mcp23018
    // not needed, already done as part of init_mcp23018()

    for(uint8_t x = 0; x < MATRIX_COLS_LEFT_KEYPAD; x++) {
        setPinInputHigh(col_pins[x]);
    }
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row)
{
    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];

    // Clear data in matrix row
    current_matrix[current_row] = 0;

    // Select row and wait for row selecton to stabilize
    select_row(current_row);

    // Select Row on MCP23018
    select_row_on_mcp23018(current_row);

    // Select Row on MCP23018
    select_row_on_mcp23018_number_keypad(current_row);

    // we don't need a 30us delay anymore, because selecting a
    // row on mcp23018 requires more than 30us for i2c.
    // wait_us(30);

    // For each col...
    for(uint8_t col_index = 0; col_index < MATRIX_COLS_LEFT_KEYPAD; col_index++) {

        // Select the col pin to read (active low)
        uint8_t pin_state = readPin(col_pins[col_index]);

        // Populate the matrix row with the state of the col pin
        current_matrix[current_row] |=  pin_state ? 0 : (ROW_SHIFTER << col_index);
    }

    // Unselect row
    unselect_row(current_row);

    uint8_t data = read_cols_on_mcp23018();

    // For each col...
    for(uint8_t col_index = 0; col_index < MATRIX_COLS_RIGHT_KEYPAD; col_index++) {

        uint8_t pin_state = data & ((uint8_t)1 << col_index);

        // Populate the matrix row with the state of the col pin
        current_matrix[current_row] |=  pin_state ? 0 : (ROW_SHIFTER << (col_index + MATRIX_COLS_LEFT_KEYPAD));
    }

    uint8_t data_number_keypad = read_cols_on_mcp23018_number_keypad();

    // For each col...
    for(uint8_t col_index = 0; col_index < MATRIX_COLS_NUMBER_KEYPAD; col_index++) {

        uint8_t pin_state = data_number_keypad & ((uint8_t)1 << col_index);

        // Populate the matrix row with the state of the col pin
        current_matrix[current_row] |=  pin_state ? 0 : (ROW_SHIFTER << (col_index + MATRIX_COLS_LEFT_KEYPAD + MATRIX_COLS_RIGHT_KEYPAD));
    }


    return (last_row_value != current_matrix[current_row]);
}

static void select_row(uint8_t row)
{
    setPinOutput(row_pins[row]);
    writePinLow(row_pins[row]);
}

static void unselect_row(uint8_t row)
{
    setPinInputHigh(row_pins[row]);
}

static void unselect_rows(void)
{
    for(uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInput(row_pins[x]);
    }
}

static void select_row_on_mcp23018(uint8_t row) {
    if (mcp23018_status) { // if there was an error
        // do nothing
    } else {

        /*
         * In the PCB design the rows are numbered as one to seven moving from bottom to top,
         * however, the QMK software starts numbering of the rows from top to bottom, that
         * means for QMK the top most row is row-one and the bottom most row is row-seven.
         * Keeping this in mind, the ordering of rows has been reversed here.
         */
        row = 6 - row;

        // set active row low  : 0
        // set other rows hi-Z : 1
        mcp23018_status = i2c_start(I2C_ADDR_WRITE, K19_I2C_TIMEOUT);       if (mcp23018_status) goto out;
        mcp23018_status = i2c_write(GPIOA, K19_I2C_TIMEOUT);                if (mcp23018_status) goto out;
        mcp23018_status = i2c_write(0xFF & ~(1 << row), K19_I2C_TIMEOUT);   if (mcp23018_status) goto out;
    out:
        i2c_stop();
    }
}

static void select_row_on_mcp23018_number_keypad(uint8_t row) {
    // If row number is either 0 or 1, then do nothing as these two rows do not exist on number keypad
    if (row <= 1) {
        return;
    }

    if (mcp23018_status_number_keypad) { // if there was an error
        // do nothing
    } else {

        /*
         * In the PCB design the rows are numbered as one to seven moving from bottom to top,
         * however, the QMK software starts numbering of the rows from top to bottom, that
         * means for QMK the top most row is row-one and the bottom most row is row-seven.
         * Keeping this in mind, the ordering of rows has been reversed here.
         */
        row = 6 - row;

        // set active row low  : 0
        // set other rows hi-Z : 1
        mcp23018_status_number_keypad = i2c_start(I2C_ADDR_NUMBER_KEYPAD_WRITE, K19_I2C_TIMEOUT);       if (mcp23018_status_number_keypad) goto out;
        mcp23018_status_number_keypad = i2c_write(GPIOA, K19_I2C_TIMEOUT);                              if (mcp23018_status_number_keypad) goto out;
        mcp23018_status_number_keypad = i2c_write(0xFF & ~(1 << row), K19_I2C_TIMEOUT);                 if (mcp23018_status_number_keypad) goto out;
    out:
        i2c_stop();
    }
}

static uint8_t read_cols_on_mcp23018() {
    if (mcp23018_status) { // if there was an error
        return 0;
    } else {
        uint8_t data = 0;
        mcp23018_status = i2c_start(I2C_ADDR_WRITE, K19_I2C_TIMEOUT);    if (mcp23018_status) goto out;
        mcp23018_status = i2c_write(GPIOB, K19_I2C_TIMEOUT);             if (mcp23018_status) goto out;
        mcp23018_status = i2c_start(I2C_ADDR_READ, K19_I2C_TIMEOUT);     if (mcp23018_status) goto out;
        mcp23018_status = i2c_read_nack(K19_I2C_TIMEOUT);                if (mcp23018_status < 0) goto out;
        data = ((uint8_t)mcp23018_status);
        mcp23018_status = I2C_STATUS_SUCCESS;
    out:
        i2c_stop();
        return data;
    }
}

static uint8_t read_cols_on_mcp23018_number_keypad() {
    if (mcp23018_status_number_keypad) { // if there was an error
        return 0;
    } else {
        uint8_t data = 0;
        mcp23018_status_number_keypad = i2c_start(I2C_ADDR_NUMBER_KEYPAD_WRITE, K19_I2C_TIMEOUT);    if (mcp23018_status_number_keypad) goto out;
        mcp23018_status_number_keypad = i2c_write(GPIOB, K19_I2C_TIMEOUT);             if (mcp23018_status_number_keypad) goto out;
        mcp23018_status_number_keypad = i2c_start(I2C_ADDR_NUMBER_KEYPAD_READ, K19_I2C_TIMEOUT);     if (mcp23018_status_number_keypad) goto out;
        mcp23018_status_number_keypad = i2c_read_nack(K19_I2C_TIMEOUT);                if (mcp23018_status_number_keypad < 0) goto out;
        data = ((uint8_t)mcp23018_status_number_keypad);
        mcp23018_status_number_keypad = I2C_STATUS_SUCCESS;
    out:
        i2c_stop();
        return data;
    }
}

#elif (DIODE_DIRECTION == ROW2COL)

static void init_rows(void)
{
    // init on mcp23018
    // not needed, already done as part of init_mcp23018()

    for(uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputHigh(row_pins[x]);
    }
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col)
{
    bool matrix_changed = false;

    // Select col and wait for col selecton to stabilize
    select_col(current_col);

    // Select Column on MCP23018
    select_col_on_mcp23018(current_col);

    // we don't need a 30us delay anymore, because selecting a
    // column on mcp23018 requires more than 30us for i2c.
    // wait_us(30);

    // For each row...
    for(uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++)
    {
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[row_index];

        // Check row pin state
        if (readPin(row_pins[row_index]) == 0)
        {
            // Pin LO, set col bit
            current_matrix[row_index] |= (ROW_SHIFTER << current_col);
        }
        else
        {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~(ROW_SHIFTER << current_col);
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_matrix[row_index]) && !(matrix_changed))
        {
            matrix_changed = true;
        }
    }

    // Unselect col
    unselect_col(current_col);

    uint8_t data = read_rows_on_mcp23018();

    for(uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++)
    {
        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[row_index];

        if ((data & ((uint8_t)1 << row_index)) == 0)
        {
            // Pin LO, set col bit
            current_matrix[row_index] |= (ROW_SHIFTER << (current_col + MATRIX_COLS_LEFT_KEYPAD));
        }
        else
        {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~(ROW_SHIFTER << (current_col + MATRIX_COLS_LEFT_KEYPAD));
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_matrix[row_index]) && !(matrix_changed))
        {
            matrix_changed = true;
        }
    }

    // no need to unselect col on mcp23018, because the select step sets all
    // the other row bits high, and it's not changing to a different
    // direction

    return matrix_changed;
}

static void select_col(uint8_t col)
{
    setPinOutput(col_pins[col]);
    writePinLow(col_pins[col]);
}

static void unselect_col(uint8_t col)
{
    setPinInputHigh(col_pins[col]);
}

static void unselect_cols(void)
{
    for(uint8_t x = 0; x < MATRIX_COLS_LEFT_KEYPAD; x++) {
        setPinInputHigh(col_pins[x]);
    }
}

static void select_col_on_mcp23018(uint8_t col) {
    if (mcp23018_status) { // if there was an error
        // do nothing
    } else {
        // set active col low  : 0
        // set other cols hi-Z : 1
        mcp23018_status = i2c_start(I2C_ADDR_WRITE, K19_I2C_TIMEOUT);       if (mcp23018_status) goto out;
        mcp23018_status = i2c_write(GPIOB, K19_I2C_TIMEOUT);                if (mcp23018_status) goto out;
        mcp23018_status = i2c_write(0xFF & ~(1 << col), K19_I2C_TIMEOUT);   if (mcp23018_status) goto out;
    out:
        i2c_stop();
    }
}

static uint8_t read_rows_on_mcp23018() {
    if (mcp23018_status) { // if there was an error
        return 0;
    } else {
        uint8_t data = 0;
        mcp23018_status = i2c_start(I2C_ADDR_WRITE, K19_I2C_TIMEOUT);    if (mcp23018_status) goto out;
        mcp23018_status = i2c_write(GPIOA, K19_I2C_TIMEOUT);             if (mcp23018_status) goto out;
        mcp23018_status = i2c_start(I2C_ADDR_READ, K19_I2C_TIMEOUT);     if (mcp23018_status) goto out;
        mcp23018_status = i2c_read_nack(K19_I2C_TIMEOUT);                if (mcp23018_status < 0) goto out;
        data = ((uint8_t)mcp23018_status);
        mcp23018_status = I2C_STATUS_SUCCESS;
    out:
        i2c_stop();
        return data;
    }
}

#endif

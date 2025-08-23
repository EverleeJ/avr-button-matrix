#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include "button-matrix.h"

uint8_t matrix_scan(void) {
  config conf;
  conf = matrix_config();

  uint8_t val = 0;  // default no key press (0)
  uint8_t row_num;  // row index (current row)
  uint8_t row_bit;  // bitmask for current row
  uint8_t col_num;  // col index (current col)
  uint8_t col_bit;  // bitmask for current col
  uint8_t cols;     // col input state

  *conf.ROW_PORT |= ~(conf.ROW_MASK);     // set all row lines to high (inactive)
  row_bit = (1 << conf.FIRST_ROW);  // start with first row bit

  // scan through rows
  for (row_num = 0; row_num < conf.ROWS; row_num++) {
    *conf.ROW_PORT &= ~(row_bit);  // set current row to low
    _delay_us(5);            // small delay for signal to stablize

    col_bit = 1 << conf.FIRST_COL;    // start with first col bit
    cols = ~(*conf.COL_PIN & conf.COL_MASK);  // read low column inputs (pressed = 0)

    *conf.ROW_PORT |= conf.ROW_MASK;  // set row back to high (inactive)

    for (col_num = 0; col_num < conf.COLS; col_num++) {
      if (cols & col_bit) {                    // if col active, keypress detected
        val = (row_num * conf.COLS) + col_num + 1;  // calculate key number
        return val;
      } else {
        col_bit <<= 1;  // next button in column
      }
    }
    row_bit <<= 1;  // left bitshift of 1 for next row
  }

  return val;  // no key press
}


#define FILTER_COUNT  (30/6)

uint8_t matrix_out(void) {
  // static so they remain the same through multiple function calls
  static uint8_t last_val = 0;  // remember last value seen
  static uint8_t count = 0;     // how many cycles val been the same
  uint8_t val;                  // current raw value
  uint8_t filtered_val = 0;     // filtered return val

  val = matrix_scan();          // get raw keypad value

  if (val != 0) {                            // if key is pressed
    if (val == last_val) {                   // if value same as last function call
      if ((count != 0) && (--count == 0)) {  // decrement count, if it reaches 0, its stable
        filtered_val = val;                  // accept the key as debounced
      }
    } else {
      count = FILTER_COUNT;  // if new key value detected, reset debounce counter
    }
  }

  last_val = val;       // rember value for next function call
  return filtered_val;  // return filtered value
}

void matrix_init(void) {
  config conf;
  conf = matrix_config();

  *conf.ROW_DDR |= conf.ROW_MASK;
  *conf.ROW_PORT |= conf.ROW_MASK;

  *conf.COL_DDR &= ~conf.COL_MASK;
  *conf.COL_PORT |= conf.COL_MASK;
}



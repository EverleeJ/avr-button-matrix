#define F_CPU  16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#define  ROW_PORT  PORTD
#define  ROW_DDR   DDRD
#define  COL_PORT  PORTB
#define  COL_DDR   DDRD
#define  COL_PIN   PIND

#define  ROWS  4
#define  COLS  4

#define  FIRST_ROW  4
#define  FIRST_COL  0

#define  ROW_MASK  0b11110000
#define  COL_MASK  0b1111

uint8_t keypad_scan(void) {
  uint8_t val = 0;  // default no key press (0)
  uint8_t row_num;  // row index (current row)
  uint8_t row_bit;  // bitmask for current row
  uint8_t col_num;  // col index (current col)
  uint8_t col_bit;  // bitmask for current col
  uint8_t cols;     // col input state

  ROW_PORT |= ~(ROW_MASK);     // set all row lines to high (inactive)
  row_bit = (1 << FIRST_ROW);  // start with first row bit

  // scan through rows
  for (row_num = 0; row_num < ROWS; row_num++) {
    ROW_PORT &= ~(row_bit);  // set current row to low
    _delay_us(5);            // small delay for signal to stablize

    col_bit = 1 << FIRST_COL;    // start with first col bit
    cols = ~COL_PIN & COL_MASK;  // read low column inputs (pressed = 0)

    ROW_PORT |= ROW_MASK;  // set row back to high (inactive)

    for (col_num = 0; col_num < COLS; col_num++) {
      if (cols & col_bit) {                    // if col active, keypress detected
        val = (row_num * COLS) + col_num + 1;  // calculate key number
        return val;
      } else {
        col_bit <<= 1;  // next button in column
      }
    }
    row_bit <<= 1;  // left bitshift of 1 for next row
  }

  return val;  // no key press
}

#define FILTER_COUNT  30/6

uint8_t keypad_out(void) {
  // static so they remain the same through multiple function calls
  static uint8_t last_val = 0;  // remember last value seen
  static uint8_t count = 0;     // how many cycles val been the same
  uint8_t val;                  // current raw value
  uint8_t filtered_val = 0;     // filtered return val

  val = keypad_scan();          // get raw keypad value

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

void keypad_init(void) {
  ROW_DDR |= ROW_MASK;
  ROW_PORT |= ROW_MASK;

  COL_DDR &= ~COL_MASK;
  COL_PORT |= COL_MASK;
}

int main() {
  keypad_init();

  DDRB |= (1 << DDB5);

  for (;;) {
    uint8_t out = keypad_out();
    if (out == 0) {
      PORTB |= (1 << PORTB5);
    } else {
      PORTB &= ~(1 << PORTB5);
    }
  }
  return 0;
}

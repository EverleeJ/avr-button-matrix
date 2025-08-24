#define  F_CPU  16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#include <button-matrix/button-matrix.h>  // edit to path to library in global include

config matrix_config(void) {
  config conf;

  conf.ROW_PORT = &PORTD;
  conf.ROW_DDR  = &DDRD;
  conf.COL_PORT = &PORTB;
  conf.COL_DDR  = &DDRB;
  conf.COL_PIN  = &PINB;

  conf.ROWS = 4;
  conf.COLS = 4;

  conf.FIRST_ROW = 4;
  conf.FIRST_COL = 0;

  conf.ROW_MASK = 0b11110000;
  conf.COL_MASK = 0b001111;

  return conf;
}

int main(void) {
  matrix_init();

  DDRB  |= (1 << DDB5);    // led set to out
  PORTB |= (1 << PORTB5);  // led on

  for (;;) {
    volatile uint8_t out = matrix_out();
    if (out != 0) {  // if any key pressed
      PORTB &= ~(1 << PORTB5);  // led off
      _delay_ms(500);
    }
    PORTB |= (1 << PORTB5);  // led on
  }

  return 0;
}

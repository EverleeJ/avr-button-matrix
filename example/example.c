#define F_CPU  16000000UL
#include <avr/io.h>
#include <util/delay.h>

#include "keypad/keypad.h"
#include "keypad/keypad.c"

keypad_config_struct keypad_config() {
  keypad_config_struct conf;

  conf.ROW_PORT = PORTD;
  conf.ROW_DDR  = DDRD;
  conf.COL_PORT = PORTB;
  conf.COL_DDR  = DDRD;
  conf.COL_PIN  = PINB;

  conf.ROWS = 4;
  conf.COLS = 4;

  conf.FIRST_ROW = 4;
  conf.FIRST_COL = 0;

  conf.ROW_MASK = 0b00001111;
  conf.COL_MASK = 0b1111000;

  return conf;
}

int main(void) {
  keypad_config_struct conf;
  conf = keypad_config();

  keypad_init();

  DDRB |= (1 << DDB5);
  PORTB |= (1 << PORTB5);

  for(;;) {
    uint8_t out = keypad_out();

    if (out == 0) {
      PORTB |= (1 << PORTB5);
      _delay_ms(100);
    } else {
      PORTB &= ~(1 << PORTB5);
      _delay_ms(100);
    }
  }

  return 0;
}

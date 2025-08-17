# avr-button-matrix

avr-button-matrix is a barebones, easy to use library written in AVR-GCC for any AVR microcontroller

## Installation (Linux/WSL)
***WARNING:*** Must have AVR-GCC installed before installing and using library

Use git-clone to clone repo to global include path

```bash
git clone git@github.com:EverleeJ/avr-button-matrix.git /usr/include/avr-button-matrix
```

## Usage
**See [example](https://github.com/EverleeJ/avr-button-matrix/tree/main/example/example.c)**

Library depends upon the initialization of `matrix_config()` in src - delcared as a prototype in button_matrix.h
`matrix_config()` should initialize and return the `config` type - also declared in button_matrix.h

```c
config matrix_config(void) {
  config conf;

  conf.ROW_PORT = PORTD;
  conf.ROW_DDR  = DDRD;
  conf.COL_PORT = PORTB;
  conf.COL_DDR  = DDRB;
  conf.COL_PIN  = PINB;

  conf.ROWS = 4;
  conf.COLS = 4;

  conf.FIRST_ROW = 4;
  conf.FIRST_COL = 0;

  conf.ROW_MASK = 0b11110000;
  conf.COL_MASK = 0b001111;

  return conf;
}
```

## License
[MIT](https://github.com/EverleeJ/avr-button-matrix/blob/main/LICENSE)

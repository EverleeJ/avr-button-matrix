#ifndef  BUTTON_MATRIX
#define  BUTTON_MATRIX

#include <stdint.h>


// configure location of button matrix on microcontroller
typedef struct Config {
  uint8_t ROW_PORT;
  uint8_t ROW_DDR;
  uint8_t COL_PORT;
  uint8_t COL_DDR;
  uint8_t COL_PIN;

  uint8_t ROWS;
  uint8_t COLS;

  uint8_t FIRST_ROW;
  uint8_t FIRST_COL;

  uint8_t ROW_MASK;
  uint8_t COL_MASK;
} config;

// prototypes
config  matrix_config(void);  // user initializes in src
uint8_t matrix_scan(void);    // get input from user, return raw output
uint8_t matrix_out(void);     // filter raw output, return filtered output
void    matrix_init(void);    // set up IO ports for matrix

#endif  // BUTTON_MATRIX

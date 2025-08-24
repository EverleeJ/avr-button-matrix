SRC = main button-matrix
MCU = atmega328p
F_CPU = 16000000UL
PORT = /dev/ttyUSB0
BAUD = 115200

BIN_DIR = bin

$(BIN_DIR)/main.hex: $(BIN_DIR)/main.elf
	avr-objcopy -O ihex -R .eeprom $(BIN_DIR)/main.elf $(BIN_DIR)/main.hex

$(BIN_DIR)/main.elf: $(BIN_DIR)/main.o $(BIN_DIR)/button-matrix.o
	avr-gcc -DF_CPU=$(F_CPU) -mmcu=$(MCU) -o $(BIN_DIR)/main.elf $(BIN_DIR)/main.o $(BIN_DIR)/button-matrix.o

$(BIN_DIR)/%.o: %.c
	mkdir -p $(BIN_DIR)
	avr-gcc -Os -DF_CPU=$(F_CPU) -mmcu=$(MCU) -c $< -o $@

flash: $(BIN_DIR)/main.hex
	sudo avrdude -F -V -c arduino -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(BIN_DIR)/main.hex

clean:
	rm -rf $(BIN_DIR)

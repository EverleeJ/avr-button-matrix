SRC = main

default:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o bin/$(SRC).o $(SRC).c
	avr-gcc -DF_CPU=16000000UL -mmcu=atmega328p -o bin/$(SRC).elf bin/$(SRC).o
	avr-objcopy -O ihex -R .eeprom bin/$(SRC).elf bin/$(SRC).hex
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b 115200 -U flash:w:bin/$(SRC).hex

clean:
	rm -f bin/$(SRC).o bin/$(SRC).elf bin/$(SRC).hex bin/$(SRC).bin

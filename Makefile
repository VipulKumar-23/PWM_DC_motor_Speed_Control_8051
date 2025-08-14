# ==============================================================================
# Makefile for 8051 PWM DC Motor Speed Control
# Target Compiler: SDCC (Small Device C Compiler) / Keil C51
# Target MCU: AT89C51 / AT89S51 (11.0592 MHz)
# ==============================================================================

CC      = sdcc
CFLAGS  = -mmcs51 --model-small -Iinc
PACK_HEX = packihx

SRC     = src/main.c src/motor.c src/pwm.c src/delay.c
OBJS    = $(SRC:.c=.rel)
TARGET  = pwm_motor_control

all: $(TARGET).hex

$(TARGET).ihx: $(SRC)
	@echo "Compiling firmware with SDCC..."
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET).ihx

$(TARGET).hex: $(TARGET).ihx
	@echo "Generating Intel HEX file..."
	$(PACK_HEX) $(TARGET).ihx > $(TARGET).hex
	@echo "Build successful: $(TARGET).hex generated."

clean:
	@echo "Cleaning intermediate build artifacts..."
	rm -f *.asm *.ihx *.lnk *.lst *.map *.mem *.rel *.rst *.sym *.hex
	rm -f src/*.asm src/*.lst src/*.rel src/*.sym

.PHONY: all clean

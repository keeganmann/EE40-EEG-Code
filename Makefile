############### CONFIGURATION SETTINGS:

DEVICE     = atmega328p

#CLOCK      = 1000000  #comment out if defined in source
OBJECTS    = main.o nyan.o

FUSES      = ""

PROGRAMMER_FLAGS =  -c usbtiny -p $(DEVICE) -B 3

############### END OF CONFIGURATION SETTINGS ##############

AVRDUDE = avrdude $(PROGRAMMER_FLAGS)
COMPILE = avr-gcc -Wall -Os -mmcu=$(DEVICE)

# symbolic targets:
all:	main.hex

.c.o:
	$(COMPILE) -c $< -o $@

.S.o:
	$(COMPILE) -x assembler-with-cpp -c $< -o $@

.c.s:
	$(COMPILE) -S $< -o $@

flash:	all
	$(AVRDUDE) -U flash:w:main.hex

fuse:
	$(AVRDUDE) $(FUSES)

read-fuse:
	$(AVRDUDE) -U lfuse:r:-:i -U hfuse:r:-:i

# Xcode uses the Makefile targets "", "clean" and "install"
install: flash fuse

clean:
	rm -f main.hex main.elf main.map main.lst $(OBJECTS) *.s

# file targets:
main.elf: $(OBJECTS)
	$(COMPILE) -o main.elf $(OBJECTS)

main.hex: main.elf
	rm -f main.hex
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex

main.map: $(OBJECTS)
	$(COMPILE) -Wl,-Map,main.map -o main.elf $(OBJECTS)

main.lst: main.elf
	avr-objdump -h -S main.elf > main.lst

size: main.elf
	avr-size -C --mcu=$(DEVICE) main.elf

# Arduino Makefile
# Arduino adaptation by mellis, eighthave, oli.keller
# Modified by Kerry Wong to support NetBeans
# Modified by Rob Gray (Graynomad) for use with Windows and no IDE
#   This works in my environment and I use it to program two different 
#   328-based boards and a Mega2560. It's not necessarily robust and 
#   I may have broken something in the original file that I don't use.
#
# This makefile allows you to build sketches from the command line
# without the Arduino environment.
#
# Instructions for using the makefile:
#
#  1. Copy this file into the folder with your sketch. The project code file
#	  should have a .c extension however the file gets copied to a .cpp before
#     compilation so you still write in C++.
#
#  2. Modify the lines between the double ### rows to set the paths 
#     comm ports etc for your system. EG. c:/progra~1/arduino/arduino-00
#     for the Arduino IDE, Note the use of short folder name, don't use
#     "Program files" because spaces will break the build.
#
#     Set the line containing "MCU" to match your board's processor.
#     Typically ATmega328 or ATmega2560.  If you're using a LilyPad Arduino,
#     change F_CPU to 8000000.
#
#  3. At the command line, change to the directory containing your
#     program's file and the makefile.
#
#  4. Type "make" and press enter to compile/verify your program.
#     The default make target will also perform the uplode using avrdude.
#
#     The first time this is done all required libraries will be built
#     and a core.a file will be created in the output folder.
#
#  NOTES:
#     All output goes into a folder called "output" underneath the working folder.
#     The default all: target creates symbol (.sym) and expanded assembly 
#     (.lss) files and uploads the program.
#
#
##########################################################
##########################################################
# Select processor here
MCU 			= atmega328p
#MCU 			= atmega2560

ifeq ($(MCU),atmega2560)
UPLOAD_RATE 	= 115200
AVRDUDE_PROTOCOL = stk500v2
COM 			= 39
endif

ifeq ($(MCU),atmega328p)
UPLOAD_RATE 	= 57600
AVRDUDE_PROTOCOL = stk500v1
COM 			= 33
endif

UNAME := $(shell uname)

ifeq ($(UNAME),Darwin)
ARDUINO_VERSION	= 21
ARDUINO_DIR 	= /opt/arduino-00$(ARDUINO_VERSION)
AVR_TOOLS_PATH 	= $(ARDUINO_DIR)/hardware/tools/avr/bin
AVRDUDECONFIG_PATH = $(ARDUINO_DIR)/hardware/tools/avr/etc
PORT                    = /dev/tty.usbserial-A600eHIs 
PORT2                   = /dev/tty.usbserial-A9007LmI
else
ARDUINO_VERSION	= 22
ARDUINO_DIR 	= /opt/arduino-00$(ARDUINO_VERSION)
AVR_TOOLS_PATH 	= /usr/bin
AVRDUDECONFIG_PATH = $(ARDUINO_DIR)/hardware/tools
PORT 			= /dev/ttyUSB0
PORT2 			= /dev/ttyUSB1
endif

PROJECT_NAME 	= $(notdir $(PWD))
PROJECT_DIR 	= . 
ARDUINO_CORE 	= $(ARDUINO_DIR)/hardware/arduino/cores/arduino
ARDUINO_AVR 	= $(ARDUINO_DIR)/hardware/tools/avr/avr/include/avr
ARDUINO_LIB 	= $(ARDUINO_DIR)/libraries
F_CPU 			= 16000000

##########################################################
##########################################################

# Note that if your program has dependencies other than those
# already listed below, you will need to add them accordingly.
C_MODULES =  \
$(ARDUINO_CORE)/wiring_pulse.c \
$(ARDUINO_CORE)/wiring_analog.c \
$(ARDUINO_CORE)/pins_arduino.c \
$(ARDUINO_CORE)/wiring.c \
$(ARDUINO_CORE)/wiring_digital.c \
$(ARDUINO_CORE)/WInterrupts.c \
$(ARDUINO_CORE)/wiring_shift.c \

CXX_MODULES = \
$(ARDUINO_CORE)/Tone.cpp \
$(ARDUINO_CORE)/main.cpp \
$(ARDUINO_CORE)/WMath.cpp \
$(ARDUINO_CORE)/Print.cpp \
$(ARDUINO_CORE)/HardwareSerial.cpp \
$(ARDUINO_LIB)/SPI/SPI.cpp \
$(ARDUINO_LIB)/EEPROM/EEPROM.cpp \
../../RF24.cpp

CXX_APP 	= output/$(PROJECT_NAME).cpp
MODULES 	= $(C_MODULES) $(CXX_MODULES)
SRC 		= $(C_MODULES)
CXXSRC 		= $(CXX_MODULES) $(CXX_APP)
FORMAT 		= ihex

# Name of this Makefile (used for "make depend").
MAKEFILE = Makefile

# Debugging format.
# Native formats for AVR-GCC's -g are stabs [default], or dwarf-2.
# AVR (extended) COFF requires stabs, plus an avr-objcopy run.
#DEBUG = stabs
DEBUG =

OPT = s

# Place -D or -U options here
CDEFS = -DF_CPU=$(F_CPU)L -DARDUINO=$(ARDUINO_VERSION)
CXXDEFS = -DF_CPU=$(F_CPU)L -DARDUINO=$(ARDUINO_VERSION)

# Place -I options here
CINCS =  -I$(ARDUINO_LIB)/EEPROM -I$(ARDUINO_CORE) -I$(ARDUINO_LIB) -I$(PROJECT_DIR) -I$(ARDUINO_AVR) -I$(ARDUINO_LIB)/SPI -I../..

CXXINCS = -I$(ARDUINO_CORE) -I$(ARDUINO_LIB)

# Compiler flag to set the C Standard level.
# c89   - "ANSI" C
# gnu89 - c89 plus GCC extensions
# c99   - ISO C99 standard (not yet fully implemented)
# gnu99 - c99 plus GCC extensions
#CSTANDARD = -std=gnu99
CDEBUG 		= -g$(DEBUG)
#CWARN 		= -Wall -Wstrict-prototypes
CWARN 		= -Wall   # show all warnings
#CWARN 		= -w      # suppress all warnings
CMAP		= -Wl,-Map,output.map 
####CTUNING = -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CTUNING = -ffunction-sections -fdata-sections
CXXTUNING = -fno-exceptions -ffunction-sections -fdata-sections
#CEXTRA = -Wa,-adhlns=$(<:.c=.lst)
MMCU 		= -mmcu=$(MCU)

CFLAGS = $(CDEBUG) -O$(OPT) $(CMAP) $(CWARN) $(CTUNING) $(MMCU) $(CDEFS) $(CINCS) $(CSTANDARD) $(CEXTRA)
CXXFLAGS = $(CDEBUG) -O$(OPT) $(CWARN) $(CXXTUNING) $(CDEFS) $(CINCS)
#ASFLAGS = -Wa,-adhlns=$(<:.S=.lst),-gstabs
LDFLAGS = -O$(OPT) -lm -Wl,--gc-sections
#LDFLAGS = -O$(OPT) -lm -Wl,-Map,output/$(PROJECT_NAME).map 

# Programming support using avrdude. Settings and variables.
AVRDUDE_PORT = $(PORT)
AVRDUDE_WRITE_FLASH = -U flash:w:output/$(PROJECT_NAME).hex:i

AVRDUDE_FLAGS = -V -F -D -C $(AVRDUDECONFIG_PATH)/avrdude.conf \
-p $(MCU) -c $(AVRDUDE_PROTOCOL) -b $(UPLOAD_RATE)

# Program settings
CC 			= $(AVR_TOOLS_PATH)/avr-gcc
CXX 		= $(AVR_TOOLS_PATH)/avr-g++
LD 			= $(AVR_TOOLS_PATH)/avr-gcc
OBJCOPY 	= $(AVR_TOOLS_PATH)/avr-objcopy
OBJDUMP 	= $(AVR_TOOLS_PATH)/avr-objdump
AR 			= $(AVR_TOOLS_PATH)/avr-ar
SIZE 		= $(AVR_TOOLS_PATH)/avr-size
NM 			= $(AVR_TOOLS_PATH)/avr-nm
AVRDUDE 	= $(AVR_TOOLS_PATH)/avrdude
REMOVE 		= rm -f
MV 			= mv -f

# Define all object files.
OBJ = $(SRC:.c=.o) $(CXXSRC:.cpp=.o) $(ASRC:.S=.o)
OBJ_MODULES = $(C_MODULES:.c=.o) $(CXX_MODULES:.cpp=.o)

# Define all listing files.
LST = $(ASRC:.S=.lst) $(CXXSRC:.cpp=.lst) $(SRC:.c=.lst)

# Combine all necessary flags and optional flags.
# Add target processor to flags.
ALL_CFLAGS 	= $(CFLAGS) -mmcu=$(MCU)
ALL_CXXFLAGS = $(CXXFLAGS) -mmcu=$(MCU)
ALL_ASFLAGS = -x assembler-with-cpp $(ASFLAGS) -mmcu=$(MCU)
ALL_LDFLAGS = $(LDFLAGS) -mmcu=$(MCU)

# Default target.
# This is th etarget that gets executed with a make command
# that has no parameters, ie "make".
all: applet_files build sym lss size upload

build: elf hex

output/$(PROJECT_NAME).cpp: $(PROJECT_NAME).pde
	test -d output || mkdir output
	echo "#include <WProgram.h>" > $@ 
	echo "#line 1 \"$<\"" >> $@ 
	cat $< >> $@ 

elf: output/$(PROJECT_NAME).elf
hex: output/$(PROJECT_NAME).hex
eep: output/$(PROJECT_NAME).eep
lss: output/$(PROJECT_NAME).lss
#sym: output/$(PROJECT_NAME).sym

# Upload HEX file to Arduino
upload: upload1 upload2

upload1: output/$(PROJECT_NAME).hex
	$(AVRDUDE) $(AVRDUDE_FLAGS) -P $(PORT) $(AVRDUDE_WRITE_FLASH)

upload2: output/$(PROJECT_NAME).hex
	$(AVRDUDE) $(AVRDUDE_FLAGS) -P $(PORT2) $(AVRDUDE_WRITE_FLASH)

sym:
	$(NM) -n -C --format=posix output/$(PROJECT_NAME).elf > output/$(PROJECT_NAME).sym
	
# Display size of file.
size:
	$(SIZE) output/$(PROJECT_NAME).elf
	
# Convert ELF to COFF for use in debugging / simulating in AVR Studio or VMLAB.
COFFCONVERT=$(OBJCOPY) --debugging \
--change-section-address .data-0x800000 \
--change-section-address .bss-0x800000 \
--change-section-address .noinit-0x800000 \
--change-section-address .eeprom-0x810000

coff: output/$(PROJECT_NAME).elf
	$(COFFCONVERT) -O coff-avr output/$(PROJECT_NAME).elf $(PROJECT_NAME).cof

	extcoff: $(PROJECT_NAME).elf
	$(COFFCONVERT) -O coff-ext-avr output/$(PROJECT_NAME).elf $(PROJECT_NAME).cof

.SUFFIXES: .elf .hex .eep .lss .sym

.elf.hex:
	$(OBJCOPY) -O $(FORMAT) -R .eeprom $< $@

.elf.eep:
	$(OBJCOPY) -O $(FORMAT) -j .eeprom --set-section-flags=.eeprom="alloc,load" \
	--no-change-warnings \
	--change-section-lma .eeprom=0 $< $@

# Create extended listing file from ELF output file.
.elf.lss:
	$(OBJDUMP) -h -S $< > $@

# Link: create ELF output file from library.
#output/$(PROJECT_NAME).elf: $(PROJECT_NAME).c output/core.a
output/$(PROJECT_NAME).elf: output/$(PROJECT_NAME).o output/core.a
	$(LD) $(ALL_LDFLAGS) -o $@ output/$(PROJECT_NAME).o output/core.a

output/core.a: $(OBJ_MODULES)
	@for i in $(OBJ_MODULES); do echo $(AR) rcs output/core.a $$i; $(AR) rcs output/core.a $$i; done

# Compile: create object files from C++ source files.
.cpp.o:
	$(CXX) -c $(ALL_CXXFLAGS) $< -o $@

# Compile: create object files from C source files.
.c.o:
	$(CC) -c $(ALL_CFLAGS) $< -o $@

# Compile: create assembler files from C source files.
.c.s:
	$(CC) -S $(ALL_CFLAGS) $< -o $@

# Assemble: create object files from assembler source files.
.S.o:
	$(CC) -c $(ALL_ASFLAGS) $< -o $@

# Automatic dependencies
%.d: %.c
	$(CC) -M $(ALL_CFLAGS) $< | sed "s;$(notdir $*).o:;$*.o $*.d:;" > $@

%.d: %.cpp
	$(CXX) -M $(ALL_CXXFLAGS) $< | sed "s;$(notdir $*).o:;$*.o $*.d:;" > $@

# Target: clean project.
clean:
	$(REMOVE) output/$(PROJECT_NAME).hex output/$(PROJECT_NAME).eep output/$(PROJECT_NAME).cof output/$(PROJECT_NAME).elf \
	output/$(PROJECT_NAME).map output/$(PROJECT_NAME).sym output/$(PROJECT_NAME).lss output/core.a \
	$(OBJ) $(LST) $(SRC:.c=.s) $(SRC:.c=.d) $(CXXSRC:.cpp=.s) $(CXXSRC:.cpp=.d)

#.PHONY:	all build elf hex eep lss sym program coff extcoff clean applet_files sizebefore sizeafter
.PHONY:		all build elf hex eep lss sym program coff extcoff applet_files sizebefore sizeafter

#include $(SRC:.c=.d)
#include $(CXXSRC:.cpp=.d)

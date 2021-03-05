MCU 	:= atmega328p
CC		:= avr-gcc
CFLAGS	:= -Wall -Wextra -g -O1 -mmcu=$(MCU)

BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib

LIBRARIES	:=

ifeq ($(OS),Windows_NT)
EXECUTABLE	:= main.exe
else
EXECUTABLE	:= main
endif

SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)

CINCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))
CLIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

SOURCES		:= $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))
OBJECTS		:= $(SOURCES:.c=.o)


all: $(BIN)/$(EXECUTABLE)

.PHONY: clean
clean:
	-$(RM) $(BIN)/$(EXECUTABLE).hex
	-$(RM) $(BIN)/$(EXECUTABLE)
	-$(RM) $(OBJECTS)


run: all
	avr-objcopy -j .text -j .data -O ihex $(BIN)/$(EXECUTABLE) $(BIN)/$(EXECUTABLE).hex
	avrdude -p $(MCU) -c arduino -b 115200 -Uflash:w:$(BIN)/$(EXECUTABLE).hex:i -P /dev/serial/by-id/*

$(BIN)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(CINCLUDES) $(CLIBS) $^ -o $@ $(LIBRARIES)
	
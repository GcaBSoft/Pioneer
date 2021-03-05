#ifndef __CDJ800_JOG_DISPLAY_H__
#define __CDJ800_JOG_DISPLAY_H__


#ifndef __AVR_ATmega328P__
#define	__AVR_ATmega328P__
#endif


#include "time.h"
#include <stdint.h>
#include <avr/io.h>	

///////////IO-PINS/////////////////////
#define LATCH_DDR           DDRB
#define BLANK_DDR           DDRB
#define DATA_OUT_DDR        DDRB
#define CLK_DDR             DDRB

#define LATCH_PORT          PORTB
#define BLANK_PORT          PORTB
#define DATA_OUT_PORT       PORTB
#define CLK_PORT            PORTB

#define LATCH               PORTB1
#define BLANK               PORTB2
#define DATA_OUT            PORTB3
#define CLK                 PORTB5

#define LATCH_PIN           PINB
///////////////////////////////////////
void CDJ800_Jog_Display_Setup();
void CDJ800_Jog_Display_Write(uint8_t data);
void CDJ800_Jog_Display_Latch();

#endif
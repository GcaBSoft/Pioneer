/*
#ifndef __AVR_ATmega328P__
#define	__AVR_ATmega328P__
#endif
#define F_CPU 16000000UL
#include <avr/io.h>
#include "uart.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include "time.h"
#include "MIDI.h"
#include "cdj800_buttons.h"
#include "led.h"
#define DEBOUNCE		50
#define CDJ_PLAY        PORTC0
#define CDJ_CUE         PORTC1
#define CDJ_TRACK       PORTC2

#define CDJ_CUE_LED     PORTB0 
#define CDJ_PLAY_LED    PORTB1
    
#define CDJ_LED_PORT    PORTB
#define CDJ_SW_PORT     PORTC

#define MIDI_LED_CUE	0x26
#define MIDI_LED_PLAY	0x27


typedef struct _cdjLeds
{
    LED play;
    LED cue;
}CDJ800_LEDS;
typedef struct _cdj
{
    CDJ800_BUTTONS buttons;
    CDJ800_LEDS leds;
}CDJ800;

void Handle_Midi(MIDI *midi,CDJ800 * cdj);

int main()
{
	MIDI * midi = MIDI_Setup(1);
	CDJ800 cdj;
	cdj.buttons = CDJ800_Buttons_Setup();
	cdj.leds.cue = Led_Setup(&CDJ_LED_PORT,CDJ_CUE_LED,250,LED_STATE_OFF);
	cdj.leds.play = Led_Setup(&CDJ_LED_PORT,CDJ_PLAY_LED,500,LED_STATE_OFF);
	while(1)
	{
		Led_Update(&cdj.leds.cue);
		Led_Update(&cdj.leds.play);
		CDJ800_Buttons_Update(&cdj.buttons,midi);
		Handle_Midi(midi,&cdj);				
	}
}
void Handle_Midi(MIDI *midi,CDJ800 * cdj)
{
	uint8_t data[256];
	int size = 0;
	switch(MIDI_Read(midi,data,&size,256)&0xf0)
	{
		case MIDI_CONTROL_CHANGE:
		{
			switch(data[0])
			{
				case MIDI_LED_PLAY:
					Led_Set(&cdj->leds.play,data[1]);
				break;
				case MIDI_LED_CUE:
					Led_Set(&cdj->leds.cue,data[1]);
				break;
			}
		}{
	SPDR = data;
    while(!(SPSR & (1<<SPIF)));
	
		break;	
	}
}

*/

#ifndef __AVR_ATmega328P__
#define	__AVR_ATmega328P__
#endif
#define F_CPU 16000000UL
#include <avr/io.h>
#include "uart.h"
#include <avr/interrupt.h>
#include <util/delay.h>

#define LATCH       PORTB1
#define BLANK       PORTB2
#define DATA_OUT    PORTB3
#define CLK         PORTB5

#define BLANK_BUTTON    PORTC0
#define LATCH_BUTTON    PORTC1
#define SEND            PORTC2
void clear();
void Full();
void draw (unsigned char * data,int size);
#include "cdj800_jog_display.h"

uint8_t left [16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
void drawLeft (unsigned char * data,int size);
void setleft(uint8_t pos);
void setAll(uint8_t pos);
//0-73 right 74-135 left
int main() 
{
	Time_Setup();
	uint32_t oldtime = 0;
	int16_t i =135;
	CDJ800_Jog_Display_Setup();
    unsigned char data[16] ={0b00000000,0b00000000,0b00000001,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,
                                0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b01111111};
    //draw(data,16);
	while(1)
	{
		if(Time_Get() - oldtime> 500)
		{
			//setleft(i++);
			for(int j = 0;j<16;j++)
				left[j] = 0;
			setAll(i--);
			setAll(i);
			setAll(i-1);
			drawLeft(0,0);
			oldtime = Time_Get();
		}
        for(int i =0;i<25;i++)
        {
            _delay_ms(10);
            PORTB &=~(1<<BLANK);
            _delay_ms(1);
            PORTB |=(1<<BLANK);
        }
       
	}
}
#define JOG_DISPLAY_RIGHT		(1<<1)
#define JOG_DISPLAY_LEFT		(1<<2)
#define JOG_DISPLAY_VINYL		(1<<4)
#define JOG_DISPLAY_TOUCHED		(1<<5)
#define JOG_DISPLAY_TOUCHED2	(1<<6)
#define JOG_DISPLAY_SEGMENT1	(1<<7)
#define JOG_DISPLAY_SEGMENT2	(1<<0)
#define JOG_DISPLAY_SEGMENT3	(1<<1)
#define JOG_DISPLAY_SEGMENT4	(1<<2)
#define JOG_DISPLAY_SEGMENT5	(1<<3)
#define JOG_DISPLAY_SEGMENT6	(1<<4)
#define JOG_DISPLAY_SEGMENT7	(1<<5)


void setleft(uint8_t pos)
{
	if(pos == 0)
		left[0] |= (1<<7);
	else if( pos<= 16)
		left[ ((pos)/9)+1] |= (1<<((pos-1)%8));
	else if (pos == 17)
		left[3] |= (1<<3);
	else if (pos == 18)
		left[3] |= (1<<7);
	else if (pos <=54)
	{
		pos -= 19;
		left[4+pos/4] |= (1<<(1+(pos%4)*2));
	}
	else if (pos == 55)
		left[13] |= (1<<2);
	else if (pos == 56)
		left[13] |= (1<<5);
	else if( pos<= 64)
		left[14] |= (1<<(pos-57));
	else if( pos<= 72)
		left[15] |= (1<<(pos-65));
}
void setAll(uint8_t pos)
{
	if(pos > 72)
		pos = (134-pos)+6;
	if(pos == 0)
		left[0] |= (1<<7);
	else if( pos<= 16)
		left[ ((pos)/9)+1] |= (1<<((pos-1)%8));
	else if (pos == 17)
		left[3] |= (1<<3);
	else if (pos == 18)
		left[3] |= (1<<7);
	else if (pos <=54)
	{
		pos -= 19;
		left[4+pos/4] |= (1<<(1+(pos%4)*2));
	}
	else if (pos == 55)
		left[13] |= (1<<2);
	else if (pos == 56)
		left[13] |= (1<<5);
	else if( pos<= 64)
		left[14] |= (1<<(pos-57));
	else if( pos<= 72)
		left[15] |= (1<<(pos-65));
}
void drawLeft (unsigned char * data,int size)
{
    PORTB |=(1<<BLANK);
	CDJ800_Jog_Display_Write( left[0] | JOG_DISPLAY_RIGHT | JOG_DISPLAY_LEFT); //JOG (1<<7);
	for(int i = 1;i<16;i++)
		CDJ800_Jog_Display_Write(left[i]);
	CDJ800_Jog_Display_Latch();
}
void draw (unsigned char * data,int size)
{
    PORTB |=(1<<BLANK);
	CDJ800_Jog_Display_Write(  JOG_DISPLAY_LEFT); //JOG (1<<7);
	CDJ800_Jog_Display_Write(0xFF);	//BOTTOM Jog only 5-7 shared
	CDJ800_Jog_Display_Write(0xFF);	//BOTTOM Jog only shared
	CDJ800_Jog_Display_Write(0xFF); //JOG : 7-3 CUE: 6-5-4-2-1 //mask cue 0x77
	CDJ800_Jog_Display_Write(0xFF);//alternate	mask 0x55
	CDJ800_Jog_Display_Write(0xFF);
	CDJ800_Jog_Display_Write(0xFF);
	CDJ800_Jog_Display_Write(0xFF);
	CDJ800_Jog_Display_Write(0xFF);
	CDJ800_Jog_Display_Write(0xFF);
	CDJ800_Jog_Display_Write(0xFF);
	CDJ800_Jog_Display_Write(0xFF);
	CDJ800_Jog_Display_Write(0xFF);//alternate 0x55 = cues on
	CDJ800_Jog_Display_Write(0xFF); //CUE on //mas cue 0xdB
	CDJ800_Jog_Display_Write(0xFF); //TOP jog only shared left right
	CDJ800_Jog_Display_Write(0xFF); //TOP Jog only (1<<0) 1 2 is shared
	CDJ800_Jog_Display_Latch();
}

void Full()
{
    PORTB &=~(1<<BLANK);
    for(int i =0;i<15;i++)
    {
        SPDR = 0xFF;
        while(!(SPSR & (1<<SPIF)));
        PORTB |=(1<<LATCH);
        while(!(PINB & (1<<LATCH)));
        _delay_us(400);
        PORTB &=~(1<<LATCH);
        _delay_ms(500);
    }
    PORTD |=(1<<2);
    _delay_ms(1000);
    SPDR = 0x00;
    while(!(SPSR & (1<<SPIF)));
    PORTB |=(1<<LATCH);
    while(!(PINB & (1<<LATCH)));
    _delay_us(400);
    PORTB &=~(1<<LATCH);
    for(int i =0;i<15;i++)
    {
        SPDR = 0xFF;
        while(!(SPSR & (1<<SPIF)));
        PORTB |=(1<<LATCH);
        while(!(PINB & (1<<LATCH)));
        _delay_us(400);
        PORTB &=~(1<<LATCH);
        _delay_ms(500);
    }
    
    PORTB &=~(1<<LATCH);
    _delay_ms(1000);
    PORTB |=(1<<BLANK);
    _delay_ms(1000);
    PORTB &=~(1<<BLANK);
}

void clear()
{
    PORTB &=~(1<<BLANK);
    for(int i =0;i<16;i++)
    {
        SPDR = 0x00;
        while(!(SPSR & (1<<SPIF)));
    }
    PORTB |=(1<<LATCH);
    while(!(PINB & (1<<LATCH)));
    _delay_us(400);
    PORTB &=~(1<<LATCH);
    _delay_ms(1000);
    PORTB |=(1<<BLANK);
    _delay_ms(1000);
    PORTB &=~(1<<BLANK);
}
#ifndef __CDJ800_DISPLAY_H__
#define __CDJ800_DISPLAY_H__


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

#define TEMPO_PROCENT       0x01    //(1<<0)  
#define TEMPO_DOT1          0x02    //(1<<1)  
#define TEMPO_DOT2          0x04    //(1<<2)  
#define TEMPO_VERT_LINE     0x08    //(1<<3)  
#define TEMPO_HOR_LINE      0x10    //(1<<4)  
#define TEMPO_WIDE          0x20    //(1<<5)  
#define TEMPO_MT            0x40    //(1<<6)  
#define TEMPO_SQUARE        0x80    //(1<<7)  

#define TRACK_DIGIT1        0
#define TRACK_DIGIT2        2
#define TRACK_DIGIT3        4

#define DECIMAL_POINT1      1
#define DECIMAL_POINT2      2

#define DISPLAY_HEADER_TRACK    0x01
#define DISPLAY_HEADER_FOLDER   0x02
#define DISPLAY_HEADER_ACUE     0x04
#define DISPLAY_HEADER_REMAIN   0x08
#define DISPLAY_HEADER_TIME     0x10



typedef struct _cdjDisplayTempo
{
    uint8_t digits[6];
    uint8_t indicators;
}CDJ800_DISPLAY_TEMPO;
typedef struct _cdjDisplayProgress
{
    uint8_t progress[5];
    uint8_t cues[5];
    uint8_t inverted;
}CDJ800_DISPLAY_PROGRESS;
typedef struct _cdjDisplaySegments
{
    uint8_t data[10];
}CDJ800_DISPLAY_SEGMENT;

typedef struct _cdjDisplay
{
    CDJ800_DISPLAY_SEGMENT segments[6];
    CDJ800_DISPLAY_PROGRESS pogressBar;
    CDJ800_DISPLAY_TEMPO tempo;
}CDJ800_DATA_DISPLAY;

CDJ800_DATA_DISPLAY CDJ800_Display_Setup();
void CDJ800_Display_Write_String(CDJ800_DATA_DISPLAY * display,uint8_t start,char * string);
void CDJ800_Display_Write_Char(CDJ800_DATA_DISPLAY * display,uint8_t segment,char character);
void CDJ800_Display_Track_Set(CDJ800_DATA_DISPLAY * display,uint16_t value);

void CDJ800_Display_Progress_Set(CDJ800_DATA_DISPLAY *display,int8_t progress);
void CDJ800_Display_Progress_Mode_Set(CDJ800_DATA_DISPLAY *display,int8_t inverted);

void CDJ800_Display_Cue_Set(CDJ800_DATA_DISPLAY *display,int8_t cue);
void CDJ800_Display_Cue_Clear(CDJ800_DATA_DISPLAY *display,int8_t cue);

void CDJ800_Display_Tempo_Set(CDJ800_DATA_DISPLAY *display , uint16_t value);
void CDJ800_Display_Tempo_Indicators_Set(CDJ800_DATA_DISPLAY *display, uint8_t indicators);
void CDJ800_Display_Tempo_Indicators_Clear(CDJ800_DATA_DISPLAY *display, uint8_t indicators);

void CDJ800_Display_Pitch_Set(CDJ800_DATA_DISPLAY *display , uint16_t value);
void CDJ800_Display_Pitch_DecimalPoint_Set(CDJ800_DATA_DISPLAY *display,uint8_t decimalPoint);
void CDJ800_Display_Pitch_DecimalPoint_Clear(CDJ800_DATA_DISPLAY *display,uint8_t decimalPoint);
void CDJ800_Display_Pitch_DecimalPoint_SwitchTo(CDJ800_DATA_DISPLAY *display,uint8_t decimalPoint);

//display header
void CDJ800_Display_Header_Indicators_Set(CDJ800_DATA_DISPLAY *display, uint8_t indicators);
void CDJ800_Display_Header_Track_Set(CDJ800_DATA_DISPLAY *display);
void CDJ800_Display_Header_Folder_Set(CDJ800_DATA_DISPLAY *display);
void CDJ800_Display_Header_AutoCue_Set(CDJ800_DATA_DISPLAY *display);
void CDJ800_Display_Header_Remain_Set(CDJ800_DATA_DISPLAY *display);
void CDJ800_Display_Header_Time_Set(CDJ800_DATA_DISPLAY *display);

void CDJ800_Display_Header_Indicators_Clear(CDJ800_DATA_DISPLAY *display, uint8_t indicators);
void CDJ800_Display_Header_Track_Clear(CDJ800_DATA_DISPLAY *display);
void CDJ800_Display_Header_Folder_Clear(CDJ800_DATA_DISPLAY *display);
void CDJ800_Display_Header_AutoCue_Clear(CDJ800_DATA_DISPLAY *display);
void CDJ800_Display_Header_Remain_Clear(CDJ800_DATA_DISPLAY *display);
void CDJ800_Display_Header_Time_Clear(CDJ800_DATA_DISPLAY *display);

//run in while
void CDJ800_Display_Update(CDJ800_DATA_DISPLAY *display);

//not for user
void CDJ800_Display_Segment_Set_Raw(CDJ800_DISPLAY_SEGMENT * segments,uint8_t segment,unsigned char character);
void CDJ800_Display_Track_Set_Raw(CDJ800_DISPLAY_SEGMENT * segments,uint8_t digit,uint8_t number);

void CDJ800_Display_Tempo_Show(CDJ800_DATA_DISPLAY *display);
void CDJ800_Display_Progress_Show(CDJ800_DATA_DISPLAY *display);
void CDJ800_Display_Segment_Show(CDJ800_DISPLAY_SEGMENT * segment,uint8_t seg);

void CDJ800_Display_Write(uint8_t data);
void CDJ800_Display_Latch();

#endif
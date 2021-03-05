#include "cdj800_display.h"
#include "ascii.h"

#define DISPLAY_FOLDER_TRACK1		(1<<0) //byte2
#define DISPLAY_TRACK2_SEGMENT1		(1<<1) //byte2
#define DISPLAY_SEGEMENT2_3			(1<<2) //byte2
#define DISPLAY_SEGEMENT4_5			(1<<3) //byte2
#define DISPLAY_SEGEMENT6_7			(1<<4) //byte2
#define DISPLAY_SEGEMENT8_9			(1<<5) //byte2
#define DISPLAY_TEMPO				(1<<6) | (1<<7) //byte2
#define DISPLAY_PROGRESS			(1<<6) | (1<<7) 


CDJ800_DATA_DISPLAY CDJ800_Display_Setup()
{
    CDJ800_DATA_DISPLAY display = {0};
	
	CDJ800_Display_Write_String(&display,0,"POWER ON");

    LATCH_DDR |=(1<<LATCH);
    BLANK_DDR |=(1<<BLANK);
    DATA_OUT_DDR |= (1<<DATA_OUT);
    CLK_DDR |= (1<<CLK);
    BLANK_PORT |= (1<<BLANK);
    LATCH_PORT &=~(1<<LATCH);
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<CPOL) | (1<<CPHA) | (1<<SPR1) | (1<<DORD);
    Time_Setup();
    while (Time_Get()<5000)
        CDJ800_Display_Update(&display);
    CDJ800_Display_Write_String(&display,0,"");
    CDJ800_Display_Tempo_Indicators_Set(&display,TEMPO_PROCENT | TEMPO_SQUARE );
    CDJ800_Display_Progress_Set(&display,0);
    return display;
}
void CDJ800_Display_Write_String(CDJ800_DATA_DISPLAY * display,uint8_t start,char * string)
{
    int i = start;
    while(*string != '\0' && i<9)
        CDJ800_Display_Write_Char(display,i++,*(string++));
    for(;i<9;i++)
        CDJ800_Display_Write_Char(display,i,' ');
}
inline void CDJ800_Display_Write_Char(CDJ800_DATA_DISPLAY * display,uint8_t segment,char character)
{
    segment+=3;
    CDJ800_Display_Segment_Set_Raw(&display->segments[segment/2],(segment)%2,character);
}
void CDJ800_Display_Track_Set(CDJ800_DATA_DISPLAY * display,uint16_t value)
{
    CDJ800_Display_Track_Set_Raw(&display->segments[1],TRACK_DIGIT1,value%10);
    value/=10;
    CDJ800_Display_Track_Set_Raw(&display->segments[0],TRACK_DIGIT2,value%10);
    value/=10;
    CDJ800_Display_Track_Set_Raw(&display->segments[0],TRACK_DIGIT3,value%10); 
}
void CDJ800_Display_Progress_Set(CDJ800_DATA_DISPLAY *display,int8_t progress)
{
    progress  = progress * 33 / 100;
    progress = 33 - progress;
    uint64_t data = ~((1ULL << (uint64_t)progress) - 1ULL);
    if(display->pogressBar.inverted)
        data = ~data;
    data<<=3UL;
    data |= 0b100;
    for(int i = 0;i<5;i++)
    {
        display->pogressBar.progress [i] =(data);
        data>>=8UL;
    }
}
inline void CDJ800_Display_Progress_Mode_Set(CDJ800_DATA_DISPLAY *display,int8_t inverted)
{
    display->pogressBar.inverted = inverted;
}

inline void CDJ800_Display_Cue_Set(CDJ800_DATA_DISPLAY *display,int8_t cue)
{
    display->pogressBar.cues[cue/8] |= (1<<(cue%8));
}

inline void CDJ800_Display_Cue_Clear(CDJ800_DATA_DISPLAY *display,int8_t cue)
{
    cue%=34;
    display->pogressBar.cues[cue/8] &= ~(1<<(cue%8));
}

void CDJ800_Display_Tempo_Set(CDJ800_DATA_DISPLAY *display , uint16_t value)
{
    int i  = 3;
    do
    {
        display->tempo.digits[i++] = digitLookUp[value%10];
        value /=10;  
    }while(value && i<6);
    for(;i<6;i++)
        display->tempo.digits[i] = digitLookUp[10]; //set to blank
}

inline void CDJ800_Display_Tempo_Indicators_Set(CDJ800_DATA_DISPLAY *display, uint8_t indicators)
{
    display->tempo.indicators |= indicators;
    display->tempo.digits[0] |= indicators & TEMPO_PROCENT;
}
inline void CDJ800_Display_Tempo_Indicators_Clear(CDJ800_DATA_DISPLAY *display, uint8_t indicators)
{
    display->tempo.indicators &= ~indicators;
    display->tempo.digits[0] &= ~(indicators & TEMPO_PROCENT);
}

void CDJ800_Display_Pitch_Set(CDJ800_DATA_DISPLAY *display , uint16_t value)
{
    for(int i = 0 ;i<3;i++)
    {
        display->tempo.digits[i] &= ~0xFE;
        display->tempo.digits[i] |= digitLookUp[value%10];
        value /=10;  
    }
}

inline void CDJ800_Display_Pitch_DecimalPoint_Set(CDJ800_DATA_DISPLAY *display,uint8_t decimalPoint)
{
    display->tempo.digits[decimalPoint] |= 0x01;
}
void CDJ800_Display_Pitch_DecimalPoint_Clear(CDJ800_DATA_DISPLAY *display,uint8_t decimalPoint)
{
    display->tempo.digits[decimalPoint%3] &= ~0x01;
}
inline void CDJ800_Display_Pitch_DecimalPoint_SwitchTo(CDJ800_DATA_DISPLAY *display,uint8_t decimalPoint)
{
    display->tempo.digits[3-decimalPoint] &= ~0x01;
    display->tempo.digits[decimalPoint] |= 0x01;
}

void CDJ800_Display_Header_Indicators_Set(CDJ800_DATA_DISPLAY *display, uint8_t indicators)
{
    if (indicators & DISPLAY_HEADER_TRACK)
        display->segments[0].data[0] |= 0x04;
    if (indicators & DISPLAY_HEADER_FOLDER)
        display->segments[0].data[0] |= 0x10;
    if (indicators & DISPLAY_HEADER_ACUE)
        display->segments[1].data[0] |= 0x02;
    if (indicators & DISPLAY_HEADER_REMAIN)
        display->segments[2].data[0] |= 0x02;
    if (indicators & DISPLAY_HEADER_TIME)
    {
        display->segments[3].data[0] |= 0x02;
        display->segments[4].data[0] |= 0x02;
        display->segments[5].data[0] |= 0x02;
    }
}

inline void CDJ800_Display_Header_Track_Set(CDJ800_DATA_DISPLAY *display)
{
    display->segments[0].data[0] |= 0x04;
}
inline void CDJ800_Display_Header_Folder_Set(CDJ800_DATA_DISPLAY *display)
{
    display->segments[0].data[0] |= 0x10;
}
inline void CDJ800_Display_Header_AutoCue_Set(CDJ800_DATA_DISPLAY *display)
{
    display->segments[1].data[0] |= 0x02;
}
inline void CDJ800_Display_Header_Remain_Set(CDJ800_DATA_DISPLAY *display)
{
    display->segments[2].data[0] |= 0x02;
}
        
inline void CDJ800_Display_Header_Time_Set(CDJ800_DATA_DISPLAY *display)
{
    display->segments[3].data[0] |= 0x02;
    display->segments[4].data[0] |= 0x02;
    display->segments[5].data[0] |= 0x02;
}
void CDJ800_Display_Header_Indicators_Clear(CDJ800_DATA_DISPLAY *display, uint8_t indicators)
{
    if (indicators & DISPLAY_HEADER_TRACK)
        display->segments[0].data[0] &=~ 0x04;
    if (indicators & DISPLAY_HEADER_FOLDER)
        display->segments[0].data[0] &=~ 0x10;
    if (indicators & DISPLAY_HEADER_ACUE)
        display->segments[1].data[0] &=~ 0x02;
    if (indicators & DISPLAY_HEADER_REMAIN)
        display->segments[2].data[0] &=~ 0x02;
    if (indicators & DISPLAY_HEADER_TIME)
    {
        display->segments[3].data[0] &=~ 0x02;
        display->segments[4].data[0] &=~ 0x02;
        display->segments[5].data[0] &=~ 0x02;
    }
}

inline void CDJ800_Display_Header_Track_Clear(CDJ800_DATA_DISPLAY *display)
{
    display->segments[0].data[0] &=~ 0x04;
}
inline void CDJ800_Display_Header_Folder_Clear(CDJ800_DATA_DISPLAY *display)
{
    display->segments[0].data[0] &=~ 0x10;
}
inline void CDJ800_Display_Header_AutoCue_Clear(CDJ800_DATA_DISPLAY *display)
{
    display->segments[1].data[0] &=~ 0x02;
}
inline void CDJ800_Display_Header_Remain_Clear(CDJ800_DATA_DISPLAY *display)
{
    display->segments[2].data[0] &=~ 0x02;
}          
inline void CDJ800_Display_Header_Time_Clear(CDJ800_DATA_DISPLAY *display)
{
    display->segments[3].data[0] &=~ 0x02;
    display->segments[4].data[0] &=~ 0x02;
    display->segments[5].data[0] &=~ 0x02;
}

void CDJ800_Display_Segment_Set_Raw(CDJ800_DISPLAY_SEGMENT * segments,uint8_t segment,unsigned char character)
{
    uint16_t data = 0;
    character -=8;
    int k = 0 ;
    uint8_t mask = 0x55<<segment;
    for(int j = 0;j<8;j++)
            data |= (ascii[character][0] & (1<<j)) << (j+segment); 
    segments->data[k] &= ~(mask & ~0x02);
    segments->data[k+1] &= ~(mask);
    segments->data[k++] |= data;
    segments->data[k++] |= data>>8; 
    for(int i = 1;i<5;i++)
    {
        data=0;
        for(int j = 0;j<8;j++)
            data |= (ascii[character][i] & (1<<j)) << (j+segment); 
        segments->data[k] &= ~(mask);
        segments->data[k+1] &= ~(mask);
        segments->data[k++] |= data;
        segments->data[k++] |= data>>8; 
    }
}
void CDJ800_Display_Track_Set_Raw(CDJ800_DISPLAY_SEGMENT * segments,uint8_t digit,uint8_t number)
{
    for(int i = 1;i<8;i++)
    {
        segments->data[i] &= ~(1<<digit);
        segments->data[i] |= (((digitLookUp[number]  & (1<<i)) >> i) << (digit));
    }
}

void CDJ800_Display_Tempo_Show(CDJ800_DATA_DISPLAY *display)
{
    for(int i =0;i<3;i++)
        CDJ800_Display_Write(display->tempo.digits[i]);
    CDJ800_Display_Write(display->tempo.indicators>>3);
    CDJ800_Display_Write(display->tempo.digits[3]);
    for(int i =4;i<6;i++)
        CDJ800_Display_Write(display->tempo.digits[i]);
    for(int i = 0;i<4;i++)
        CDJ800_Display_Write(0);
    CDJ800_Display_Write(DISPLAY_TEMPO);
    CDJ800_Display_Latch();
}

void CDJ800_Display_Progress_Show(CDJ800_DATA_DISPLAY *display)
{
    for(int i = 0;i<4;i++)
        CDJ800_Display_Write(display->pogressBar.cues[i]);
   
    CDJ800_Display_Write(display->pogressBar.progress[0] | display->pogressBar.cues[4]);

    for(int i = 1;i<5;i++)
        CDJ800_Display_Write(display->pogressBar.progress[i]);

    CDJ800_Display_Write(0x00);
    CDJ800_Display_Write(DISPLAY_PROGRESS);
    CDJ800_Display_Write(0);
    CDJ800_Display_Latch();
}

void CDJ800_Display_Segment_Show(CDJ800_DISPLAY_SEGMENT * segment,uint8_t seg)
{
    for(int i = 0;i<10;i++)
        CDJ800_Display_Write(segment->data[i]);
    CDJ800_Display_Write(0);
    CDJ800_Display_Write(seg);
    CDJ800_Display_Latch();
}

inline void CDJ800_Display_Write(uint8_t data)
{
	SPDR = data;
    while(!(SPSR & (1<<SPIF)));
}

inline void CDJ800_Display_Latch()
{
    LATCH_PORT |=(1<<LATCH);
	while(!(LATCH_PIN & (1<<LATCH)));
	LATCH_PORT &=~(1<<LATCH);
}

void CDJ800_Display_Update(CDJ800_DATA_DISPLAY *display)
{
    static uint32_t updateTime = 0;
    static uint8_t status = 0;
    if(Time_Get_U() - updateTime >= 500)
    {
        BLANK_PORT |= (1<<BLANK);
        if(status<6)
            CDJ800_Display_Segment_Show(&display->segments[status],(1<<(status)));
        else if (status == 6)
            CDJ800_Display_Progress_Show(display);
        else if (status == 7)
            CDJ800_Display_Tempo_Show(display);

        if(++status == 8)
            status = 0;
        updateTime = Time_Get_U();
        BLANK_PORT &= ~(1<<BLANK);
    }
}
#include "cdj800_jog_display.h"
#include <util/delay.h>

void CDJ800_Jog_Display_Setup()
{

    LATCH_DDR |=(1<<LATCH);
    BLANK_DDR |=(1<<BLANK);
    DATA_OUT_DDR |= (1<<DATA_OUT);
    CLK_DDR |= (1<<CLK);
    BLANK_PORT |= (1<<BLANK);
    LATCH_PORT &=~(1<<LATCH);
	SPCR = (1<<SPE) | (1<<MSTR) | (1<<CPOL) | (1<<CPHA) | (1<<SPR1) | (1<<DORD);
    
}

inline void CDJ800_Jog_Display_Write(uint8_t data)
{
	SPDR = data;
    while(!(SPSR & (1<<SPIF)));
}

inline void CDJ800_Jog_Display_Latch()
{
    LATCH_PORT |=(1<<LATCH);
	while(!(LATCH_PIN & (1<<LATCH)));
	LATCH_PORT &=~(1<<LATCH);
}
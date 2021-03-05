#ifndef __DMX_H__
#define __DMX_H__

#define F_CPU 16000000UL
#include <stdint.h>
#include "buffer.h"
#include <stdlib.h>
#include "uart.h"
#define DMX_START               0x00
#define DMX_READY               0
#define DMX_SENDING_BREAK       1
#define DMX_SENDING_MARK        2 // wait 12usec to maximum 1sec before calling DMX_Update again!
#define DMX_SENDING_DATA        3
#define DMX_SENDING_COMPLETE    4 // wait 1024usec to maximum 1sec before calling DMX_Update again!

typedef struct _dmx
{
    BUFFER * channels;
}DMX;

DMX* DMX_Setup();
void DMX_SetChannelValue(DMX * dmx,uint16_t channel,uint8_t value);
void DMX_Send(DMX * dmx);
void DMX_Start(DMX * dmx);

int DMX_Update(DMX * dmx);

void DMX_Destroy(DMX **dmx);
#endif
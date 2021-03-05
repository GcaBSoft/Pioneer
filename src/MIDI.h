#ifndef __MIDI_H__
#define __MIDI_H__
#include "uart.h"
#define MIDI_BANK_SELECT            0

#define MIDI_CH_MODE_RESET          121
#define MIDI_CH_MODE_LOCAL_ON       122
#define MIDI_CH_MODE_LOCAL_OFF      123
#define MIDI_CH_MODE_OMNI_ON        124
#define MIDI_CH_MODE_OMNI_OFF       125
#define MIDI_CH_MODE_MONO_MODE      126
#define MIDI_CH_MODE_POLY_MODE      127

#define MIDI_COM_MTC
#define MIDI_SONG_SELECT
#define MIDI_SONG_POS_PTR
#define MIDI_TUNE_REQ
#define MIDI_EOX

#define MIDI_SYNC
#define MIDI_START
#define MIDI_CONTINUE
#define MIDI_STOP
#define MIDI_ACTIVE_SENSE
#define MIDI_RESET
#define MIDI_TIMING_CLOCK


#define MIDI_NOTE_OFF               0x80
#define MIDI_NOTE_ON                0x90
#define MIDI_POLY_KEY_PRESSURE      0xA0
#define MIDI_CONTROL_CHANGE         0xB0 
#define MIDI_PROGRAM_CHANGE         0xC0
#define MIDI_CHANNEL_PRESSURE       0xD0
#define MIDI_PITCH_BEND             0xE0






typedef struct _midiPort
{
    uint8_t status;
}MIDI_PORT;

typedef struct _midi
{
    MIDI_PORT * in;
    MIDI_PORT * out;
    UART * uart;
    uint8_t channel;
}MIDI;

MIDI* MIDI_Setup(uint8_t channel);
uint8_t MIDI_Read(MIDI * midi,uint8_t * data,int * size,int MaxSize);
void MIDI_Send(MIDI * midi,uint8_t status,uint8_t command,uint8_t value);
void MIDI_Set_Channel(MIDI * midi,uint8_t channel);
void MIDI_Send_Note_On(MIDI * midi,uint8_t note,uint8_t velocity);
void MIDI_Send_Note_Off(MIDI * midi,uint8_t note,uint8_t velocity);
void MIDI_Send_CC(MIDI * midi,uint8_t controller,uint8_t value);
void MIDI_Send_Channel_Mode(MIDI * midi,uint8_t mode,uint8_t data);
void MIDI_Send_System_Common();
void MIDI_Send_System_Time(MIDI * midi,uint8_t type);
void MIDI_Send_Raw(MIDI * midi,uint8_t *data,int size);
uint8_t MIDI_Get_MessageSize(uint8_t status);
void MIDI_Clear_Out_Status(MIDI * midi);
void MIDI_Close(MIDI ** midi);



#endif
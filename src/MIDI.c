#include "MIDI.h"

MIDI* MIDI_Setup(uint8_t channel)
{
    MIDI * new = malloc(sizeof(MIDI));
    if(new)
    {
        new->in = malloc(sizeof(MIDI_PORT));
        new->out = malloc(sizeof(MIDI_PORT));
        new->uart = Uart_Setup("0",0,0,B115200,256,0);
        if(!(new->in && new->out && new->uart))
            MIDI_Close(&new);
        new->channel = channel;
    }
    return new;
}
uint8_t MIDI_Read(MIDI * midi,uint8_t * data,int * size,int MaxSize)
{
    uint8_t result = 0;
    *size=0;
    if(Uart_Get_Recv_BufferSize(midi->uart) > 2 && Uart_Read(midi->uart,&result,sizeof(uint8_t),1))
    {
        if(result > 0x7F)
            midi->in->status = result;
        else
        {
            data[(*size)++] = result;
            result = midi->in->status;
        }
        (*size)+= Uart_Read(midi->uart,data+*size,sizeof(uint8_t),MaxSize-*size);

    }
    return result;
}
void MIDI_Set_Channel(MIDI * midi,uint8_t channel);
void MIDI_Send_Note_On(MIDI * midi,uint8_t note,uint8_t velocity)
{
    MIDI_Send(midi,MIDI_NOTE_ON,note,velocity);
}
void MIDI_Send_Note_Off(MIDI * midi,uint8_t note,uint8_t velocity)
{
    MIDI_Send(midi,MIDI_NOTE_OFF,note,velocity);
}
void MIDI_Send_CC(MIDI * midi,uint8_t controller,uint8_t value)
{
    MIDI_Send(midi,MIDI_CONTROL_CHANGE,controller,value);
}
void MIDI_Send_Channel_Mode(MIDI * midi,uint8_t mode,uint8_t data);
void MIDI_Send_System_Common();
void MIDI_Send_System_Time(MIDI * midi,uint8_t type);
void MIDI_Send_Raw(MIDI * midi,uint8_t *data,int size);
void MIDI_Send(MIDI * midi,uint8_t status,uint8_t command,uint8_t value)
{
    if( 1 || (midi->out->status != ((status & 0xF0 ) | midi->channel)))
    {
        midi->out->status = ((status & 0xF0 ) | (midi->channel));
        Uart_Write(midi->uart,&midi->out->status,sizeof(uint8_t),1);
    }
    Uart_Write(midi->uart,&command,sizeof(uint8_t),1);
    Uart_Write(midi->uart,&value,sizeof(uint8_t),1);
}
void MIDI_Clear_Out_Status(MIDI * midi)
{
    midi->out->status = 0;
}
void MIDI_Close(MIDI ** midi)
{
    if(midi && *midi)
    {
        if((*midi)->in)
            free((*midi)->in);
        if((*midi)->out)
            free((*midi)->out);
        Uart_Close(&(*midi)->uart);
        free(*midi);
        *midi = NULL;
    }
}
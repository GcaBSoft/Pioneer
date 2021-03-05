#include "time.h"

#ifdef __AVR_ATmega328P__
#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint32_t _time = 0;
volatile uint8_t _state = 0;
volatile uint32_t _micro = 0;
ISR(TIMER2_COMPA_vect)
{
    _micro += 1000;
    _time++;
}
void Time_Setup()
{
    if(!_state)
    {
        sei();
        TCCR2A = (1<<WGM21);
        TIMSK2 |= (1<<OCIE2A);
        OCR2A = 250;
        TCNT2 = 0;
        Time_Start();
        _state = 1;
    } 
}
inline void Time_Start()
{
    TCCR2B = (1<<CS22);
}
inline uint32_t Time_Get()
{
    TIMSK2 &=~(1<<OCIE2A);
    uint32_t time = _time;
    TIMSK2 |= (1<<OCIE2A);
    return time;
}
inline uint32_t Time_Get_U()
{
    TIMSK2 &=~(1<<OCIE2A);
    uint32_t time = _micro + TCNT2/4;
    TIMSK2 |= (1<<OCIE2A);
    return time;
}
inline void Time_Set(uint32_t time)
{
    TIMSK2 &=~(1<<OCIE2A);
    _time = time;
    TIMSK2 |= (1<<OCIE2A);
}
inline void Time_Stop()
{
    _state = 0;
    TCCR2B =0;
}

#endif
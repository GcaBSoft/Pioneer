#include "led.h"

LED Led_Setup(volatile uint8_t *PORT,uint8_t number,uint16_t blinkTime,uint8_t state)
{
    Time_Setup();
    LED new = {0};
    new.port = PORT;
    new.number =number;
    if(PORT == &PORTB)
        new.ddr = &DDRB;
    else if(PORT == &PORTC)
        new.ddr = &DDRC;
    else if(PORT == &PORTD)
        new.ddr = &DDRD;
    new.blinkTime =blinkTime;
    *(new.ddr) |= (1<<new.number);
    Led_Set(&new,state);
    return new;    
}
inline void Led_Set(LED * led,uint8_t state)
{
    led->state = state;
    switch (state)
    {
        case LED_BLINK_STATE_ON:
            led->lastTime = Time_Get();
        case LED_STATE_ON:
            *(led->port) |= (1<<led->number);
            break;
        case LED_BLINK_STATE_OFF:
            led->lastTime = Time_Get();
        case LED_STATE_OFF:
            *(led->port) &= ~(1<<led->number);
            break;
    }
    
}
inline void Led_Update(LED * led)
{
    if(led->state>= LED_BLINK_STATE_ON &&  led->state<=LED_BLINK_STATE_OFF)
    {
        uint32_t time = Time_Get();
        if(time-led->lastTime>=led->blinkTime)
        {
            *(led->port) ^= (1<<led->number);
            led->state^=0x01;
            led->lastTime = time;
        }
    }
}
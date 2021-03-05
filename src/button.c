#include "button.h"
BUTTON Button_Setup(volatile uint8_t *PORT,uint8_t number,uint8_t id,uint8_t options)
{
    Time_Setup();
    BUTTON new = {0};
    new.port = PORT;
    new.number =number;
    new.id = id;
    if(PORT == &PORTB)
    {
        new.ddr = &DDRB;
        new.pin = &PINB;
    }
    else if(PORT == &PORTC)
    {
        new.ddr = &DDRC;
        new.pin = &PINC;
    }
    else if(PORT == &PORTD)
    {
        new.ddr = &DDRD;
        new.pin = &PIND;
    }
    Button_Set_PullUp(&new,options & BUTTON_ENABLE_PULL_UP);
    new.options = options & 0b11;
    return new;    
}
void Button_Set_PullUp(BUTTON * button,uint8_t onOff)
{
    if(onOff)
        *(button->port) |= (1<<button->number);
    else
        *(button->port) &= ~(1<<button->number); 
}
inline uint8_t Button_Get_State(BUTTON * button)
{
    if(button->options == BUTTON_NO_EDGE)
        return Button_Get_State_Raw(button);
    else
        return button->state;
}
void Button_Update(BUTTON * button)
{
    switch(button->options)
    {
        case BUTTON_ANY_EDGE:
            Button_Check_Any(button);
        break;
        case BUTTON_FALLING_EDGE:
            Button_Check_Falling(button);
        break;
        case BUTTON_RISING_EDGE:
            Button_Check_Rising(button);
        break;
    }
}

inline void Button_Check_Falling(BUTTON * button)
{
    Button_Check_Any(button);
    if(button->state== BUTTON_HIGH)
        button->state = BUTTON_NOCHANGE;
}
inline void Button_Check_Rising(BUTTON * button)
{
    Button_Check_Any(button);
    if(button->state== BUTTON_LOW)
        button->state = BUTTON_NOCHANGE;
}
inline void Button_Check_Any(BUTTON * button)
{
    uint8_t newState = *(button->pin) & (1<<button->number);
    button->state = BUTTON_NOCHANGE;
    if(newState != button->lastState)
    {
        uint32_t time = Time_Get();
        if(time - button->lastTime>DEBOUNCE)
        {
            if(newState)
                button->state =BUTTON_HIGH;
            else
                button->state =BUTTON_LOW;
        }
        button->lastTime = time;
    }
    button->lastState = newState;
    
}
inline uint8_t Button_Get_State_Raw(BUTTON * button)
{
    if(*(button->pin) & (1<<button->number))
        return BUTTON_HIGH;
    else
        return BUTTON_LOW;
    
}
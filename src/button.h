#ifndef __BUTTON_H__
#define __BUTTON_H__
#include <stdint.h>
#include "time.h"
#include <avr/io.h>
#define BUTTON_ANY_EDGE         0
#define BUTTON_RISING_EDGE      1
#define BUTTON_FALLING_EDGE     2
#define BUTTON_NO_EDGE          3
#define BUTTON_ENABLE_PULL_UP   0x04
#define BUTTON_NOCHANGE     0
#define BUTTON_LOW          1
#define BUTTON_HIGH         2
#ifndef DEBOUNCE 
#define DEBOUNCE    50
#endif
typedef struct _button{
    volatile uint8_t * ddr;
    volatile uint8_t * port;
    volatile uint8_t * pin;
    uint8_t  number;
    uint8_t options;
	uint32_t lastTime;
	uint8_t lastState;
	uint8_t state;
    uint8_t id;
    
}BUTTON;

BUTTON Button_Setup(volatile uint8_t *PORT,uint8_t number,uint8_t id,uint8_t options);
void Button_Set_PullUp(BUTTON * button,uint8_t onOff);
uint8_t Button_Get_State(BUTTON * button);
void Button_Update(BUTTON * button);

void Button_Check_Falling(BUTTON * button);
void Button_Check_Rising(BUTTON * button);
void Button_Check_Any(BUTTON * button);
uint8_t Button_Get_State_Raw(BUTTON * button);
#endif
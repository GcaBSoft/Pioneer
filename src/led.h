#ifndef __LED_H__
#define __LED_H__
#ifndef __AVR_ATmega328P__
#define	__AVR_ATmega328P__
#endif
#include "avr/io.h"
#include "time.h"

#define LED_STATE_ON          0
#define LED_STATE_OFF         1
#define LED_BLINK_STATE_ON    2
#define LED_BLINK_STATE_OFF   3



typedef struct _led
{
    volatile uint8_t * ddr;
    volatile uint8_t * port;
    uint8_t  number;
	uint32_t lastTime;
	uint8_t state;
    uint16_t blinkTime;
}LED;

LED Led_Setup(volatile uint8_t *PORT,uint8_t number,uint16_t blinkTime,uint8_t state);
void Led_Set(LED * led,uint8_t state);
void Led_Update(LED * led);
#endif
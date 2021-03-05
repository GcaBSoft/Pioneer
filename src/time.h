#ifndef __TIME_H__
#define __TIME_H__
#include <stdint.h>

#ifndef __AVR_ATmega328P__
#define	__AVR_ATmega328P__
#endif
void Time_Setup();
void Time_Start();
uint32_t Time_Get();
uint32_t Time_Get_U();
void Time_Set(uint32_t time);
void Time_Stop();
#endif
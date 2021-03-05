/*
 * Serial.h
 *
 * Created: 13/02/2020 10:16:18
 *  Author: r0637556
 */ 


#ifndef __UART_H__
#define __UART_H__

#define UART_ALLOW_BUFFER_OVERFLOW  0x01
#define UART_DISABLE_TX             0x02
#define UART_DISABLE_RX             0x03
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif
#ifdef __AVR_ATmega328P__
#ifndef NULL
#define NULL (void*)0
#endif
#include <avr/io.h>
#include "avr/interrupt.h"
#define F_CPU 16000000UL
#define CALCBAUD(a)  (F_CPU/(8UL*a)-1)
#define B50     CALCBAUD(50UL)
#define B75     CALCBAUD(75UL)    
#define B110    CALCBAUD(110UL)
#define B134    CALCBAUD(134UL)
#define B150    CALCBAUD(150UL)
#define B200    CALCBAUD(200UL)
#define B300    CALCBAUD(300UL)
#define B600    CALCBAUD(600UL)
#define B1200   CALCBAUD(1200UL)
#define B1800   CALCBAUD(1800UL)
#define B2400   CALCBAUD(2400UL)
#define B4800   CALCBAUD(4800UL)
#define B9600   CALCBAUD(9600UL)
#define B19200  CALCBAUD(19200UL)
#define B38400  CALCBAUD(38400UL)
#define B31250  CALCBAUD(31250UL)
#define B57600  CALCBAUD(57600UL)
#define B115200 CALCBAUD(115200UL)
#define B230400 CALCBAUD(230400UL)
#define B250000 CALCBAUD(250000UL)

#endif
#ifdef __linux__
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h> 
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#endif
#include "buffer.h"
typedef struct _uart
{
    int fd;
    BUFFER *bufferRecv;
    BUFFER *bufferSend;
}UART;
UART* Uart_Setup(char * device,BUFFER * send,BUFFER * recv, unsigned int baudrate,int bufferSize,int options);

void Uart_SetBaudRate(UART *uart,unsigned int baud);

int Uart_Enum(char *data, int arrayMaxLen, int stringMaxLength);

void Uart_Receive(UART *uart);

void Uart_Send(UART *uart);

int Uart_Read(UART *uart,void * dest,uintptr_t typeSize,uintptr_t arrayMaxSize);
int Uart_Write(UART *uart,void * data,uintptr_t typeSize,uintptr_t size);
unsigned int Uart_Get_Recv_BufferSize(UART *uart);
unsigned int Uart_Get_Send_BufferSize(UART *uart);
void Uart_Close(UART **uart);

#endif /* SERIAL_H_ */

#include "uart.h"

#ifdef __AVR_ATmega328P__
volatile UART devices[1] = {0};

ISR(USART_RX_vect)
{
	Buffer_Add(devices[0].bufferRecv,(uint8_t*)&UDR0,sizeof(uint8_t));
}
ISR(USART_TX_vect)
{
	if(Buffer_GetSize(devices[0].bufferSend))
	{
		if(!(UCSR0A & (1<<UDRE0)))
			Buffer_Read(devices[0].bufferSend,(uint8_t*)&UDR0,sizeof(uint8_t));
		else
			UCSR0B |= (1<<UDRIE0);
	}
}
ISR(USART_UDRE_vect)
{
	if(Buffer_GetSize(devices[0].bufferSend))
		Buffer_Read(devices[0].bufferSend,(uint8_t*)&UDR0,sizeof(uint8_t));
	UCSR0B &= ~(1<<UDRIE0);
}


UART* Uart_Setup(char * device,BUFFER * send,BUFFER * recv, unsigned int baudrate,int bufferSize,int options)
{
	
	if(device == NULL || device[0]>'0' || device[0]<'0')
		return NULL;
	int fd =  device[0]-'0';
	if(devices[fd].bufferSend || devices[fd].bufferRecv)
		return NULL; //device already open
	UART * new = malloc(sizeof(UART));
	if(new)
	{
		new->fd = fd;
		if(!send)
			send = Buffer_Create(bufferSize,sizeof(unsigned char),options & 0x01);
		if(!recv)
			recv = Buffer_Create(bufferSize,sizeof(unsigned char),options & 0x01);
		new->bufferSend = send;
		new->bufferRecv = recv;	
		devices[new->fd].bufferRecv = new->bufferRecv;
		devices[new->fd].bufferSend = new->bufferSend;
		if(!new->bufferRecv || !new->bufferSend)
			Uart_Close(&new);
	}
	if(new)
	{
		sei();
		UCSR0B = 0;
		Uart_SetBaudRate(new,baudrate);
		if(!(options & UART_DISABLE_RX))
			UCSR0B |=  (1<<RXCIE0) | (1<<RXEN0);
		if(!(options & UART_DISABLE_TX))	
			UCSR0B |=  (1<<TXCIE0)  | (1<<TXEN0);
	}	
	return new;
}

void Uart_SetBaudRate(__attribute__ ((unused))UART * uart,unsigned int baud)
{
	if(baud > 4095)
	{
		baud /=2;
		UCSR0A &=~(1<<U2X0);
		if(baud >4095)
			return;
	}
	else
		UCSR0A |= (1<<U2X0);
	
	UBRR0L = baud & 0x00FF;
	UBRR0H =  (baud >> 8);
}

int Uart_Enum(char *data, int arrayMaxLen, int stringMaxLength)
{
	if(data && arrayMaxLen && stringMaxLength>0)
		data[0] = '\0';
	return 1;
}


void Uart_Receive(__attribute__ ((unused))UART *uart)
{
	return; 
}


void Uart_Send(__attribute__ ((unused))UART *uart)
{	
	UCSR0B |= (1<<UDRIE0);
}
int Uart_Read(UART *uart,void * dest,uintptr_t typeSize,uintptr_t arrayMaxSize)
{
	return Buffer_ReadArray(uart->bufferRecv,dest,typeSize,arrayMaxSize);
}
int Uart_Write(UART *uart,void * data,uintptr_t typeSize,uintptr_t size)
{
	int result = Buffer_AddArray(uart->bufferSend,data,typeSize,size);
	if(!result)
		Uart_Send(uart);
	return result;
}
unsigned int Uart_Get_Recv_BufferSize(UART *uart)
{
	return Buffer_GetSize(uart->bufferRecv);
}
unsigned int Uart_Get_Send_BufferSize(UART *uart)
{
	return Buffer_GetSize(uart->bufferSend);
}
void Uart_Close(UART ** uart)
{
	if(uart && *uart)
	{
		Buffer_Destroy(&(*uart)->bufferRecv);
		Buffer_Destroy(&(*uart)->bufferSend);
		devices[(*uart)->fd].bufferRecv = NULL;
		devices[(*uart)->fd].bufferSend = NULL;
		free(*uart);
		*uart =NULL;
		UCSR0B = 0;
	}
}

#endif

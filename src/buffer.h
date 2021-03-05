#ifndef __BUFFER_H__
#define __BUFFER_H__

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#define BUFFER_NO_OPTIONS       0
#define BUFFER_ALLOW_OVERFLOW   0x01 // warning: enabling Overflow could cause buffer corruption when Buffer_Add() or Buffer_AddArray() is interupted;
#define BUFFER_FULL             -1
#define BUFFER_EMPTY            -2
#define BUFFER_OVERFLOW         1

typedef struct BUFFER
{
    void *buffer;
    uintptr_t typeSize;
    void * end;
    void *head;
    void *tail;
    unsigned int options; 
} BUFFER;


BUFFER * Buffer_Create(uintptr_t size,uintptr_t typeSize,unsigned int options);

void Buffer_Destroy(BUFFER ** buffer);
uintptr_t Buffer_GetSpace(BUFFER * buffer);
int Buffer_Add(BUFFER * buffer,void * data,uintptr_t typeSize);
int Buffer_Peek(BUFFER * buffer,void * dest,uintptr_t typeSize);
uintptr_t Buffer_GetBufferSize(BUFFER * buffer);

int Buffer_Read(BUFFER * buffer,void * dest,uintptr_t typeSize);
int Buffer_IsEmpty(BUFFER * buffer);
uintptr_t Buffer_GetSize(BUFFER * buffer);
void Buffer_Clear(BUFFER * buffer);
int Buffer_AddArray(BUFFER * buffer,void * data,uintptr_t typeSize,uintptr_t size);
uintptr_t Buffer_ReadArray(BUFFER * buffer,void * dest,uintptr_t typeSize,uintptr_t arrayMaxSize);
void Buffer_Reset_To_Start(BUFFER * buffer);
void Buffer_SetSize(BUFFER * buffer,uintptr_t size);
void Buffer_SetValueRaw(BUFFER * buffer,void * data,uintptr_t typeSize,uintptr_t position);
#endif
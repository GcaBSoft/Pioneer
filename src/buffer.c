#include "buffer.h"

BUFFER * Buffer_Create(uintptr_t size,uintptr_t typeSize,unsigned int options)
{
	BUFFER * new = (BUFFER *)malloc(sizeof(BUFFER));
	if(new == NULL)
		return new;

	new->buffer = calloc(size+1,typeSize);
	if(new->buffer == NULL)
		Buffer_Destroy(&new);
	else
	{
		new->head = new->buffer;
		new->tail = new->buffer;
		new->end = new->buffer+(size+1)*typeSize;
		new->typeSize = typeSize;
		new->options = options;
	}
	return new;
}

int Buffer_Add(BUFFER * buffer,void * data,uintptr_t typeSize)
{
	void * tempHead = buffer->head;
	void * tempTail = buffer->tail;
	int result = 0;
	if(typeSize>buffer->typeSize)
		typeSize = buffer->typeSize;

	tempTail += typeSize;
	
	if((tempTail) >= buffer->end)
		tempTail = buffer->buffer;

	if(tempTail == tempHead)
	{
		if((buffer->options & BUFFER_ALLOW_OVERFLOW))
		{
			tempHead += typeSize;
			if(tempHead >= buffer->end)
				tempHead = buffer->buffer;
			if(buffer->head == tempTail)
				buffer->head = tempHead;
			result = BUFFER_OVERFLOW;
		}
		else
			return BUFFER_FULL;	
	}
	if(buffer->typeSize>typeSize)
	{
		memset(tempTail,0,buffer->typeSize);
		memcpy(tempTail+(buffer->typeSize - typeSize),data,typeSize);
	}	
	else
		memcpy(tempTail,data,typeSize);
	
	buffer->tail = tempTail;
	return result;
}

uintptr_t Buffer_GetBufferSize(BUFFER * buffer)
{
	return ((buffer->end - buffer->buffer) / buffer->typeSize)-1;
}
uintptr_t Buffer_GetSpace(BUFFER * buffer)
{
	return Buffer_GetBufferSize(buffer) -Buffer_GetSize(buffer);
}
int Buffer_Read(BUFFER * buffer,void * dest,uintptr_t typeSize)
{
	if(buffer->tail != buffer->head)
	{
		buffer->head +=  buffer->typeSize;
		if(buffer->head>= buffer->end)
			buffer->head = buffer->buffer;
		if(buffer->typeSize >= typeSize)
			memcpy(dest,buffer->head + buffer->typeSize - typeSize, typeSize);
		else
		{
			memset(dest,0,typeSize);
			memcpy(dest,buffer->head,buffer->typeSize);
		}	
		return 0;
	}
	return BUFFER_EMPTY;
}
int Buffer_AddArray(BUFFER * buffer,void * data,uintptr_t typeSize,uintptr_t size)
{
	int temp = 0;
	int result = 0;
	if(!(buffer->options & BUFFER_ALLOW_OVERFLOW) && Buffer_GetSpace(buffer)<size)
		return BUFFER_FULL;
	for(size_t i = 0;i<size;i++)
	{
		temp  = Buffer_Add(buffer,data+i*typeSize,typeSize);
		if(temp<0)
			return temp;
		else if(temp>0)
			result = temp;
	}
	return result;
}
uintptr_t Buffer_ReadArray(BUFFER * buffer,void * dest,uintptr_t typeSize,uintptr_t arrayMaxSize)
{
	size_t i =0;
	while(i<arrayMaxSize && !Buffer_Read(buffer,dest+typeSize*i,typeSize))
		i++;
	return i;
}
void Buffer_Clear(BUFFER * buffer)
{
	buffer->head = buffer->tail;
}
int Buffer_IsEmpty(BUFFER * buffer)
{
	return (buffer->head == buffer->tail);
}
uintptr_t Buffer_GetSize(BUFFER * buffer)
{
	intptr_t result  = buffer->tail - buffer->head;
	if(buffer->tail < buffer->head)
		result +=(buffer->end - buffer->buffer) + 1;
	return (result/buffer->typeSize);
}
//sets the bufferPosition to the start of the buffer // Only use when values have been set Using Buffer_SetValueRaw()
void Buffer_Reset_To_Start(BUFFER * buffer)
{
	buffer->head = buffer->buffer;
}
//sets the amount of items in the buffer //only use after calling Buffer_Reset_To_Start();
void Buffer_SetSize(BUFFER * buffer,uintptr_t size)
{
	if(size>Buffer_GetBufferSize(buffer))
		return;
	void *temp = buffer->tail;
	temp = buffer->head + size*buffer->typeSize;
	if(temp>=buffer->end)
		temp = buffer->buffer + (temp - buffer->typeSize - buffer->end);
	buffer->tail =temp;
}
void Buffer_SetValueRaw(BUFFER * buffer,void * data,uintptr_t typeSize,uintptr_t position)
{
	if(typeSize>buffer->typeSize)
		typeSize = buffer->typeSize;
	
	memcpy(buffer->buffer+(position+2)*buffer->typeSize - typeSize,data,typeSize);
}
void Buffer_Destroy(BUFFER ** buffer)
{
	if(buffer && *buffer)
	{
		if((*buffer)->buffer)
		{
			free((*buffer)->buffer);
			(*buffer)->buffer = NULL;
		}	
		free(*buffer);
		*buffer=NULL;
	}
}

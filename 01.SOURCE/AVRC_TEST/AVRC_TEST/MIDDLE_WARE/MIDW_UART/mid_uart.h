#ifndef MID_UART_H_
#define MID_UART_H_

#include "stdint.h"
#include "stdbool.h"

#define MID_UART_BUFFER_SIZE    32U

typedef struct
{
	char buffer[MID_UART_BUFFER_SIZE];
	uint8_t in;
	uint8_t out;
	uint8_t count;
} MID_UART_RingBuffer_t;

void Mid_UART_Init(void);
void Mid_UART_Update(void);

void Mid_UART_SendChar(char data);
void Mid_UART_SendString(const char *data);
void Mid_UART_SendArray(const char *data, uint8_t length);

uint8_t Mid_UART_GetRxCount(void);
uint16_t Mid_UART_ReadChar(void);

void Mid_UART_Printf(const char *format, ...);

void Mid_UART_Close(void);

void Mid_UART_RingBuffer_Init(MID_UART_RingBuffer_t *rb);
uint8_t Mid_UART_RingBuffer_Count(MID_UART_RingBuffer_t *rb);
bool Mid_UART_RingBuffer_Full(MID_UART_RingBuffer_t *rb);
bool Mid_UART_RingBuffer_Empty(MID_UART_RingBuffer_t *rb);
void Mid_UART_RingBuffer_Insert(MID_UART_RingBuffer_t *rb, char data);
char Mid_UART_RingBuffer_Remove(MID_UART_RingBuffer_t *rb);

#endif
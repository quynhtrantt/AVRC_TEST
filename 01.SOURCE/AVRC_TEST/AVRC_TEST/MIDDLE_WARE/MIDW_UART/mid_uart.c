#include "mid_uart.h"
#include "avr/io.h"

static MID_UART_RingBuffer_t rx_buffer;
static MID_UART_RingBuffer_t tx_buffer;

void Mid_UART_RingBuffer_Init(MID_UART_RingBuffer_t *rb)
{
	if (rb == 0)
	{
		return;
	}

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		rb->in = 0U;
		rb->out = 0U;
		rb->count = 0U;
	}
}

uint8_t Mid_UART_RingBuffer_Count(MID_UART_RingBuffer_t *rb)
{
	if (rb == 0)
	{
		return 0U;
	}

	return rb->count;
}

bool Mid_UART_RingBuffer_Full(MID_UART_RingBuffer_t *rb)
{
	if (rb == 0)
	{
		return false;
	}

	return (rb->count >= MID_UART_BUFFER_SIZE);
}

bool Mid_UART_RingBuffer_Empty(MID_UART_RingBuffer_t *rb)
{
	if (rb == 0)
	{
		return true;
	}

	return (rb->count == 0U);
}

void Mid_UART_RingBuffer_Insert(MID_UART_RingBuffer_t *rb, char data)
{
	if (rb == 0)
	{
		return;
	}

	if (Mid_UART_RingBuffer_Full(rb))
	{
		return;
	}

	rb->buffer[rb->in] = data;

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		rb->in++;

		if (rb->in >= MID_UART_BUFFER_SIZE)
		{
			rb->in = 0U;
		}

		rb->count++;
	}
}

char Mid_UART_RingBuffer_Remove(MID_UART_RingBuffer_t *rb)
{
	char data;

	if (rb == 0)
	{
		return 0;
	}

	if (Mid_UART_RingBuffer_Empty(rb))
	{
		return 0;
	}

	data = rb->buffer[rb->out];

	ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
	{
		rb->out++;

		if (rb->out >= MID_UART_BUFFER_SIZE)
		{
			rb->out = 0U;
		}

		rb->count--;
	}

	return data;
}

void Mid_UART_Init(void)
{
	Mid_UART_RingBuffer_Init(&rx_buffer);
	Mid_UART_RingBuffer_Init(&tx_buffer);

	BSP_UART_Init();
}

void Mid_UART_Update(void)
{
	uint16_t data;

	while (BSP_UART_GetRxCount() > 0U)
	{
		data = BSP_UART_ReadChar();

		if ((data & 0x0100U) == 0U)
		{
			Mid_UART_RingBuffer_Insert(&rx_buffer, (char)data);
		}
	}

	while (!Mid_UART_RingBuffer_Empty(&tx_buffer))
	{
		BSP_UART_SendChar(
		Mid_UART_RingBuffer_Remove(&tx_buffer)
		);
	}
}

void Mid_UART_SendChar(char data)
{
	Mid_UART_RingBuffer_Insert(&tx_buffer, data);
}

void Mid_UART_SendString(const char *data)
{
	if (data == 0)
	{
		return;
	}

	while (*data != '\0')
	{
		Mid_UART_RingBuffer_Insert(&tx_buffer, *data);
		data++;
	}
}

void Mid_UART_SendArray(const char *data, uint8_t length)
{
	uint8_t i;

	if (data == 0)
	{
		return;
	}

	for (i = 0U; i < length; i++)
	{
		Mid_UART_RingBuffer_Insert(&tx_buffer, data[i]);
	}
}

uint8_t Mid_UART_GetRxCount(void)
{
	return Mid_UART_RingBuffer_Count(&rx_buffer);
}

uint16_t Mid_UART_ReadChar(void)
{
	if (Mid_UART_RingBuffer_Empty(&rx_buffer))
	{
		return 0x0100U;
	}

	return (uint8_t)Mid_UART_RingBuffer_Remove(&rx_buffer);
}

void Mid_UART_Printf(const char *format, ...)
{
	va_list args;

	if (format == 0)
	{
		return;
	}

	va_start(args, format);

	BSP_UART_vprintf(format, args);

	va_end(args);
}

void Mid_UART_Close(void)
{
	BSP_UART_Close();
}
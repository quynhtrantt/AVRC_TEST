#include "fifo.h"

void fifo_init(fifo_t *fifo, uint8_t *buffer_memory, uint16_t size)
{
	fifo->buffer = buffer_memory;
	fifo->size = size;
	fifo->rd = 0U;
	fifo->wr = 0U;
	fifo->count = 0U;
}

bool fifo_empty(fifo_t *fifo)
{
	return (fifo->count == 0U);
}

bool fifo_full(fifo_t *fifo)
{
	return (fifo->count == fifo->size);
}

bool fifo_push(fifo_t *fifo, uint8_t data)
{
	if (fifo_full(fifo))
	{
		return false;
	}

	fifo->buffer[fifo->wr] = data;

	fifo->wr++;

	if (fifo->wr >= fifo->size)
	{
		fifo->wr = 0U;
	}

	fifo->count++;

	return true;
}

bool fifo_get(fifo_t *fifo, uint8_t *data)
{
	if (fifo_empty(fifo))
	{
		return false;
	}

	*data = fifo->buffer[fifo->rd];

	fifo->rd++;

	if (fifo->rd >= fifo->size)
	{
		fifo->rd = 0U;
	}

	fifo->count--;

	return true;
}
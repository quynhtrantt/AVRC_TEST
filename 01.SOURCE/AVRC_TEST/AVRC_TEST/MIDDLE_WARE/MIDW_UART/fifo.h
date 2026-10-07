#ifndef FIFO_H_
#define FIFO_H_

#include "stdbool.h"
#include "stdint.h"


typedef enum fifo_t
{
	uint8_t *buffer;
	uint16_t size;
	uint16_t rd;
	uint16_t wr;
	uint16_t count;

};


void fifo_init(fifo_t *fifo, uint8_t *buffer_memory, uint16_t size);
bool fifo_empty(fifo_t *fifo);
bool fifo_full(fifo_t *fifo);
bool fifo_push(fifo_t *fifo, uint8_t data);
bool fifo_get(fifo_t *fifo, uint8_t *data);

#endif

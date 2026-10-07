#include "UART.h"
#include "fifo.h"
#include "UART_CONFIG.h"

#include "avr/io.h"
#include "avr/interrupt.h"

static uint8_t uart_rx_buffer[UART_RX_BUFFER_SIZE];
static uint8_t uart_tx_buffer[UART_TX_BUFFER_SIZE];

static fifo_t uart_rx_fifo;
static fifo_t uart_tx_fifo;
void usart1_init(void)
{
	fifo_init(&uart_rx_fifo,
	uart_rx_buffer,
	UART_RX_BUFFER_SIZE);

	fifo_init(&uart_tx_fifo,
	uart_tx_buffer,
	UART_TX_BUFFER_SIZE);

	UCSR1A = (1 << U2X1);

	UCSR1B = (1 << RXEN1) |
	(1 << TXEN1) |
	(1 << RXCIE1);

	UCSR1C = (1 << UCSZ11) |
	(1 << UCSZ10);

	UBRR1H = (uint8_t)(UART_UBRR_VALUE >> 8);
	UBRR1L = (uint8_t)UART_UBRR_VALUE;
}
void usart1_send_char(char data)
{
	if (fifo_push(&uart_tx_fifo, (uint8_t)data))
	{

		UCSR1B |= (1 << UDRIE1);
	}
}

void usart1_send_string(const char *str)
{
	if (str == 0)
	{
		return;
	}

	while (*str != '\0')
	{
		usart1_send_char(*str);
		str++;
	}
}

void usart1_send_array(const char *str, uint8_t len)
{
	uint8_t i;

	if (str == 0)
	{
		return;
	}

	for (i = 0U; i < len; i++)
	{
		usart1_send_char(str[i]);
	}
}

uint8_t usart1_rx_count(void)
{
	return (uint8_t)uart_rx_fifo.count;
}

uint16_t usart1_read_char(void)
{
	uint8_t data;

	if (fifo_get(&uart_rx_fifo, &data))
	{
		return (uint16_t)data;
	}

	return 0x0100U;
}

void usart1_close(void)
{
	UCSR1B &= ~((1 << RXEN1) |
	(1 << TXEN1) |
	(1 << RXCIE1) |
	(1 << UDRIE1));
}

ISR(USART1_RX_vect)
{
	uint8_t data;

	data = UDR1;

	fifo_push(&uart_rx_fifo, data);
}

ISR(USART1_UDRE_vect)
{
	uint8_t data;

	if (fifo_get(&uart_tx_fifo, &data))
	{
		UDR1 = data;
	}
	else
	{
		UCSR1B &= ~(1 << UDRIE1);
	}
}
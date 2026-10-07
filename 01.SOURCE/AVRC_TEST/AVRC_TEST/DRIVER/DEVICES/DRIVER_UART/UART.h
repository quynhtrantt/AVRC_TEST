#ifndef UART_H_
#define UART_H_

#include "stdint.h"

void usart1_init(void);

void usart1_send_char(char data);
void usart1_send_string(const char *str);
void usart1_send_array(const char *str, uint8_t len);

uint8_t usart1_rx_count(void);
uint16_t usart1_read_char(void);

void usart1_close(void);

#endif
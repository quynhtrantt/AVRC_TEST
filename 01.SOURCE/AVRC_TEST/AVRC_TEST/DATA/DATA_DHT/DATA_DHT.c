/*
 * DATA_DHT.c
 *
 * Created: 9/19/2026 1:13:22 PM
 *  Author: HP
 */ 
#include "DATA_DHT.h"
#include "BOARD.h"

volatile uint8_t temperature = 0;
volatile uint8_t humidity = 0;

void data_dht_set_temperature(uint8_t value)
{
	temperature = value;
}

uint8_t data_dht_get_temperature(void)
{
	return temperature;
}

void data_dht_set_humidity(uint8_t value)
{
	humidity = value;
}

uint8_t data_dht_get_humidity(void)
{
	return humidity;
}
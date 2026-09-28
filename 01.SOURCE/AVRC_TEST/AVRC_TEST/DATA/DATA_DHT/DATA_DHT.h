/*
 * DATA_DHT.h
 *
 * Created: 9/19/2026 1:13:37 PM
 *  Author: HP
 */ 


#ifndef DATA_DHT_H_
#define DATA_DHT_H_

#include <stdint.h>

void data_dht_set_temperature(uint8_t temperature);
uint8_t data_dht_get_temperature(void);

void data_dht_set_humidity(uint8_t humidity);
uint8_t data_dht_get_humidity(void);

#endif /* DATA_DHT_H_ */
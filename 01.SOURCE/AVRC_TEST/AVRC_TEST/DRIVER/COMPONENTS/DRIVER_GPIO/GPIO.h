#ifndef GPIO_H_
#define GPIO_H_
#include "stdint.h"
#include "avr/io.h"

#define NUM_OF_PORTS           4
#define NUM_OF_PINS_PER_PORT   8

#define PORTA_ID               0
#define PORTB_ID               1
#define PORTC_ID               2
#define PORTD_ID               3

#define PIN0_ID                0
#define PIN1_ID                1
#define PIN2_ID                2
#define PIN3_ID                3
#define PIN4_ID                4
#define PIN5_ID                5
#define PIN6_ID                6
#define PIN7_ID                7

#define LOGIC_HIGH 1
#define LOGIC_LOW 0

#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

#define BIT_IS_SET(REG,BIT) ( REG & (1<<BIT) )

typedef enum
{
	PIN_INPUT,PIN_OUTPUT
}GPIO_PinDirectionType;

typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF
}GPIO_PortDirectionType;

void GPIO_setupPinDirection(uint8_t port_num, uint8_t pin_num, GPIO_PinDirectionType direction);

void GPIO_writePin(uint8_t port_num, uint8_t pin_num, uint8_t value);

uint8_t GPIO_readPin(uint8_t port_num, uint8_t pin_num);

void GPIO_setupPortDirection(uint8_t port_num, uint8_t direction);

void GPIO_writePort(uint8_t port_num, uint8_t value);

uint8_t GPIO_readPort(uint8_t port_num);

#endif 


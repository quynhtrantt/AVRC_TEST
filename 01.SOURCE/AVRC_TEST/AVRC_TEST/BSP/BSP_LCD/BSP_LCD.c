#define F_CPU 8000000UL
#include "avr/io.h"
#include "BSP_LCD.h"
#include "stdint.h"
#include "util/delay.h"

#define LCD_PORT PORTA
#define LCD_DDR DDRA
#define LCD_RS  PA0
#define LCD_EN  PA1
#define LCD_D4  PA4
#define LCD_D5  PA5
#define LCD_D6  PA6
#define LCD_D7  PA7

	
void BSP_LCD_Init(void) {

	LCD_DDR |= (1 << LCD_RS) | (1 << LCD_EN) |
	(1 << LCD_D4) | (1 << LCD_D5) |
	(1 << LCD_D6) | (1 << LCD_D7);

	LCD_Init();

}

void LCD_WriteBus4(uint8_t nibble)
{
	LCD_PORT = (LCD_PORT & 0x0F) | ((nibble & 0x0F) << 4);
}


void LCD_RS_HIGH(void)
{
	LCD_PORT |= (1 << LCD_RS);
}

void LCD_RS_LOW(void)
{
	LCD_PORT &= ~(1 << LCD_RS);
}

void LCD_EN_HIGH(void)
{
	LCD_PORT |= (1 << LCD_EN);
}

void LCD_EN_LOW(void)
{
	LCD_PORT &= ~(1 << LCD_EN);
}

void LCD_DelayMs(uint32_t ms)
{
	while (ms--)
	{
		_delay_ms(1);
	}
}

void LCD_DelayUs(uint32_t us)
{
	while (us--)
	{
		_delay_us(1);
	}
}
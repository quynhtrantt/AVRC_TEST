#ifndef BSP_LCD_H_
#define BSP_LCD_H_
#include "LCD.h"

#define F_CPU 8000000UL

void LCD_RS_HIGH(void);
void LCD_RS_LOW(void);
void LCD_EN_HIGH(void);
void LCD_EN_LOW(void);

void BSP_LCD_Init(void);
void LCD_WriteBus4(uint8_t nibble);

#endif 
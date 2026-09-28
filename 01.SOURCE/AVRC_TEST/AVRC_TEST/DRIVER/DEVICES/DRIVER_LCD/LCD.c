#define F_CPU 8000000UL
#include "LCD.h"
#include "stdint.h"

#ifndef LCD_WEAK
#define LCD_WEAK __attribute__((weak))
#endif

LCD_WEAK void LCD_DelayMs(uint32_t ms)
{
	while (ms--) {
		LCD_DelayMs(1000);
	}
}

LCD_WEAK void LCD_DelayUs(uint32_t us)
{
	while (us--) {
		for (uint8_t i = 100; i>0; i--);
	}
}

LCD_WEAK void LCD_RS_HIGH(void) { (void)0; }
LCD_WEAK void LCD_RS_LOW(void)  { (void)0; }
LCD_WEAK void LCD_EN_HIGH(void) { (void)0; }
LCD_WEAK void LCD_EN_LOW(void)  { (void)0; }
	
void LCD_PulseEnable(void)
{
    LCD_EN_HIGH();	
    LCD_DelayUs(1);      
    LCD_EN_LOW();
    LCD_DelayUs(50);     
}

void LCD_Write4Bits(uint8_t nibble)
{
	LCD_WriteBus4(nibble & 0x0F);
	LCD_PulseEnable();
}

void LCD_Send(uint8_t value, uint8_t isData)
{
    if (isData) {
        LCD_RS_HIGH();
    } else {
        LCD_RS_LOW();
    }

    LCD_Write4Bits(value >> 4);

    LCD_Write4Bits(value & 0x0F);


    if (!isData && (value == 0x01u || value == 0x02u)) {

        LCD_DelayMs(2);
    }
}

void LCD_SendCommand(uint8_t cmd)
{
    LCD_Send(cmd, 0u);
}

void LCD_SendData(uint8_t data)
{
    LCD_Send(data, 1u);
}

void LCD_Init(void)
{
 
    LCD_DelayMs(40);

    LCD_RS_LOW();
    LCD_EN_LOW();

    LCD_Write4Bits(0x03u);
    LCD_DelayMs(5);

    LCD_Write4Bits(0x03u);
    LCD_DelayUs(150);

    LCD_Write4Bits(0x03u);
    LCD_DelayUs(150);

//4 bit mode
    LCD_Write4Bits(0x02u);
    LCD_DelayUs(150);

    /* Function Set: 4-bit, 2 dòng, font 5x8
       0x28 = 0b0010 1000
    */
    LCD_SendCommand(0x28u);

    /* Display OFF: t?t hi?n th?, t?t cursor, t?t blink */
    LCD_SendCommand(0x08u);

    /* Clear display */
    LCD_Clear();

    /* Entry Mode Set: t?ng ??a ch? DDRAM, không d?ch màn hình
       0x06 = 0b0000 0110
    */
    LCD_SendCommand(0x06u);

    /* Display ON: b?t hi?n th?, t?t cursor, t?t blink
       0x0C = 0b0000 1100
    */
    LCD_SendCommand(0x0Cu);
}

/* Xóa màn hình LCD */
void LCD_Clear(void)
{
    LCD_SendCommand(0x01u);   /* Clear display */
}

/* ??a con tr? v? v? trí home (0,0) */
void LCD_Home(void)
{
     LCD_SendCommand(0x02u);   /* Return home */
}

/* Ghi 1 ký t? lên v? trí hi?n t?i c?a con tr? */
void LCD_PutChar(char c)
{
    LCD_SendData((uint8_t)c);
}

/* Ghi chu?i null-terminated */
void LCD_PutString(const char *s)
{
    if (s == 0) return;

    while (*s != '\0') {
        LCD_PutChar(*s++);
    }
}

void LCD_GotoXY(uint8_t col, uint8_t row)
{
    uint8_t addr;

    if (col > 15u) {
        col = 15u;
    }

    switch (row) {
    case 0u:
        addr = 0x00u + col;
        break;
    case 1u:
    default:
        addr = 0x40u + col;   /* Dòng 2 b?t ??u t?i DDRAM 0x40 */
        break;
    }

    LCD_SendCommand(0x80u | addr);  /* Set DDRAM address */
}

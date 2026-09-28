#ifndef BSP_LED_H_
#define BSP_LED_H_
#include "GPIO.h"

#define F_CPU 8000000UL

void BSP_LED_Init(void);
void BSP_LED_On (void);
void BSP_LED_Off(void);

#endif 
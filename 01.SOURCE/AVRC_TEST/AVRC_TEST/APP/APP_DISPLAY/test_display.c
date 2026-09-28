#ifndef F_CPU
#define F_CPU 8000000UL
#endif

#include "avr/io.h"
#include "BSP_LCD.h"
#include "app_display.h"
#include "DATA_DHT.h"
#include "APP_DHT.h"
#include "BSP_BUTTON.h"
#include "APP_BUTTON.h"
#include "BSP_TIMER.h"
#include "APP_LCD_3.h"
#include "avr/interrupt.h"

int main(void)
{

	bsp_button_init();
	
	app_dht_init();
	App_Display_Init();

	BSP_Timer1_Init();
	bsp_button_init();
	
	app_dht_init();
	App_Display_Init();

	sei();

	while (1)
	{
		app_button_update();
		app_button_page_update();
		
		app_dht_update();
		app_LCD_3_update();

		
		App_Display_Task();
	
		

	}

	return 0;
}
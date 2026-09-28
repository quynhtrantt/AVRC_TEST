#include "app_display.h"
#include "BSP_LCD.h"
#include "DATA_DHT.h"
#include "APP_LCD_3.h"
#include "APP_BUTTON.h"
#include "stdio.h"

extern uint8_t set_temp;

static uint8_t current_page = PAGE_TEMPERATURE;
static uint8_t update_index = UPDATE_TEMPERATURE;

static uint8_t page_changed = 1U;
static uint8_t last_temperature = 0U;
static uint8_t last_humidity = 0U;
static uint8_t last_set_temp = 0U;

static void App_Display_ShowPage(void);
static void App_Display_UpdateData(void);

void App_Display_Init(void)
{
	BSP_LCD_Init();
	page_changed = 1U;
}


void App_Display_Task(void)
{
	if (app_button_page_get_state() == BUTTON_PRESSED)
	{
		App_Display_NextPage();
	}

	if (page_changed != 0U)
	{
		App_Display_ShowPage();
	}

	App_Display_UpdateData();
}


void App_Display_NextPage(void)
{
	current_page++;

	if (current_page > PAGE_COUNT)
	{
		current_page = PAGE_TEMPERATURE;
	}

	page_changed = 1U;
}

void App_Display_ShowPage(void)
{
	char buffer[17];

	LCD_GotoXY(0U, 0U);
	LCD_PutString("                ");

	LCD_GotoXY(0U, 1U);
	LCD_PutString("                ");

	switch (current_page)
	{
		case PAGE_TEMPERATURE:
		LCD_GotoXY(0U, 0U);
		LCD_PutString("  TEMPERATURE");

		sprintf(buffer, "      %02u C", data_dht_get_temperature());
		LCD_GotoXY(0U, 1U);
		LCD_PutString(buffer);
		break;

		case PAGE_HUMIDITY:
		LCD_GotoXY(0U, 0U);
		LCD_PutString("    HUMIDITY");

		sprintf(buffer, "      %02u %%", data_dht_get_humidity());
		LCD_GotoXY(0U, 1U);
		LCD_PutString(buffer);
		break;

		case PAGE_COUNT:
		LCD_GotoXY(0U, 0U);
		LCD_PutString("    SET TEMP");

		sprintf(buffer, "      %u", set_temp);
		LCD_GotoXY(0U, 1U);
		LCD_PutString(buffer);
		break;

		default:
		current_page = PAGE_TEMPERATURE;
		break;
	}

	page_changed = 0U;
}

void App_Display_UpdateData(void)
{

	char buffer[17];

	uint8_t temperature;
	uint8_t humidity;

	switch (update_index)
	{
		case UPDATE_TEMPERATURE:
		temperature = data_dht_get_temperature();

		if (temperature != last_temperature)
		{
			last_temperature = temperature;

			if (current_page == PAGE_TEMPERATURE)
			{
				sprintf(buffer, "      %02u C", temperature);

				LCD_GotoXY(0U, 1U);
				LCD_PutString("                ");

				LCD_GotoXY(0U, 1U);
				LCD_PutString(buffer);
			}
		}
		break;

		case UPDATE_HUMIDITY:
		humidity = data_dht_get_humidity();

		if (humidity != last_humidity)
		{
			last_humidity = humidity;

			if (current_page == PAGE_HUMIDITY)
			{
				sprintf(buffer, "      %02u %%", humidity);

				LCD_GotoXY(0U, 1U);
				LCD_PutString("                ");

				LCD_GotoXY(0U, 1U);
				LCD_PutString(buffer);
			}
		}
		break;

		case UPDATE_COUNT:
		if (set_temp != last_set_temp)
		{
			last_set_temp = set_temp;

			if (current_page == PAGE_COUNT)
			{
				sprintf(buffer, "      %u", set_temp);

				LCD_GotoXY(0U, 1U);
				LCD_PutString("                ");

				LCD_GotoXY(0U, 1U);
				LCD_PutString(buffer);
			}
		}
		break;

		default:
		break;
	}

	update_index++;

	if (update_index >= UPDATE_MAX)
	{
		update_index = UPDATE_TEMPERATURE;
	}
}

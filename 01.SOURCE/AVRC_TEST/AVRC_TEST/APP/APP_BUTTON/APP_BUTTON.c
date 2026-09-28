/*
 * APP_BUTTON.c
 *
 * Created: 9/16/2026 4:09:06 PM
 *  Author: HP
 */ 
#include <stdio.h>
#include "bsp_button.h"
typedef enum {S_BUTTON_PRESSED, S_BUTTON_PRESSED_CHECK, S_BUTTON_RELEASED, S_BUTTON_RELEASED_CHECK} button_state_t;
typedef enum {S_PAGE_RELEASED,S_PAGE_PRESSED_CHECK,S_PAGE_PRESSED,S_PAGE_RELEASED_CHECK} page_button_state_t;

static page_button_state_t page_state = S_PAGE_RELEASED;

static button_state_t state = S_BUTTON_RELEASED;

volatile uint16_t	app_button_timer_count;

void app_button_update()
{
	switch (state)
	{
		case S_BUTTON_RELEASED:
		if (BUTTON_PRESSED == bsp_button_start_get_state())
		{
			state = S_BUTTON_PRESSED_CHECK;
			app_button_timer_count = 2000;	//wait for 2000 ms
		}
		break;
		case S_BUTTON_PRESSED_CHECK:
		if (BUTTON_RELEASED == bsp_button_start_get_state())
		{
			state = S_BUTTON_RELEASED;
			app_button_timer_count = 0;	//stop timer
		}
		else if (0 == app_button_timer_count)	//timer fired
		{
			state = S_BUTTON_PRESSED;
		}
		break;
		case S_BUTTON_PRESSED:
		if (BUTTON_RELEASED == bsp_button_start_get_state())
		{
			state = S_BUTTON_RELEASED_CHECK;
			app_button_timer_count = 2000;	//wait for 2000 ms
		}
		break;
		case S_BUTTON_RELEASED_CHECK:
		if (BUTTON_PRESSED == bsp_button_start_get_state())
		{
			state = S_BUTTON_PRESSED;
			app_button_timer_count = 0;	//stop timer
		}
		else if (0 == app_button_timer_count)	//timer fired
		{
			state = S_BUTTON_RELEASED;
		}
		break;
		default:
		break;
	}
}

uint8_t app_button_get_state()
{
	switch (state)
	{
		case S_BUTTON_RELEASED:
		case S_BUTTON_PRESSED_CHECK:
		return BUTTON_RELEASED;
		case S_BUTTON_PRESSED:
		case S_BUTTON_RELEASED_CHECK:
		return BUTTON_PRESSED;
		default:
		return BUTTON_RELEASED;
	}
	
}


void app_button_page_update(void)
{
    switch (page_state)
    {
        case S_PAGE_RELEASED:

            if (BUTTON_PRESSED == bsp_button_page_get_state())
            {
                page_state = S_PAGE_PRESSED_CHECK;
                app_button_timer_count = 100;
            }

            break;


        case S_PAGE_PRESSED_CHECK:

            if (BUTTON_RELEASED == bsp_button_page_get_state())
            {
                page_state = S_PAGE_RELEASED;
                app_button_timer_count = 0;
            }
            else if (app_button_timer_count == 0)
            {
                page_state = S_PAGE_PRESSED;
            }

            break;


        case S_PAGE_PRESSED:

            page_state = S_PAGE_RELEASED_CHECK;

            break;


        case S_PAGE_RELEASED_CHECK:

            if (BUTTON_RELEASED == bsp_button_page_get_state())
            {
                page_state = S_PAGE_RELEASED;
            }

            break;


        default:

            page_state = S_PAGE_RELEASED;
            break;
    }
}

uint8_t app_button_page_get_state(void)
{
    switch (page_state)
    {
        case S_PAGE_PRESSED:
            return BUTTON_PRESSED;

        default:
            return BUTTON_RELEASED;
    }
}
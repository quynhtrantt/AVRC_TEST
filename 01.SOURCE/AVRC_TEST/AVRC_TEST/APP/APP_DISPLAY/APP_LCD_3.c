#include "APP_LCD_3.h"
#include "APP_BUTTON.h"
#include "BSP_BUTTON.h"
#include "DATA_BUTTON.h"
#include "BSP_TIMER.h"
#include "BSP_LCD.h"
#include "GPIO.h"

uint8_t set_temp = 16;
extern volatile uint16_t	app_button_timer_count;
typedef enum
{
    STATE_IDLE,
    STATE_WAIT_HOLD,
    STATE_AUTO_REPEAT,
} temp_control_state_t;

static uint8_t temp_state;
static uint8_t active_btn;

void app_LCD_3_update()
{
    
    switch (temp_state)
    {
    case STATE_IDLE:
        
        if(GPIO_readPin(2, 0) == BUTTON_PRESSED)
        {
            if(set_temp < 30)
            {
                set_temp++;
            }
            else
            {
                break;
            }
            temp_state = STATE_WAIT_HOLD;
            active_btn = 0;
            app_button_timer_count = 500;
        }
        else if(GPIO_readPin(2, 1) == BUTTON_PRESSED)
        {
            if(set_temp > 16)
            {
                set_temp--;
            }
            else
            {
                break;
            }
            temp_state = STATE_WAIT_HOLD;
            active_btn = 1;
            app_button_timer_count = 500;
        }
        else 
        {
            break;
        }
        break;
    case STATE_WAIT_HOLD:
        if(GPIO_readPin(2, active_btn) == BUTTON_RELEASED)
        {
            temp_state = STATE_IDLE;
            app_button_timer_count = 0; // timer oft
        }
        else if(app_button_timer_count == 0) // timer expired
        {
            temp_state = STATE_AUTO_REPEAT;
            app_button_timer_count = 100;
        }
        break;
    case STATE_AUTO_REPEAT:
        if(GPIO_readPin(2, active_btn) == BUTTON_RELEASED)
        {
           temp_state = STATE_IDLE;
           app_button_timer_count = 0; //timer oft
        }
       
        else if(app_button_timer_count == 0)
        {   
            app_button_timer_count = 100;
            if (active_btn == 0 && set_temp < 30)
            {
                set_temp++;
            }
            else if(active_btn == 1 && set_temp > 16)
            {
                set_temp--;
            }
            
        }

        break;
    }
} 
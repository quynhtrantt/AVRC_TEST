#ifndef APP_DISPLAY_H_
#define APP_DISPLAY_H_

#include "stdint.h"

#define PAGE_TEMPERATURE    0U
#define PAGE_HUMIDITY       1U
#define PAGE_COUNT          2U

#define UPDATE_TEMPERATURE  0U
#define UPDATE_HUMIDITY     1U
#define UPDATE_COUNT        2U
#define UPDATE_MAX          3U


void App_Display_Init(void);
void App_Display_Task(void);
void App_Display_NextPage(void);


#endif
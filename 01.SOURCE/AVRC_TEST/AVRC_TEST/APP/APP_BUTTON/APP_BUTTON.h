/*
 * IncFile1.h
 *
 * Created: 9/16/2026 4:09:12 PM
 *  Author: HP
 */ 


#ifndef APP_BUTTON_H_
#define APP_BUTTON_H_

#define BUTTON_PRESSED   0u
#define BUTTON_RELEASED  1u
#include <stdint.h>

void app_button_update();
uint8_t app_button_get_state();

void app_button_page_update(void);
uint8_t app_button_page_get_state(void);


#endif /* INCFILE1_H_ */